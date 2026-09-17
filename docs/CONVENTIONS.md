# Convenções C

Regras para este template. São as mesmas que times de sistemas, embarcados
e infraestrutura esperam num repositório novo.

## Nomes

- Arquivos e diretórios: `snake_case`. Um conceito por arquivo.
- O header público `include/<modulo>/<arquivo>.h` tem implementação em
  `src/<modulo>/<arquivo>.c`. O caminho relativo depois de `include/` e
  `src/` é o mesmo.
- Funções públicas: prefixo do módulo, depois verbo. `str_trim`,
  `graph_add_edge`, `arena_alloc`.
- Funções privadas: `static` no `.c`. Sem prefixo de módulo se o arquivo
  já é o módulo; se o arquivo crescer, prefixe com o nome interno.
- Macros e constantes de compilação: `MODULO_NOME`.
- Enums: tipo em `snake_case` (`app_status`), variantes em `SCREAMING_SNAKE`
  (`APP_ERR_IO`).
- Typedefs de struct: `typedef struct foo foo_t;` — ou, preferível neste
  template, o enum/struct com nome próprio e sem typedef extra.

Não use camelCase nem PascalCase em C. Isso é Java.

## Headers

- Todo header tem include guard `MODULO_ARQUIVO_H`. `#pragma once` é
  aceito em compiladores modernos, mas o guard portátil está neste repo.
- Include o que o header usa. Não inclua o mundo em um `common.h`.
- Headers públicos não declaram `static` nem detalhes de implementação.
- Wrapping `extern "C"` permite que o mesmo header seja usado em C++.
- O resto do código inclui `"text/str.h"`, nunca o caminho relativo até
  `include/`. O `-Iinclude` do Makefile cuida disso.

## Estilo

- C17. Sem VLA em API pública. Sem `gets`. Sem `typedef` de ponteiro
  (`typedef struct foo *Foo`) — esconde a indireção.
- Chaves Allman, 4 espaços, 100 colunas (`.clang-format`).
- Sempre chaves, inclusive no `if` de uma linha.
- Ponteiro: `char *text`, espaço à esquerda (PointerAlignment: Right).
- `const` em todo parâmetro que não é escrito.
- Cast de `isspace` / `tolower` para `unsigned char`.
- Erros de biblioteca: retorne `app_status` (ou um enum do módulo).
  `errno` fica para I/O da libc. Não use `exit()` no meio de uma lib —
  só em `main` depois de reportar o erro.

## `main`

`main` analisa argumentos, abre recursos, chama o núcleo, fecha recursos,
devolve o status. Lógica de verdade vive em módulos testáveis. Por isso
os testes ligam todos os `.o` **exceto** `main.o`.

Códigos de saída seguem sysexits quando faz sentido: 0 ok, 64 uso, 66
arquivo inexistente, 74 I/O.

## Testes

- Um `tests/test_<modulo>.c` por módulo. Sem framework externo: as macros
  em `tests/test.h` bastam para a faculdade e para um serviço pequeno.
- Nomes: `test_<unidade>_<comportamento>`.
- Cubra o caminho feliz, o vazio, o NULL e um caso de borda.
- `make test` precisa passar. `make sanitize` também, no CI e na sua
  máquina, antes do push.

Quando o projeto crescer e você quiser um framework, Unity ou Criterion
encaixam neste layout sem mexer em `include/` nem `src/`.

## Git

- Commits em inglês, modo imperativo: `Add graph_add_edge tests`.
- Não commitar `bin/`, `build/`, `.o`, cores de sanitizer, nem arquivos
  de IDE pessoais. `.vscode/settings.json` compartilhado sim.
- Um PR / um trabalho: o CI em `.github/workflows/ci.yml` roda gcc e
  clang com `-Werror` e sanitizers.

## O que não fazer

- Um `utils.c` gigante. Abra um módulo.
- `#define` de constante que deveria ser `static const` ou `enum`.
- `using` / namespaces — isto não é C++.
- Compilar com o botão da IDE e ignorar o Makefile. O Makefile é o
  contrato do projeto. A IDE deve chamar `make`.
