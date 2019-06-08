cmake_minimum_required(VERSION 3.0)

set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS "-Wall -Wextra")

project("trait")

add_executable("Main" "src/Main.cpp")
