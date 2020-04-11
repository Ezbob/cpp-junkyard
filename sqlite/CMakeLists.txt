CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

PROJECT(sqlite_buf)

SET(SOURCE_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/src)
SET(SQLITE_PREFIX ${SOURCE_PREFIX}/sqlite_connect)

SET(SOURCES
    ${SOURCE_PREFIX}/main.cpp
    ${SQLITE_PREFIX}/database_exception.cpp
    ${SQLITE_PREFIX}/transaction.cpp
    ${SQLITE_PREFIX}/connection.cpp
    ${SQLITE_PREFIX}/prepared_statement.cpp
    ${SQLITE_PREFIX}/iquery.cpp
)

ADD_SUBDIRECTORY(lib/sqlite3 EXCLUDE_FROM_ALL)

ADD_EXECUTABLE(sqlite_buf "")
TARGET_SOURCES(sqlite_buf PRIVATE ${SOURCES})
TARGET_LINK_LIBRARIES(sqlite_buf sqlite3_static)
TARGET_INCLUDE_DIRECTORIES(sqlite_buf PRIVATE ${SOURCE_DIR} ${SQLITE_PREFIX})