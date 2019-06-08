cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

project("linAlg")

set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Wshadow -pedantic -Weffc++")

add_executable("main" "src/Main.cpp")

#add_executable("tests" "src/Tests.cpp")

include_directories("linAlg", "include")
