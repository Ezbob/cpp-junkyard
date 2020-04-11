
#pragma once

#include <string>
#include <memory>
#include "iquery.hpp"
#include "sqlite3.h"

namespace sqlite_connect
{

class connection
{
private:
    std::string m_db_name;
    sqlite3 *m_db = nullptr;
    bool m_is_open = false;

public:
    explicit connection(std::string name = ":memory:");
    virtual ~connection();

    connection(connection &) = delete;
    connection &operator=(connection &) = delete;

    connection(connection &&other) = default;
    connection &operator=(connection &&other) = default;

    void execute_query(std::shared_ptr<iquery> query);
    void execute_query(iquery &query);
    void execute_query(const char *query);
    bool is_open() const;
    explicit operator sqlite3 *();
    operator bool();
};

}; // namespace sqlite_connect
