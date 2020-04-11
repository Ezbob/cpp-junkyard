#include <iostream>
#include "sqlite3.h"
#include <memory>
#include <exception>
#include <string>
#include <vector>

#include "sqlite_connect/sqlite_connect.hpp"

struct create_table_query : public sqlite_connect::iquery
{
    const char *sql() const override
    {
        return "CREATE TABLE IF NOT EXISTS tab ( id INTEGER PRIMARY KEY, x INTEGER, y REAL )";
    }
};

struct insert_query : public sqlite_connect::iquery
{
    const char *sql() const override
    {
        return "INSERT OR IGNORE INTO tab (x, y) VALUES (32, 2.3), (42, 2.7), (11, 1.2)";
    }
};

struct upsert_query : public sqlite_connect::iquery
{
    const char *sql() const override
    {
        return "INSERT OR IGNORE INTO tab (x, y) VALUES (32, 2.3), (42, 2.7), (11, 1.2)";
    }
};

struct select_query : public sqlite_connect::iquery
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
    auto connection = std::make_shared<sqlite_connect::connection>();

    {
        sqlite_connect::transaction transaction(connection);
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
