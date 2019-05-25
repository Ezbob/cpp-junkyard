cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

project("linAlg")

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow -pedantic")

add_executable("Main" "src/Main.cpp")

include_directories("linAlg", "include")
