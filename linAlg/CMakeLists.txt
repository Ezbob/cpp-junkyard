cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/googletest-1.10.0 EXCLUDE_FROM_ALL)

project("linAlg")

set(TEST_COMPILER_FLAGS
   $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
      -Wall -Wextra -Wshadow -pedantic-errors -Weffc++
   >
   $<$<CXX_COMPILER_ID:MSVC>:
      /W4 /MTd
   >)

add_library(linalg INTERFACE)
target_include_directories(linalg SYSTEM INTERFACE include/)

add_executable(tests "")
target_sources(tests PRIVATE
      src/LinAlg_Vector_TEST.cpp
)
target_compile_options(tests PRIVATE ${TEST_COMPILER_FLAGS})
target_link_libraries(tests PRIVATE linalg gtest gtest_main)
