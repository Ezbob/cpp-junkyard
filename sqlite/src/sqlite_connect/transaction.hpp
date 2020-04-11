
#pragma once

#include <memory>
#include "connection.hpp"
#include "sqlite3.h"
#include <iostream>

namespace sqlite_connect
{

class transaction
{
private:
    std::weak_ptr<connection> m_db;

    void execute_sql(const char *sql);
    void start_transaction();
    void end_transaction();
    void rollback_transaction();

public:
    transaction(std::shared_ptr<connection> db);
    virtual ~transaction();

    void execute_query(iquery &q);
};
}; // namespace sqlite_connect
