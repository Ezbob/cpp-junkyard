#include <iostream>

#include "gtest/gtest.h"
#include "lin_alg.hpp"


TEST( matrix_test, square_matrix_equality_operator ) {

    auto result = LinAlg::MatR<2>({1., 2., 3., 4.});

    auto expected = LinAlg::MatR<2>({
        1., 2.,
        3., 4.
    });

    ASSERT_EQ(result, expected);
}
/*
TEST( matrix_test, matrix_square_from_3d_vectors ) {

    auto vec = LinAlg::VecR2({4., 3.});
    auto vec2 = LinAlg::VecR2({1., 2.});

    auto result = LinAlg::MatR<2>({vec, vec2});

    auto expected = LinAlg::MatR<2>({
        4., 3.,
        1., 2.
    });

    ASSERT_EQ(result, expected);
}

*/

/*
TEST( matrix_test, square_subtraction_operator ) {

    auto mat = LinAlg::MatR<2>({
        4., 3.,
        1., 2.
    });

    auto mat2 = LinAlg::MatR<2>({
        4., 3.,
        1., 2.
    });

    auto mat3 = LinAlg::MatR<2>({
        4., 1.,
        1., 2.
    });

    auto zeroes = LinAlg::MatR<2>::zeroes();
    auto result = mat - mat2;

    ASSERT_EQ(result, zeroes);

    auto expected = LinAlg::MatR<2>({
        0., 2.,
        0., 0.,
    });
    result = mat - mat3;

    ASSERT_EQ(result, expected);
}
*/

TEST( matrix_test, square_multiplication_operator ) {

    auto mat = LinAlg::MatR<2>({
        4., 3.,
        1., 2.
    });

    auto mat2 = LinAlg::MatR<2>({
        4., 1.,
        1., 2.
    });

    auto expected = LinAlg::MatR<2>({
        19., 10.,
        6., 5.,
    });
    auto result = mat * mat2;

    ASSERT_EQ(result, expected);
}


TEST( matrix_test, square_addition_operator ) {

    auto mat = LinAlg::MatR<2>({
        4., 3.,
        1., 2.
    });

    auto mat2 = LinAlg::MatR<2>({
        4., 1.,
        1., 2.
    });

    auto expected = LinAlg::MatR<2>({
        8., 4.,
        2., 4.,
    });
    auto result = mat + mat2;

    ASSERT_EQ(result, expected);
}

TEST( matrix_test, nonsquare_matrix_equality_operator ) {

    auto mat = LinAlg::MatR<2, 3>({
        4., 3., 3.,
        1., 2., 4.
    });

    auto mat2 = LinAlg::MatR<2, 3>({
        4., 3., 3.,
        1., 2., 4.,
    });

    ASSERT_EQ(mat, mat2);
}


TEST( matrix_test, nonsquare_matrix_not_equality_operator ) {

    auto mat = LinAlg::MatR<2, 3>({
        4., 3., 3.,
        1., 2., 4.
    });

    auto mat2 = LinAlg::MatR<3, 3>({
        4., 1., 3.,
        1., 2., 4.,
        4., 5., 6.,
    });

    ASSERT_NE(mat, mat2);
}


TEST( matrix_test, matrix_nonsquare_from_3d_vectors ) {

    auto vec = LinAlg::VecR3({4., 3., 3.});
    auto vec2 = LinAlg::VecR3({1., 2., 3.});

    auto result = LinAlg::MatR<2, 3>({vec, vec2});

    std::cout << result << "\n";

    auto expected = LinAlg::MatR<2, 3>({
        {4., 3., 3.},
        {1., 2., 3.}
    });

    
    std::cout << expected << "\n";

    ASSERT_EQ(result, expected);
}
