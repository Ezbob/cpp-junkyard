#include <iostream>
#include <sstream>

class CustomBuf : public std::basic_stringbuf<char> {
protected:
    virtual int sync() {
        std::cout << "From buffer: " << str() << std::endl;
        return 0;
    }
};


int main(int argc, char const *argv[]) {

    std::cout << "Hello world!" << std::endl;

    CustomBuf buf;

    std::ostream c(&buf);
    std::istream i(&buf);

    c << "hello\n";

    c.flush();

    c << "hello2\n";

    return 0;
}
