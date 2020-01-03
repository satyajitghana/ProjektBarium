cmake_minimum_required(VERSION 3.10)

# enable verbose output from makefiles
set(CMAKE_VERBOSE_MAKEFILE ON)

set(HEADER_COMMON 
                    ASTNode.hpp
                    ASTExpr.hpp 
                    ASTDecimal.hpp 
                    ASTFraction.hpp 
                    ASTIdent.hpp 
                    ASTFunctionCall.hpp 
                    ASTBlock.hpp 
                    ASTStmt.hpp
                    ASTAssignment.hpp)

# make sure you have LLVM
find_package(LLVM REQUIRED CONFIG)

# message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
# message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# find BOOST
find_package(Boost 1.70.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_library(Ast ${HEADER_COMMON})

target_include_directories(Ast PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs support core irreader)

# Link against LLVM libraries
target_link_libraries(Ast ${llvm_libs} ${Boost_LIBRARIES})
