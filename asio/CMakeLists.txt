cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

project("asio-test")

add_executable(${TARGET_EXE} "src/Main.cpp")

SET(INCLUDE_DIRS
    "modules/asio/asio/include"
)

SET(LINK_LIBS "")

if(WIN32)
    LIST(APPEND LINK_LIBS "-lwsock32")
endif()

target_include_directories(${TARGET_EXE} PRIVATE ${INCLUDE_DIRS})
target_link_libraries(${TARGET_EXE} PRIVATE ${LINK_LIBS})