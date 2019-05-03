
#include <iostream>
#include "signals.hpp"


int main() {
    std::cout << "Hello world" << std::endl;
    SignalSlot sig;

    std::string buffer = "hello";

    sig.bind("fun", [&buffer](int a) {
        buffer += " would";
    }, 0);

    std::cout << buffer << std::endl;
    sig.emit("fun");
    std::cout << buffer << std::endl;
    sig.emit("fun");
    std::cout << buffer << std::endl;

    sig.emit("no");

    return 0;
}