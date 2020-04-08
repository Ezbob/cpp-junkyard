CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

PROJECT(sqlite_buf)

SET(SOURCES
    main.cpp
    database_exception.cpp
    database_transaction.cpp
    database_connection.cpp
    prepared_statement.cpp
    idatabase_query.cpp
)

ADD_SUBDIRECTORY(lib/sqlite3 EXCLUDE_FROM_ALL)

ADD_EXECUTABLE(sqlite_buf "")
TARGET_SOURCES(sqlite_buf PRIVATE ${SOURCES})
TARGET_LINK_LIBRARIES(sqlite_buf sqlite3_static)