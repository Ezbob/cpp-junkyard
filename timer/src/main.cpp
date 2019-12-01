#include <iostream>
#include <functional>
#include "asio.hpp"

class Printer {
    asio::io_context::strand strand_;
    asio::steady_timer timer1_;
    asio::steady_timer timer2_;
    int count_;

public:
    Printer(asio::io_context &io)
    : strand_(io)
    , timer1_(io, asio::chrono::seconds(1))
    , timer2_(io, asio::chrono::seconds(1))
    , count_(0)
    {
        timer1_.async_wait(asio::bind_executor(strand_, [this](const asio::error_code &) {
            print1();
        }));

        timer2_.async_wait(asio::bind_executor(strand_, [this](const asio::error_code &) {
            print2();
        }));
    }

    ~Printer() {
        std::cout << "Final count is " << count_ << std::endl;
    }

    void print1() {
        if (count_ < 10) {
            std::cout << "Timer 1: " << count_ << std::endl;
            ++count_;

            timer1_.expires_at(timer1_.expiry() + asio::chrono::seconds(1));
            auto stand_executor = asio::bind_executor(strand_, [this](const asio::error_code &) {
                print1();
            });
            timer1_.async_wait(stand_executor);
        }
    }

    void print2() {
        if (count_ < 10) {
            std::cout << "Timer 2: " << count_ << std::endl;
            ++count_;

            timer2_.expires_at(timer2_.expiry() + asio::chrono::seconds(1));
            auto stand_executor = asio::bind_executor(strand_, [this](const asio::error_code &) {
                print2();
            });
            timer2_.async_wait(stand_executor);
        }
    }
};


int main() {
    asio::io_context io;
    Printer p(io);

    std::thread t([&io]() {
        io.run();
    });

    io.run();

    t.join();
    return 0;
}
