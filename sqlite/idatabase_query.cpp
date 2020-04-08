
#include "idatabase_query.hpp"

using namespace sqlite_connect;

void idatabase_query::execute(std::shared_ptr<prepared_statement> stmt)
{
    stmt->step();
};