
#pragma once

#include "sqlite3.h"
#include "database_exception.hpp"
#include <memory>
#include <string>

namespace sqlite_connect {

    class prepared_statement
    {
    private:
        sqlite3_stmt *m_stmt = nullptr;
        bool m_has_row = false;

        void throw_on_no_row(void);

    public:
        prepared_statement() = default;
        virtual ~prepared_statement();

        prepared_statement(prepared_statement &) = delete;
        prepared_statement &operator=(prepared_statement &) = delete;

        prepared_statement(prepared_statement &&) = default;
        prepared_statement &operator=(prepared_statement &&) = default;

        void prepare(sqlite3 *db, const char *sql, const char **more = nullptr);

        void bind(size_t i, int value);
        void bind(size_t i, long long value);
        void bind(size_t i, double value);
        void bind(size_t i, float value);
        void bind(size_t i, std::string const &value);

        void extract_column(size_t i, int &output);

        void extract_column(size_t i, long long &output);

        void extract_column(size_t i, float &output);
        void extract_column(size_t i, double &output);
        void extract_column(size_t i, std::string &output);

        bool step();

        void reset();

        bool has_row() const;

        operator sqlite3_stmt *();

    };

};

