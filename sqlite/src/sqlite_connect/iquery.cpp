
#include "iquery.hpp"

using namespace sqlite_connect;

void iquery::execute(std::shared_ptr<prepared_statement> stmt)
{
    stmt->step();
};

bool iquery::is_cached(void) const {
    return m_cached != nullptr;
}

void iquery::cache(statement_ptr ptr) {
    m_cached = ptr;
}

auto iquery::cache(void) -> statement_ptr {
    return m_cached;
}
