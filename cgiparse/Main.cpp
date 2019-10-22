#include <iostream>
#include "Cgiparse.hpp"

std::string getter(const std::string &key) {
    if (key == "done") {
        return "1234";
    } else if (key == "blu") {
        return "120";
    } else if (key == "d") {
        return "-1";
    } else if (key == "blah") {
        return "2.3";
    } else if (key == "str") {
        return "blah blah";
    } else if (key == "llll") {
        return "";
    } else if (key == "lol") {
        return "1,3,4";
    } else if (key == "lul") {
        return "1.2,4.1,5.1";
    }
    return std::string(key);
}

struct CgiArguments : public cgiparse::CgiInputParser<> {
    uint16_t a;
    uint8_t c;
    int32_t d;
    double m;
    std::string b;
    std::vector<int> o;
    std::vector<float> fs;

    int64_t l = 30;

    void Parse(cgiparse::Getter_t &getter) {
        cgiInput(getter, a,  "done");
        cgiInput(getter, c, "blu");
        cgiInput(getter, d, "d");
        cgiInput(getter, m, "blah");
        cgiInput(getter, b, "str");
        cgiInput(getter, o, "lol");
        cgiInput(getter, fs, "lul");
        cgiInputOptional(getter, l, "llll");
    }
};

int main(int argc, char **argv) {

    CgiArguments args;
    args.GetCgiArgs(getter);

    if (args.HasErrors()) {
        std::cout << "cgi has errors" << std::endl;

        auto errors = args.getErrors();
        for (auto error : errors) {
            std::cout << error.first << "<->" << std::endl;
        }
    } else {
        std::cout << "hello a: " << args.a << "\n";
        std::cout << "hello c: " << args.c << "\n";
        std::cout << "hello d: " << args.d << "\n";
        std::cout << "hello m: " << args.m << "\n";
        std::cout << "hello llll: " << args.l << "\n";

        std::cout << "From o:\n";
        for (const auto &l : args.o) {
            std::cout << l << "\n";
        }

        std::cout << "From o:\n";
        for (const auto &l : args.fs) {
            std::cout << l << "\n";
        }
    }

    return 0;
}

