#include <iostream>

import MyModule;


int main(int argc, char const *argv[])
{
    int a = 32;

    std::cout << "------- blah " << L::f(a) << std::endl;
    return 0;
}

