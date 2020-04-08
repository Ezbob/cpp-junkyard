
#include "database_exception.hpp"
#include "sqlite3.h"

using namespace sqlite_connect;


database_exception::database_exception(std::string const &what_arg)
    : std::runtime_error(what_arg)
{
}

database_exception::database_exception(const char *what_arg)
    : std::runtime_error(what_arg)
{
}

bool database_exception::is_error_code(int rc)
{
    return !(SQLITE_DONE == rc || SQLITE_OK == rc || SQLITE_DONE == rc);
}

void database_exception::throw_on_error(int rc)
{
    if (is_error_code(rc))
    {
        throw database_exception(sqlite3_errstr(rc));
    }
}