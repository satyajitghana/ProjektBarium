cmake_minimum_required(VERSION 3.10)
project(barium VERSION 0.1.0)

message(STATUS "==================")
message(STATUS "CONFIGURING Barium")
message(STATUS "==================")

# enable verbose output from makefiles
set(CMAKE_VERBOSE_MAKEFILE ON)

# setup FLEX and BISOn
FIND_PACKAGE(FLEX)
FIND_PACKAGE(BISON)

# sources
set(SOURCES_COMMON tokens.l main.cpp)

# lex the file
FLEX_TARGET(Scanner tokens.l ${CMAKE_CURRENT_BINARY_DIR}/tokens.cc)

# add the executable to the project
add_executable(barium ${SOURCES_COMMON} ${FLEX_Scanner_OUTPUTS})

# set the executable to use C++17
set_property(TARGET barium PROPERTY CXX_STANDARD 17)
set_property(TARGET barium PROPERTY CXX_STANDARD_REQUIRED ON)

# additional search directories
target_include_directories(barium PRIVATE ${barium_SOURCE_DIR})
target_include_directories(barium PRIVATE ${CMAKE_CURRENT_BINARY_DIR})