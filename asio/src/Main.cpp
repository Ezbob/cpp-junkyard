#include <iostream>
#include <array>
#include <asio.hpp>
#include <functional>

asio::io_context io;
auto secs = asio::chrono::seconds(2);
asio::steady_timer rt(io, secs);

void print() {
    std::cout << "Hello, world!\n";
}

void runner(const asio::error_code &) {

    print();

    rt.expires_at(rt.expires_at() + secs);
    rt.async_wait(runner);
}

template<
    typename Duration_t = asio::chrono::seconds,
    typename Timer_t = asio::steady_timer,
    typename Callback_t = std::function<void(void)>
>
class RecurringTimer {
    Duration_t duration;
    Timer_t timer;
    Callback_t &callback;

    void runner(const asio::error_code &) {
        callback();
        rt.expires_at(rt.expires_at() + duration);
        rt.async_wait(runner);
    }

public:
    RecurringTimer(Timer_t timer, Duration_t dur, Callback_t callback)
        : duration(dur)
        , timer(timer)
        , callback(callback) {}

    RecurringTimer(asio::io_context &io, Duration_t dur, Callback_t callback)
        : duration(dur)
        , timer(Timer_t(io, dur))
        , callback(callback) {}

    void async_await() {
        timer.async_wait(std::bind(runner, this, std::placeholders::_1));
    }
};


int main(int argc, char const *argv[]) {

    RecurringTimer rt2(io, asio::chrono::seconds(2), print);
    int a[] = {2, 3, 4, 5};

    std::cout << "What? ";

    //rt.async_wait(runner);

    rt2.async_await();

    io.run();

    return 0;
}
