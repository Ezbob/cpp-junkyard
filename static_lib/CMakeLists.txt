cmake_minimum_required(VERSION 3.12)

project(
    "staticlib"
    DESCRIPTION "A lib"
    LANGUAGES CXX
)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

set(LIB_SOURCES
    src/lib.cpp
)

set(EXEC_SOURCES
    src/main.cpp
)

set(INCLUDE_DIRS
    "${PROJECT_SOURCE_DIR}/include"
)

include_directories(
    ${INCLUDE_DIRS}
)

add_library(lib STATIC ${LIB_SOURCES})

add_executable(main ${EXEC_SOURCES})

target_link_libraries(main PRIVATE lib)
