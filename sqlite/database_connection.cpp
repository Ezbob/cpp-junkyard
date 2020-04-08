
#include "database_connection.hpp"

using namespace sqlite_connect;

database_connection::database_connection(std::string name) : m_db_name(name)
{
    m_is_open = (sqlite3_open(m_db_name.c_str(), &m_db) == SQLITE_OK);
}

database_connection::~database_connection()
{
    if (m_is_open)
    {
        sqlite3_close_v2(m_db);
    }
}

void database_connection::execute_query(std::shared_ptr<idatabase_query> query)
{
    execute_query(*query);
}

void database_connection::execute_query(idatabase_query &query)
{
    if (!m_is_open)
    {
        throw database_exception("Database is not open");
    }

    auto prepared = prepared_statement::create();

    prepared->prepare(m_db, query.sql());

    query.execute(prepared);
}

bool database_connection::is_open() const
{
    return m_is_open;
}

database_connection::operator sqlite3 *()
{
    return m_db;
}

database_connection::operator bool()
{
    return m_is_open;
}