# C17 template

Template profissional de C para trabalhos da faculdade e para o primeiro emprego.
Makefile POSIX, testes sem dependência extra, sanitizers, formatação e CI.

O módulo `text/str` e o programa em `src/main.c` existem só para demonstrar o
fluxo **header → source → teste → binário**. Apague-os quando o projeto for
o seu.

Repositório original: [c-template](https://github.com/enzosalvadorcordeiro/c-template)

## Requisitos

- GCC 11+ ou Clang 14+
- GNU Make
- Linux, macOS ou WSL. No Windows nativo, use MinGW ou compile no WSL.

Opcional: `clang-format`, `clang-tidy`, extensão **clangd** no VS Code / CLion.

## Começar

```text
make            # bin/app  (debug, -g -O0)
make test       # testes em tests/
make run        # lê data/sample.txt e imprime linhas úteis
make sanitize   # ASan + UBSan nos testes — rode sempre que mexer em memória
make release    # -O2 -DNDEBUG
make help
```

Compilar com Clang: `make CC=clang`.
Tratar warning como erro: `make WERROR=1` (já é o padrão no CI).

## Estrutura

```text
include/          API pública, um header por módulo
  app/            version.h, status.h
  text/           str.h
src/              implementação, espelha include/
  main.c          ponto de entrada — não coloque lógica aqui
  text/str.c
tests/            runner + um arquivo test_<modulo>.c por módulo
data/             entradas de exemplo (não commitar segredos)
bin/              executáveis gerados (gitignored)
build/            .o e .d gerados (gitignored)
.github/workflows CI: gcc e clang, testes e sanitizers
```

`include/` é o que o resto do programa pode ver. Tudo que for privado do
módulo fica `static` no `.c`.

## Alvos do Makefile

| Alvo        | Função                                              |
| ----------- | --------------------------------------------------- |
| `all`       | binário de debug                                    |
| `run`       | executa `bin/app data/sample.txt`                   |
| `test`      | liga a lib (tudo menos `main.c`) com o runner       |
| `sanitize`  | rebuild + testes com AddressSanitizer e UBSan       |
| `release`   | binário otimizado                                   |
| `format`    | `clang-format -i` segundo `.clang-format`           |
| `tidy`      | `clang-tidy` segundo `.clang-tidy`                  |
| `clean`     | apaga artefatos, preserva `.gitkeep`                |

## Convenções

Leia [docs/CONVENTIONS.md](docs/CONVENTIONS.md). Resumo:

| Coisa        | Forma                         | Exemplo              |
| ------------ | ----------------------------- | -------------------- |
| Arquivo      | `snake_case.c` / `.h`         | `text/str.c`         |
| Função       | `modulo_verbo_objeto`         | `str_starts_with`    |
| Tipo typedef | `snake_case` + `_t`           | `app_status` (enum)  |
| Macro        | `SCREAMING_SNAKE`             | `APP_VERSION`        |
| Chaves       | Allman (chave na linha de baixo) | igual a este repo |
| Header       | include guard `MODULO_H`      | `TEXT_STR_H`         |
| Include      | `"text/str.h"` via `-Iinclude` | nunca `../include` |

Código em inglês. Documentação pode ficar em português.

## Como usar isto num trabalho novo

1. Copie o conteúdo deste repositório para o seu (mantenha o `.git` dele).
2. Renomeie `APP_NAME` / `APP_VERSION` em `include/app/version.h`.
3. Substitua `text/str` pelo primeiro módulo do trabalho.
4. Atualize `TEST_SRCS` no Makefile se criar `tests/test_outro.c`.
5. `make test && make sanitize` antes de cada commit.

Para adicionar um módulo `graph`:

```text
include/graph/graph.h
src/graph/graph.c
tests/test_graph.c
```

Declare `void test_graph_...(void);` no runner, acrescente o `.c` em
`TEST_SRCS`, rode `make test`.

## Por que sanitizers

ASan encontra use-after-free, double free e buffer overflow.
UBSan encontra shift inválido, overflow com sinal, null dereference.
Um programa que “passa nos testes” e explode no sanitizer tem um bug real —
é o tipo de coisa que aparece na prova prática e na entrevista.

## Licença

MIT. Veja [LICENSE](LICENSE).
