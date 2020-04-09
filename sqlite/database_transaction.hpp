
#pragma once

#include <memory>
#include "database_connection.hpp"
#include "sqlite3.h"
#include <iostream>

namespace sqlite_connect {

class database_transaction
{
private:
    std::weak_ptr<database_connection> m_db;

    void execute_sql(const char *sql);
    void start_transaction();
    void end_transaction();
    void rollback_transaction();
public:
    database_transaction(std::shared_ptr<database_connection> db);
    virtual ~database_transaction();

    void execute_query(idatabase_query &q);

};
}; // namespace sqlite_connect
