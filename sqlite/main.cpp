#include <iostream>
#include "sqlite3.h"
#include <memory>
#include <exception>
#include <string>
#include <vector>

#include "database_exception.hpp"
#include "prepared_statement.hpp"
#include "idatabase_query.hpp"
#include "database_connection.hpp"
#include "database_transaction.hpp"

struct create_table_query : public sqlite_connect::idatabase_query
{
    const char *sql() const override
    {
        return "CREATE TABLE IF NOT EXISTS tab ( id INTEGER PRIMARY KEY, x INTEGER, y REAL )";
    }
};

struct insert_query : public sqlite_connect::idatabase_query
{
    const char *sql() const override
    {
        return "INSERT OR IGNORE INTO tab (x, y) VALUES (32, 2.3), (42, 2.7), (11, 1.2)";
    }
};

struct upsert_query : public sqlite_connect::idatabase_query
{
    const char *sql() const override
    {
        return "INSERT OR IGNORE INTO tab (x, y) VALUES (32, 2.3), (42, 2.7), (11, 1.2)";
    }
};

struct select_query : public sqlite_connect::idatabase_query
{

    struct record
    {
        int64_t id;
        int x;
        double y;
    };

    std::vector<record> records;

    const char *sql() const override
    {
        return "SELECT * FROM tab";
    }

    void execute(std::shared_ptr<sqlite_connect::prepared_statement> stmt) override
    {
        while (stmt->step())
        {
            record r;
            stmt->extract_column(0, r.id);
            stmt->extract_column(1, r.x);
            stmt->extract_column(2, r.y);
            records.push_back(r);
        }
    }
};

int main(void)
{
    auto connection = std::make_shared<sqlite_connect::database_connection>();

    {
        sqlite_connect::database_transaction transaction(connection);
        create_table_query create;
        insert_query insert;

        transaction.execute_query(create);
        transaction.execute_query(insert);
    }

    select_query select;

    connection->execute_query(select);

    for (auto &r : select.records)
    {
        std::cout << "(id: " << r.id << ", x: " << r.x << ", y: " << r.y << ")\n";
    }

    return 0;
}
