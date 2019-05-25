#include <iostream>
#include "linAlg.hpp"

int main() {
    auto v = VecR2::one();
    auto v2 = VecR2({3., 2.});

    std::cout << v << std::endl;

    auto v3 = v + v2;

    auto v4 = v2 * 2;

    std::cout << v3 << std::endl;
    std::cout << v2 << std::endl;
    std::cout << v4 << std::endl;

    std::cout << v3.dot(v4) << std::endl;

    auto normed = v3.norm();
    std::cout << normed << std::endl;

    return 0;
}