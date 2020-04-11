
#include "transaction.hpp"

using namespace sqlite_connect;

transaction::transaction(std::shared_ptr<connection> db)
    : m_db(db)
{
    start_transaction();
}

transaction::~transaction()
{
    try
    {
        end_transaction();
    }
    catch (std::exception const &e)
    {
        std::cerr << "Transaction commit error: " << e.what() << "\n";
    }
}

void transaction::execute_sql(const char *sql)
{
    std::shared_ptr<connection> db;
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

void transaction::start_transaction()
{
    execute_sql("BEGIN TRANSACTION");
}

void transaction::end_transaction()
{
    execute_sql("END TRANSACTION");
}

void transaction::rollback_transaction()
{
    execute_sql("ROLLBACK TRANSACTION");
}

void transaction::execute_query(iquery &q)
{

    std::shared_ptr<connection> db;
    if (db = m_db.lock())
    {
        try
        {
            db->execute_query(q);
        }
        catch (database_exception const &e)
        {
            std::string new_err = e.what();
            new_err += ": ";
            new_err += sqlite3_errmsg((sqlite3 *)db.get());

            rollback_transaction();

            throw database_exception(new_err);
        }
    }
}
