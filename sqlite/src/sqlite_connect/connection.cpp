
#include "connection.hpp"
#include <iostream>

using namespace sqlite_connect;

connection::connection(std::string name) : m_db_name(name)
{
    m_is_open = (sqlite3_open(m_db_name.c_str(), &m_db) == SQLITE_OK);
}

connection::~connection()
{
    if (m_is_open)
    {
        sqlite3_close_v2(m_db);
    }
}

void connection::execute_query(const char *query)
{
    char *err = nullptr;
    int rc = sqlite3_exec(m_db, query, nullptr, nullptr, &err);

    if (database_exception::is_error_code(rc))
    {
        std::string err_msg = sqlite3_errmsg(m_db);
        if (err != nullptr)
        {
            err_msg += ": ";
            err_msg += err;
        }
        throw database_exception(err_msg);
    }
}

void connection::execute_query(std::shared_ptr<iquery> query)
{
    this->execute_query(*query);
}

void connection::execute_query(iquery &query)
{
    if (!m_is_open)
    {
        throw database_exception("Database is not open");
    }

    try
    {
        if (query.is_cached()) {
            auto cached = query.cache();
            cached->reset();
            query.execute(cached);
        } else {
            auto prepared = std::make_shared<prepared_statement>();
            prepared->prepare(m_db, query.sql());
            query.execute(prepared);
            query.cache(prepared);
        }
    }
    catch (database_exception const &e)
    {
        std::string new_err = e.what();
        new_err += ": ";
        new_err += sqlite3_errmsg(m_db);
        throw database_exception(new_err);
    }
}

bool connection::is_open() const
{
    return this->m_is_open;
}

connection::operator sqlite3 *()
{
    return this->m_db;
}

connection::operator bool()
{
    return this->m_is_open;
}