
#include "prepared_statement.hpp"

using namespace sqlite_connect;

void prepared_statement::throw_on_no_row(void)
{
    if (!m_has_row)
    {
        throw database_exception("No row available");
    }
}

prepared_statement::~prepared_statement()
{
    sqlite3_finalize(m_stmt);
}

void prepared_statement::bind(size_t i, int value)
{
    database_exception::throw_on_error(sqlite3_bind_int(m_stmt, i, value));
}

void prepared_statement::bind(size_t i, long long value)
{
    database_exception::throw_on_error(sqlite3_bind_int64(m_stmt, i, value));
}

void prepared_statement::bind(size_t i, double value)
{
    database_exception::throw_on_error(sqlite3_bind_double(m_stmt, i, value));
}

void prepared_statement::bind(size_t i, float value)
{
    database_exception::throw_on_error(sqlite3_bind_double(m_stmt, i, value));
}

void prepared_statement::bind(size_t i, std::string const &value)
{
    database_exception::throw_on_error(sqlite3_bind_text(m_stmt, i, value.c_str(), -1, nullptr));
}

void prepared_statement::prepare(sqlite3 *db, const char *sql, const char **more)
{
    database_exception::throw_on_error(sqlite3_prepare_v2(db, sql, -1, &m_stmt, more));
}

void prepared_statement::extract_column(size_t i, int &output)
{
    throw_on_no_row();
    output = sqlite3_column_int(m_stmt, i);
}

void prepared_statement::extract_column(size_t i, long long &output)
{
    throw_on_no_row();
    output = sqlite3_column_int64(m_stmt, i);
}

void prepared_statement::extract_column(size_t i, float &output)
{
    throw_on_no_row();
    output = sqlite3_column_double(m_stmt, i);
}

void prepared_statement::extract_column(size_t i, double &output)
{
    throw_on_no_row();
    output = sqlite3_column_double(m_stmt, i);
}

void prepared_statement::extract_column(size_t i, std::string &output)
{
    throw_on_no_row();
    output = reinterpret_cast<const char *>(sqlite3_column_text(m_stmt, i));
}

bool prepared_statement::step()
{
    m_has_row = false;
    int rc = sqlite3_step(m_stmt);

    if (rc == SQLITE_ROW)
    {
        m_has_row = true;
        return true;
    }
    else if (rc == SQLITE_DONE)
    {
        return false;
    }
    else
    {
        throw database_exception(sqlite3_errstr(rc));
    }
}

void prepared_statement::reset()
{
    int rc = sqlite3_reset(m_stmt);
    if (database_exception::is_error_code(rc))
    {
        throw database_exception(sqlite3_errstr(rc));
    }
}

bool prepared_statement::has_row() const
{
    return m_has_row;
}

prepared_statement::operator sqlite3_stmt *()
{
    return m_stmt;
}

