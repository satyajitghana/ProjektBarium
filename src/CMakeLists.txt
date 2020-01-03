cmake_minimum_required(VERSION 3.10)
project(barium VERSION 0.1.0)

message(STATUS "==================")
message(STATUS "CONFIGURING Barium")
message(STATUS "==================")

# enable verbose output from makefiles
set(CMAKE_VERBOSE_MAKEFILE ON)

# make sure you have LLVM
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs support core irreader all)

# setup FLEX and BISON
FIND_PACKAGE(FLEX)
FIND_PACKAGE(BISON)

# sources
set(SOURCES_COMMON tokens.l parser.y main.cpp codegen_context.cpp)

# headers
set(HEADERS_COMMON codegen_context.hpp)

# create the tokenizer
FLEX_TARGET(Scanner tokens.l ${CMAKE_CURRENT_BINARY_DIR}/tokens.cpp)

# create the parser
BISON_TARGET(Parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)

# for parser.hpp to be generated to be used by tokens.l
ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

# add the executable to the project with the Scanner and the Parser
add_executable(barium ${SOURCES_COMMON} ${HEADERS_COMMON} ${FLEX_Scanner_OUTPUTS} ${BISON_Parser_OUTPUTS})

# set the executable to use C++17
set_property(TARGET barium PROPERTY CXX_STANDARD 17)
set_property(TARGET barium PROPERTY CXX_STANDARD_REQUIRED ON)

# additional search directories
target_include_directories(barium PRIVATE ${barium_SOURCE_DIR})
target_include_directories(barium PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

# LLVM - Abstract Syntax Tree
add_subdirectory(AST)

# link the AST and LLVM
target_link_libraries(barium LINK_PUBLIC Ast ${llvm_libs})