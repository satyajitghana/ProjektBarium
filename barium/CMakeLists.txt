cmake_minimum_required(VERSION 3.0.0)
project(ProjektBarium VERSION 0.1.0)

# setup FLEX and BISON
FIND_PACKAGE(FLEX)
FIND_PACKAGE(BISON)

# pthreads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(HELPER_FILES visitor.hpp visitor_pprint.cpp visitor_pprint.hpp)

set(SOURCES_COMMON main.cpp driver.cpp ast_structures.cpp code_generator.cpp extern_func.cpp parser.y tokens.l)
set(HEADERS_COMMON driver.hpp ast_structures.hpp code_generator.hpp extern_func.hpp)

# create the tokenizer
FLEX_TARGET(Scanner tokens.l ${CMAKE_CURRENT_BINARY_DIR}/tokens.cpp)

# create the parser
BISON_TARGET(Parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)

# for parser.hpp to be generated to be used by tokens.l
ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

# add LLVM to project
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# additional include directories
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# external sources
aux_source_directory(external EXTERNAL_HEADERS)

# add the executable to the project with the Scanner and the Parser
add_executable(barium ${SOURCES_COMMON}
                      ${HEADERS_COMMON} 
                      ${FLEX_Scanner_OUTPUTS}
                      ${BISON_Parser_OUTPUTS}
                      ${EXTERNAL_HEADERS}
                      ${HELPER_FILES})


target_compile_definitions(barium PRIVATE LOGURU_WITH_STREAMS=1)

# link pthreads
target_link_libraries(barium PUBLIC Threads::Threads)

if(NOT WIN32)
  target_link_libraries(barium PRIVATE dl)
endif(NOT WIN32)

# Add additional include search directories.
target_include_directories(barium PUBLIC ${ProjektBarium_SOURCE_DIR})
target_include_directories(barium PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

# Now set the header and library paths:
include_directories( ${LLVM_ROOT}/include )
link_directories( ${LLVM_ROOT}/lib )

if(LLVM_LINK_LLVM_DYLIB)
  set(USE_SHARED USE_SHARED)
endif()
llvm_config(barium ${USE_SHARED} ${llvm_libs})

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs core native irreader mcjit)

# Link against LLVM libraries
target_link_libraries(barium PRIVATE ${llvm_libs})

# lets say you want to link liblldELF then use find_library(YOUR_LIB_NAME lldELF)
# then later you can link ${YOUR_LIB_NAME} to the executable, pretty neat
# you can print the list of libraries using : /sbin/ldconfig -p
# find_library(LLDELF_LIB lldELF)
# target_link_libraries(barium PUBLIC "${LLDELF_LIB}")

set_target_properties(barium PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)

