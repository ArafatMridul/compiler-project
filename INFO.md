# Project file guide

This workspace contains a small compiler / source-to-source translator for a custom language.

## Source files

- [compiler.y](compiler.y) — Bison grammar for the current compiler front end. It defines the parser, AST construction, semantic checks, and C code generation.
- [compiler.l](compiler.l) — Flex lexer used by the current compiler. It converts source text into tokens for the parser.

## Legacy files

The following reference files were moved into [old](old) and are not part of the current build:

- [old/parser.y](old/parser.y) — Older parser prototype kept for reference.
- [old/scan.l](old/scan.l) — Older lexer prototype kept for reference.
- [old/text.l](old/text.l) — Original lexer-based translator implementation.
- [old/lex.yy.c](old/lex.yy.c) — Legacy generated lexer from the old translator.
- [old/parser.tab.c](old/parser.tab.c) — Legacy generated parser source from the old prototype.
- [old/parser.tab.h](old/parser.tab.h) — Legacy generated parser header from the old prototype.
- [old/scan.yy.c](old/scan.yy.c) — Legacy generated lexer source from the old prototype.
- [old/translator_asan](old/translator_asan) — Temporary ASan debug build.

## Build files

- [Makefile](Makefile) — Automates generation of parser and lexer files, builds the translator, generates C output, and compiles the final executable.

## Input / output files

- [input.txt](input.txt) — Sample program written in the custom language.
- [output.c](output.c) — Generated C source produced by the translator.
- [output](output) — Final compiled executable built from `output.c`.

## Generated files

These files are created during the build process:

- [compiler.tab.c](compiler.tab.c) — Bison-generated parser implementation.
- [compiler.tab.h](compiler.tab.h) — Bison-generated parser header containing token definitions.
- [compiler.yy.c](compiler.yy.c) — Flex-generated lexer implementation for the current compiler.
- [translator](translator) — Executable that reads `input.txt` and writes `output.c`.

## Notes

- The current build uses [compiler.y](compiler.y) and [compiler.l](compiler.l).
- Legacy files now live under [old](old) for reference.
