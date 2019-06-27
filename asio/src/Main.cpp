#include <iostream>
#include "asio.hpp"

void print(const asio::error_code &e [[maybe_unused]]) {
    std::cout << "Hello, world!\n";
}

int main(int argc, char const *argv[])
{
    asio::io_context io;
    asio::steady_timer t(io, asio::chrono::seconds(5));

    t.async_wait(&print);
    std::cout << "What? ";
    io.run();

    return 0;
}
