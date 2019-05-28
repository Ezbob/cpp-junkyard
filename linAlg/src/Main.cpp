#include "LinAlg.hpp"
#include <iostream>

int main() {
    auto v = LinAlg::VecR2({2., 3.});    
    auto v2 = LinAlg::VecR2({2., 3.});

    std::cout << "Is the same?? " << (v == v2) << std::endl; 

    return 0;
}