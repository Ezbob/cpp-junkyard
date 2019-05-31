#include "LinAlg.hpp"
#include <iostream>

int main() {
    /*
    constexpr auto v = LinAlg::VecR<6>({2., 3.});
    constexpr auto v2 = LinAlg::VecR<6>({2., 3., 5., 5., 5., 5.});

    std::cout << v << std::endl;
    std::cout << v2 << std::endl;
    std::cout << "Is the same?? " << (v == v2) << std::endl; 

    constexpr auto vv = LinAlg::Vec2<float>({2.2, 2});
    constexpr auto vvv = LinAlg::Vec2<float>({3, 3.2});

    constexpr auto cross = vv.cross(vvv);

    static_assert(cross);

    constexpr auto b = v * cross;

    std::cout << b << std::endl;

    */

    auto m = LinAlg::MatR<3, 3>({
        {1., 2., 3.},
        {4., 5., 5.},
        {2,  1,  3}
    });

    std::cout << m << std::endl;

    auto A = LinAlg::MatR<3, 3>({
        LinAlg::VecR3({2., 2., 1.}),
        LinAlg::VecR3({1., 2., 1.})
    });

    std::cout << A << std::endl;


    return 0;
}