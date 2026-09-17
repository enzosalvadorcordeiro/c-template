# Professional C17 template.
#
#   make            debug build  (bin/app)
#   make run        build and run with data/sample.txt
#   make test       unit tests
#   make sanitize   tests under ASan + UBSan
#   make release    -O2 -DNDEBUG
#   make format     clang-format (if installed)
#   make tidy       clang-tidy   (if installed)
#   make help       this list
#
# Override the compiler with `make CC=clang`.
# Treat warnings as errors with `make WERROR=1`.

CC     ?= gcc
STD    ?= c17
WERROR ?= 0

SRC_DIR  := src
INC_DIR  := include
TEST_DIR := tests
OBJ_DIR  := build
BIN_DIR  := bin
DATA_DIR := data

APP_NAME := app
ifeq ($(OS),Windows_NT)
  EXE := .exe
else
  EXE :=
endif

APP      := $(BIN_DIR)/$(APP_NAME)$(EXE)
TEST_BIN := $(BIN_DIR)/tests$(EXE)

SRCS := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

LIB_OBJS := $(filter-out $(OBJ_DIR)/main.o,$(OBJS))
TEST_SRCS := $(TEST_DIR)/runner.c $(wildcard $(TEST_DIR)/test_*.c)
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/tests/%.o,$(TEST_SRCS))
TEST_DEPS := $(TEST_OBJS:.o=.d)

WARNINGS := -Wall -Wextra -Wpedantic -Wshadow -Wconversion \
            -Wstrict-prototypes -Wmissing-prototypes -Wformat=2 \
            -Wno-unused-command-line-argument
ifeq ($(WERROR),1)
  WARNINGS += -Werror
endif

CPPFLAGS := -I$(INC_DIR) -I$(TEST_DIR) -MMD -MP
CFLAGS_COMMON := -std=$(STD) $(WARNINGS)
CFLAGS_DEBUG := $(CFLAGS_COMMON) -g -O0 -fno-omit-frame-pointer
CFLAGS_RELEASE := $(CFLAGS_COMMON) -O2 -DNDEBUG
CFLAGS_SAN := $(CFLAGS_COMMON) -g -O1 -fno-omit-frame-pointer \
              -fsanitize=address,undefined -fno-sanitize-recover=all

CFLAGS  ?= $(CFLAGS_DEBUG)
LDFLAGS ?=
LDLIBS  ?=

.PHONY: all run test sanitize release format tidy clean help dirs

all: $(APP)

$(APP): $(OBJS) | dirs
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | dirs
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/tests/%.o: $(TEST_DIR)/%.c | dirs
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(TEST_BIN): $(LIB_OBJS) $(TEST_OBJS) | dirs
	$(CC) $(LDFLAGS) -o $@ $(TEST_OBJS) $(LIB_OBJS) $(LDLIBS)

run: $(APP)
	./$(APP) $(DATA_DIR)/sample.txt

test: $(TEST_BIN)
	./$(TEST_BIN)

sanitize:
	$(MAKE) clean
	$(MAKE) test CFLAGS="$(CFLAGS_SAN)" LDFLAGS="$(CFLAGS_SAN)"
	$(MAKE) clean

release:
	$(MAKE) clean
	$(MAKE) all CFLAGS="$(CFLAGS_RELEASE)"

format:
	@command -v clang-format >/dev/null || { echo "clang-format not installed"; exit 1; }
	clang-format -i $(SRCS) $(INC_DIR)/*/*.h $(TEST_SRCS) $(TEST_DIR)/test.h

tidy:
	@command -v clang-tidy >/dev/null || { echo "clang-tidy not installed"; exit 1; }
	clang-tidy $(SRCS) -- $(CPPFLAGS) $(CFLAGS_DEBUG)

dirs:
	@mkdir -p $(BIN_DIR) $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	mkdir -p $(OBJ_DIR) $(BIN_DIR)
	touch $(OBJ_DIR)/.gitkeep $(BIN_DIR)/.gitkeep
	rm -f $(APP) $(TEST_BIN) $(APP).d $(TEST_BIN).d

help:
	@printf '%s\n' \
		'make            debug build' \
		'make run        run bin/app on data/sample.txt' \
		'make test       unit tests' \
		'make sanitize   tests with ASan + UBSan' \
		'make release    optimized binary' \
		'make format     clang-format' \
		'make tidy       clang-tidy' \
		'make clean      remove build artifacts' \
		'make CC=clang   compile with clang' \
		'make WERROR=1   treat warnings as errors'

-include $(DEPS) $(TEST_DEPS)
