
#pragma once

#include <memory>
#include "prepared_statement.hpp"

namespace sqlite_connect {

struct idatabase_query
{
    virtual ~idatabase_query() = default;
    virtual const char *sql(void) const = 0;
    virtual void execute(std::shared_ptr<prepared_statement> stmt);
};

}; // namespace sqlite_connect
