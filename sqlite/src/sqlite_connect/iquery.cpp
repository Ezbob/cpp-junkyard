
#include "iquery.hpp"

using namespace sqlite_connect;

void iquery::execute(std::shared_ptr<prepared_statement> stmt)
{
    stmt->step();
};