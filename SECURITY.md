# Security

This is a starting template, not a shipped product. Before you treat a
project derived from it as production software:

- Keep `-Wall -Wextra -Wpedantic` and run `make sanitize` on every change
  that touches memory, parsing, or I/O.
- Never log secrets. Do not read credentials from `data/` in production.
- Prefer bounded buffers (`fgets`, `snprintf`) over `gets`, `scanf("%s")`
  and unbounded `strcat`.
- Report vulnerabilities privately to the repository owner rather than
  opening a public issue.
