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
    }
    return std::string(key);
}

struct CgiArguments : public cgiparse::CgiInputParser<> {
    uint16_t a;
    uint8_t c;
    int32_t d;
    double m;
    std::string b;

    int64_t l = 30;

    void Parse(cgiparse::Getter_t &getter) {
        cgiInput(getter, a,  "done");
        cgiInput(getter, c, "blu");
        cgiInput(getter, d, "d");
        cgiInput(getter, m, "blah");
        cgiInput(getter, b, "str");
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
            std::cout << error.first << "<->" << static_cast<uint32_t>(error.second) << std::endl;
        }
    } else {
        std::cout << "hello a: " << args.a << "\n";
        std::cout << "hello c: " << args.c << "\n";
        std::cout << "hello d: " << args.d << "\n";
        std::cout << "hello m: " << args.m << "\n";
        std::cout << "hello llll: " << args.l << "\n";
    }

    return 0;
}

