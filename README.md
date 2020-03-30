# Projekt Barium - A Basic Compiler for Barium Programming Language

This is the compiler i built for my programming lanugage barium, a fun little project to understand compilers.

Tech Stack : Flex, Bison, LLVM

## Build Status

![Barium-CI](https://github.com/satyajitghana/ProjektBarium/workflows/Barium-CI/badge.svg)

## The Compiler Recipe

Lexical Analyzer (Lex) -> Semantic Parsing (Bison) -> Assembly (LLVM) -> Executable


### Task List

- [X] Add Data Types
- [X] Operators, Symbols, Reserved Keywords
- [ ] Add Looping Statements - ongoing
- [ ] Add Control Statements - ongoing
- [X] Add Output Statements - uses vprintf
- [ ] Add Input Statements
- [ ] Add Arrays Support
- [ ] Finish the compiler
- [ ] Make it a Library
- [ ] Add Boost Math Support
- [ ] Containerize the Compiler using Docker
- [X] Create a CI/CD Pipeline
- [X] Output executables instead of obj files

## Dependencies

LLVM 9.0.1
Bison 3.5

## Build Instructions


## Example Run

Normal Run

```shell
$ ./barium test_files/test.bar -v OFF
```

Debug Verbose Run

```shell
$ ./barium test_files/test.bar -v INFO
```
