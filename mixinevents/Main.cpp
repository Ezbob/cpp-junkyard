
#include <iostream>
#include <functional>

#include "Signal.hpp"
#include "Resource.hpp"
#include "ResourceFetcher.hpp"

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

int main() {
    //std::cout << "Hello world" << std::endl;

    connectStuff();

    A a;

    g_sig.connect([&a](int p) { a.method(p); });

    g_sig.connect(what);

    g_sig.emit(32);

    ResourceFetcher fetcher; // persistence fetcher
    Resource &resource = fetcher; // fetcher is a implementor where Resource is common interface

    auto f = [](const Resource &a) {
        std::cout << "Hello! " << a.stuff << ", " << a.blah << "\n";
    };

    resource.on_ready(f);

    resource.get(); // should be non-blocking

    return 0;
}