cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

project("asio-test")

add_executable("Main" "src/Main.cpp")

SET(INCLUDE_DIRS
    "modules/asio/asio/include"
)

SET(LINK_LIBS
    "-lwsock32"
)

target_include_directories("Main" PRIVATE ${INCLUDE_DIRS})
target_link_libraries("Main" PRIVATE ${LINK_LIBS})