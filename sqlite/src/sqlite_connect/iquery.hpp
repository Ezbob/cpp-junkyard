
#pragma once

#include <memory>
#include "prepared_statement.hpp"

namespace sqlite_connect
{

struct iquery
{
    using statement_ptr = std::shared_ptr<prepared_statement>;
    virtual ~iquery() = default;
    virtual const char *sql(void) const = 0;
    virtual void execute(statement_ptr stmt);

    bool is_cached(void) const;
    void cache(statement_ptr ptr);
    statement_ptr cache(void);

private:
    std::shared_ptr<prepared_statement> m_cached;
};

}; // namespace sqlite_connect
