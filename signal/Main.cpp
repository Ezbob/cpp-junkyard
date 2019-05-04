
#include <iostream>
#include <functional>
#include "signals.hpp"

SignalSlot<> g_sig;

class A {

    std::string name;

    void bindable() {
        std::cout << "Hi from " << name << std::endl;
    }

public:

    A(std::string &&name) : name(name) {
        g_sig.bind("fix", std::bind(bindable, this));
    }
};

class B {

    std::string name;

    void bindable() {
        std::cout << "Greetings from " << name << std::endl;
    }

public:

    B(std::string &&name) : name(name) {
        g_sig.bind("fix", std::bind(bindable, this));
    }
};


int main() {
    //std::cout << "Hello world" << std::endl;

    A a("A1");
    A a2("A2");
    A a3("A3");

    B b1("B1");
    B b2("B2");

    g_sig.emit("fix");

    SignalSlot<int> sig1;

    std::string buffer = "hello";

    sig1.bind("fun", [&buffer](int a) {
        buffer += " would " + std::to_string(a);
    });

    std::cout << buffer << std::endl;
    sig1.emit("fun", 0);
    std::cout << buffer << std::endl;
    sig1.emit("fun", 0);
    std::cout << buffer << std::endl;

    sig1.emit("fun", 10);

    sig1.emit("no", 0);

    std::cout << buffer << std::endl;

    return 0;
}