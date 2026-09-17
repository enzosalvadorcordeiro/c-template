# Changelog

## 2.0.0

Reescrita profissional do template original.

- Layout `include/` + `src/` em módulos, com `main.c` separado da lib
- Makefile: debug, release, test, sanitize (ASan+UBSan), format, tidy
- Testes sem dependência (`tests/test.h` + runner)
- Módulo exemplo `text/str` (trim, is_blank, starts_with)
- CLI com `--help` / `--version` e códigos de saída estilo sysexits
- clang-format (Allman, 4 espaços), clang-tidy, clangd, EditorConfig
- GitHub Actions: gcc e clang, `-Werror`, testes e sanitizers
- README, convenções, SECURITY e gitignore de verdade
