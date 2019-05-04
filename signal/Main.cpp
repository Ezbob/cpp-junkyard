
#include <iostream>
#include "signals.hpp"


int main() {
    std::cout << "Hello world" << std::endl;
    SignalSlot<int> sig;

    std::string buffer = "hello";

    sig.bind("fun", [&buffer](int a) {
        buffer += " would " + std::to_string(a);
    });

    std::cout << buffer << std::endl;
    sig.emit("fun", 0);
    std::cout << buffer << std::endl;
    sig.emit("fun", 0);
    std::cout << buffer << std::endl;

    sig.emit("fun", 10);

    sig.emit("no", 0);

    std::cout << buffer << std::endl;

    return 0;
}