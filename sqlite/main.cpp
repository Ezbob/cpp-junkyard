#include <iostream>
#include "sqlite3.h"
#include <memory>
#include <exception>
#include <string>
#include <vector>

namespace sqlite_connect
{
struct database_exception : std::runtime_error
{
    virtual ~database_exception() = default;
    explicit database_exception(std::string const &what_arg) : std::runtime_error(what_arg) {}
    explicit database_exception(const char *what_arg) : std::runtime_error(what_arg) {}
};

bool is_error_code(int rc)
{
    return !(SQLITE_DONE == rc || SQLITE_OK == rc || SQLITE_DONE == rc);
}

void throw_on_error(int rc)
{
    if (is_error_code(rc))
    {
        throw database_exception(sqlite3_errstr(rc));
    }
}

class prepared_statement
{
private:
    sqlite3_stmt *m_stmt = nullptr;
    bool m_has_row = false;

    void throw_on_no_row(void)
    {
        if (!m_has_row)
        {
            throw database_exception("No row available");
        }
    }

public:
    prepared_statement() = default;
    virtual ~prepared_statement()
    {
        sqlite3_finalize(m_stmt);
    };

    prepared_statement(prepared_statement &) = delete;
    prepared_statement &operator=(prepared_statement &) = delete;

    prepared_statement(prepared_statement &&) = default;
    prepared_statement &operator=(prepared_statement &&) = default;

    void prepare(sqlite3 *db, const char *sql, const char **more = nullptr)
    {
        throw_on_error(sqlite3_prepare_v2(db, sql, -1, &m_stmt, more));
    }

    void bind(size_t i, int value)
    {
        throw_on_error(sqlite3_bind_int(m_stmt, i, value));
    }
    void bind(size_t i, long long value)
    {
        throw_on_error(sqlite3_bind_int64(m_stmt, i, value));
    }
    void bind(size_t i, double value)
    {
        throw_on_error(sqlite3_bind_double(m_stmt, i, value));
    }
    void bind(size_t i, float value)
    {
        throw_on_error(sqlite3_bind_double(m_stmt, i, value));
    }
    void bind(size_t i, std::string const &value)
    {
        throw_on_error(sqlite3_bind_text(m_stmt, i, value.c_str(), -1, nullptr));
    }

    void extract_column(size_t i, int &output)
    {
        throw_on_no_row();
        output = sqlite3_column_int(m_stmt, i);
    }

    void extract_column(size_t i, long long &output)
    {
        throw_on_no_row();
        output = sqlite3_column_int64(m_stmt, i);
    }

    void extract_column(size_t i, float &output)
    {
        throw_on_no_row();
        output = sqlite3_column_double(m_stmt, i);
    }

    void extract_column(size_t i, double &output)
    {
        throw_on_no_row();
        output = sqlite3_column_double(m_stmt, i);
    }

    void extract_column(size_t i, std::string &output)
    {
        throw_on_no_row();
        output = reinterpret_cast<const char *>(sqlite3_column_text(m_stmt, i));
    }

    bool step()
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

    void reset()
    {
        int rc = sqlite3_reset(m_stmt);
        if (is_error_code(rc))
        {
            throw database_exception(sqlite3_errstr(rc));
        }
        rc = sqlite3_clear_bindings(m_stmt);
        if (is_error_code(rc))
        {
            throw database_exception(sqlite3_errstr(rc));
        }
    }

    bool has_row() const
    {
        return m_has_row;
    }

    operator sqlite3_stmt *()
    {
        return m_stmt;
    }

    static std::shared_ptr<prepared_statement> create()
    {
        return std::make_shared<prepared_statement>();
    }
};

struct idatabase_query
{
    virtual ~idatabase_query() = default;
    virtual const char *sql(void) const = 0;
    virtual void execute(std::shared_ptr<prepared_statement> stmt)
    {
        stmt->step();
    };
};

class database_connection
{
private:
    std::string m_db_name;
    sqlite3 *m_db = nullptr;
    bool m_is_open = false;

public:
    explicit database_connection(std::string name = ":memory:") : m_db_name(name)
    {
        m_is_open = (sqlite3_open(m_db_name.c_str(), &m_db) == SQLITE_OK);
    }

    virtual ~database_connection()
    {
        if (m_is_open)
        {
            sqlite3_close_v2(m_db);
        }
    }

    database_connection(database_connection &) = delete;
    database_connection &operator=(database_connection &) = delete;

    database_connection(database_connection &&other) = default;
    database_connection &operator=(database_connection &&other) = default;

    void execute_query(std::shared_ptr<idatabase_query> query)
    {
        execute_query(*query);
    }

    void execute_query(idatabase_query &query)
    {
        if (!m_is_open)
        {
            throw database_exception("Database is not open");
        }

        auto prepared = prepared_statement::create();

        prepared->prepare(m_db, query.sql());

        query.execute(prepared);
    }

    bool is_open() const
    {
        return m_is_open;
    }

    explicit operator sqlite3 *()
    {
        return m_db;
    }

    operator bool()
    {
        return m_is_open;
    }
};

class database_transaction
{
private:
    std::weak_ptr<database_connection> m_db;
    bool m_has_caught_exception = false;

    void execute_sql(const char *sql)
    {
        std::shared_ptr<database_connection> db;
        if (db = m_db.lock())
        {
            char *err = nullptr;
            sqlite3 *db_ptr = (sqlite3 *)(*db);
            int rc = sqlite3_exec(db_ptr, sql, nullptr, nullptr, &err);

            if (is_error_code(rc))
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

    void start_transaction()
    {
        execute_sql("BEGIN TRANSACTION");
    }

    void end_transaction()
    {
        execute_sql("END TRANSACTION");
    }

    void rollback_transaction()
    {
        execute_sql("ROLLBACK TRANSACTION");
    }

public:
    database_transaction(std::shared_ptr<database_connection> db) : m_db(db)
    {
        start_transaction();
    }

    void execute_query(idatabase_query &q)
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

    virtual ~database_transaction()
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
};
} // namespace sqlite_connect

struct create_table_query : public sqlite_connect::idatabase_query
{
    const char *sql() const override
    {
        return "CREATE TABLE IF NOT EXISTS tab ( x INTEGER, y REAL )";
    }
};

struct insert_query : public sqlite_connect::idatabase_query
{
    const char *sql() const override
    {
        return "INSERT OR IGNORE INTO tab (x, y) VALUES (32, 2.3), (42, 2.7)";
    }
};

struct select_query : public sqlite_connect::idatabase_query
{

    struct record
    {
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
            stmt->extract_column(0, r.x);
            stmt->extract_column(1, r.y);
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
        std::cout << "record: "
                  << "\nx: " << r.x << " \ny: " << r.y << "\n";
    }

    return 0;
}
