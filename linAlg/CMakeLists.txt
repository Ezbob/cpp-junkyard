cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/googletest-1.10.0)

project("linAlg")

set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Wshadow -pedantic -Weffc++")

set(TEST_INCLUDE_DIRS ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

#add_executable(main "")
#target_sources(main PRIVATE
#    src/Main.cpp
#)

#target_include_directories(main PRIVATE include/)


add_executable(tests "")
target_sources(tests PRIVATE
    src/LinAlg_Vector_TEST.cpp
    src/LinAlg_Matrix_TEST.cpp
)

target_include_directories(tests PRIVATE include/ ${TEST_INCLUDE_DIRS})
target_link_libraries(tests PRIVATE gtest gtest_main)

enable_testing()
add_test(NAME tests COMMAND tests)

