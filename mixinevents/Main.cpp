
#include <iostream>
#include <functional>
#include <chrono>
#include <thread>
#include "signals.hpp"

Signal<int> g_sig;


class A {
    int b = 32;

public:
    void method(int a) {
        std::cout << "--> " << (a + b) << std::endl;
    }
};

void what(int a) {
    std::cout << "Second " << a << "\n";
}

void connectStuff() {
    auto f = [](int a) {
        std::cout << "Here " << a << std::endl;
    };

    g_sig.connect(f);
}


template<typename Derived_t>
class ReadyEvent {

    Signal<const Derived_t &> m_signal_ready;

protected:
    void _emit_ready() {
        auto r = static_cast<const Derived_t *>(this);
        m_signal_ready.emit(*r);
    }

public:
    ReadyEvent() {}
    virtual ~ReadyEvent() = default;

    void on_ready(std::function<void (const Derived_t &)> &f) {
        m_signal_ready.connect(f);
    }

    void on_ready(std::function<void (const Derived_t &)> &&f) {
        m_signal_ready.connect(f);
    }
};

class AResource : public ReadyEvent<AResource> {

public:
    int stuff = 32;

    void fetch_some_resource() {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        stuff += 2;
        _emit_ready();
    }
};


int main() {
    //std::cout << "Hello world" << std::endl;

    connectStuff();

    A a;

    g_sig.connect([&a](int p) { a.method(p); });

    g_sig.connect(what);

    g_sig.emit(32);

    AResource resource;

    auto f = [](const AResource &a) {
        std::cout << "Hello!" << a.stuff << "\n";
    };

    resource.on_ready(f);

    resource.fetch_some_resource();

    return 0;
}