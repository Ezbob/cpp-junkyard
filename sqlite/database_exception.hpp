
#pragma once

#include <stdexcept>
#include <string>

namespace sqlite_connect {

struct database_exception : std::runtime_error
{
    virtual ~database_exception() = default;
    explicit database_exception(std::string const &what_arg);
    explicit database_exception(const char *what_arg);

    static bool is_error_code(int rc);
    static void throw_on_error(int rc);
};

}; // namespace sqlite_connect
