cmake_minimum_required(VERSION 3.0)
set (CMAKE_CXX_STANDARD 11)

project("trait")

set(SOURCES
    "src/Main.cpp"
)

add_executable("Main" ${SOURCES})

