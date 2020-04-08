
#include "database_transaction.hpp"

using namespace sqlite_connect;

database_transaction::database_transaction(std::shared_ptr<database_connection> db)
    : m_db(db)
{
    start_transaction();
}

database_transaction::~database_transaction()
{
    try
    {
        if (m_has_caught_exception)
        {
            rollback_transaction();
        }
        else
        {
            end_transaction();
        }
    }
    catch (...)
    {
        std::cerr << "Error when issueing transaction rollback\n";
    }
}

void database_transaction::execute_sql(const char *sql)
{
    std::shared_ptr<database_connection> db;
    if (db = m_db.lock())
    {
        char *err = nullptr;
        sqlite3 *db_ptr = (sqlite3 *)(*db);
        int rc = sqlite3_exec(db_ptr, sql, nullptr, nullptr, &err);

        if (database_exception::is_error_code(rc))
        {
            std::string err_msg = sqlite3_errmsg(db_ptr);
            if (err != nullptr)
            {
                err_msg += ": ";
                err_msg += err;
            }
            throw database_exception(err_msg);
        }
    }
}

void database_transaction::start_transaction()
{
    execute_sql("BEGIN TRANSACTION");
}

void database_transaction::end_transaction()
{
    execute_sql("END TRANSACTION");
}

void database_transaction::rollback_transaction()
{
    execute_sql("ROLLBACK TRANSACTION");
}

void database_transaction::execute_query(idatabase_query &q)
{
    try
    {
        std::shared_ptr<database_connection> db;
        if (db = m_db.lock())
        {
            db->execute_query(q);
        }
    }
    catch (database_exception const &e)
    {
        m_has_caught_exception = true;
    }
}
