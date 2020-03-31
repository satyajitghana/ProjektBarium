# Projekt Barium - A Basic Compiler for Barium Programming Language

This is the compiler i built for my programming lanugage barium, a fun little project to understand compilers.

Tech Stack : Flex, Bison, LLVM

## Build Status

![ubuntu-build](https://github.com/satyajitghana/ProjektBarium/workflows/ubuntu-build/badge.svg)

## Status

![language-count](https://img.shields.io/github/languages/count/satyajitghana/ProjektBarium)
![top-language](https://img.shields.io/github/languages/top/satyajitghana/ProjektBarium)
![repo-size](https://img.shields.io/github/repo-size/satyajitghana/ProjektBarium)
![loc-count](https://sloc.xyz/github/satyajitghana/ProjektBarium)

![release-date](https://img.shields.io/github/release-date-pre/satyajitghana/ProjektBarium)
![release](https://img.shields.io/github/v/release/satyajitghana/ProjektBarium?include_prereleases)
![license](https://img.shields.io/github/license/satyajitghana/ProjektBarium)
![maintainer](https://img.shields.io/badge/maintainer-shadowleaf-blue)

## The Compiler Recipe

Lexical Analyzer (Lex) -> Semantic Parsing (Bison) -> Assembly (LLVM) -> Executable


### Task List

- [X] Add Data Types (decimal, fraction)
- [X] Operators, Symbols, Reserved Keywords
- [X] Add Looping Statements - ongoing (parse done)
- [X] Add Control Statements - ongoing (parse done)
- [X] Add Output Statements - uses vprintf
- [ ] Add Input Statements
- [X] Add Arrays Support - ongoing (parse done)
- [X] Create a CI/CD Pipeline
- [X] Output executables instead of obj files (partial support)
- [X] locations (YYLTYPE, and @$)

### Far-fetched task list

- [ ] Make it a Library
- [ ] Add Boost Math Support
- [ ] Containerize the Compiler using Docker

## Dependencies

- LLVM    9.0.1
- Bison   3.5.2
- Flex    2.6.4

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
