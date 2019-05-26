#include <iostream>
#include "linAlg.hpp"

int main() {
    using namespace LinAlg;

    constexpr auto v = VecR2::ones();
    constexpr auto v2 = VecR2({3., 2.});

    constexpr auto vv4 = VecR<4>::ones();

    std::cout << v << std::endl;
    constexpr auto v3 = v + v2;

    static_assert(v3.dimension == 2, "Hello?");
    static_assert(vv4.dimension == 4, "What?");

    auto v4 = v2 * 2;

    std::cout << v3 << std::endl;
    std::cout << v2 << std::endl;
    std::cout << v4 << std::endl;

    std::cout << v3.dot(v4) << std::endl;

    auto normed = v3.norm();
    std::cout << normed << std::endl;

    std::cout << v3.mul(v3) << std::endl;

    constexpr auto mv = VecR2();

    std::cout << mv[0] << std::endl;

    return 0;
}