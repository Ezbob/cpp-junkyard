
#pragma once

#include <string>
#include <memory>
#include "idatabase_query.hpp"
#include "sqlite3.h"

namespace sqlite_connect {

class database_connection
{
private:
    std::string m_db_name;
    sqlite3 *m_db = nullptr;
    bool m_is_open = false;

public:
    explicit database_connection(std::string name = ":memory:");
    virtual ~database_connection();

    database_connection(database_connection &) = delete;
    database_connection &operator=(database_connection &) = delete;

    database_connection(database_connection &&other) = default;
    database_connection &operator=(database_connection &&other) = default;

    void execute_query(std::shared_ptr<idatabase_query> query);
    void execute_query(idatabase_query &query);
    bool is_open() const;
    explicit operator sqlite3 *();
    operator bool();
};

}; // namespace sqlite_connect
