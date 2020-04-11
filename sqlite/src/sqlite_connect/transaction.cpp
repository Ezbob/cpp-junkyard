
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
        db->execute_query(sql);
    }
    else
    {
        throw database_exception("Could not execute one-step query");
    }
}

void transaction::start_transaction()
{
    this->execute_sql("BEGIN TRANSACTION");
}

void transaction::end_transaction()
{
    this->execute_sql("END TRANSACTION");
}

void transaction::rollback_transaction()
{
    this->execute_sql("ROLLBACK TRANSACTION");
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
            this->rollback_transaction();

            throw e;
        }
    }
}
