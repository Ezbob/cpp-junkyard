#include <iostream>

#include "gtest/gtest.h"
#include "lin_alg.hpp"

TEST( vector_test, vector_initialization_with_single_scalar ) {
    auto scalarIniter = 2.;
    auto vec = LinAlg::VecR3::initWith(scalarIniter);

    ASSERT_EQ(vec[0], scalarIniter);
    ASSERT_EQ(vec[1], scalarIniter);
    ASSERT_EQ(vec[2], scalarIniter);
}


TEST( vector_test, vector_initialization_with_zeroes ) {
    auto vec = LinAlg::VecR3::zeroes();

    ASSERT_EQ(vec[0], 0);
    ASSERT_EQ(vec[1], 0);
    ASSERT_EQ(vec[2], 0);
}


TEST( vector_test, vector_initialization_with_ones ) {
    auto vec = LinAlg::VecR3::ones();

    ASSERT_EQ(vec[0], 1);
    ASSERT_EQ(vec[1], 1);
    ASSERT_EQ(vec[2], 1);
}

TEST( vector_test, vector_vector_addition_with_operator ) {

    auto vec = LinAlg::VecR2({2., 3.});
    auto vec2 = LinAlg::VecR2({1., 2.});

    auto result = vec + vec2;

    ASSERT_TRUE(result[0] == 3);
    ASSERT_TRUE(result[1] == 5);
}

TEST( vector_test, vector_scalar_addition_with_operator ) {

    auto vec = LinAlg::VecR2({2., 3.});
    auto scalar = 3.;

    auto result = vec + scalar;

    ASSERT_TRUE(result[0] == 5);
    ASSERT_TRUE(result[1] == 6);
}

TEST( vector_test, vector_vector_subtraction_with_operator ) {

    auto vec = LinAlg::VecR2({2., 3.});
    auto vec2 = LinAlg::VecR2({1., 2.});

    auto result = vec - vec2;

    ASSERT_TRUE(result[0] == 1);
    ASSERT_TRUE(result[1] == 1);
}

TEST( vector_test, vector_scalar_subtraction_with_operator ) {

    auto vec = LinAlg::VecR2({2., 3.});
    auto scalar = 3.;

    auto result = vec - scalar;

    ASSERT_TRUE(result[0] == -1);
    ASSERT_TRUE(result[1] == 0);
}

TEST( vector_test, vector_vector_multiplication_with_operator ) {

    auto vec = LinAlg::VecR2({2., 3.});
    auto vec2 = LinAlg::VecR2({1., 2.});

    auto result = vec * vec2;

    ASSERT_TRUE(result[0] == 2);
    ASSERT_TRUE(result[1] == 6);
}

TEST( vector_test, vector_scalar_multiplication_with_operator ) {

    auto vec = LinAlg::VecR2({2., 3.});
    auto scalar = 2.;

    auto result = vec * scalar;

    ASSERT_TRUE(result[0] == 4);
    ASSERT_TRUE(result[1] == 6);
}

TEST(  vector_test, vector_scalar_division_with_operator ) {

    auto vec = LinAlg::VecR2({2., 3.});
    auto scalar = 2.;

    auto result = vec / scalar;

    ASSERT_TRUE(result[0] == 1);
    ASSERT_TRUE(result[1] == 1.5);
}

TEST( vector_test, vector_magnitude ) {

    auto vec = LinAlg::VecR2({4., 3.});
    auto result = vec.mag();

    ASSERT_TRUE(result == 5.);
}

TEST( vector_test, vector_2d_cross ) {

    auto vec = LinAlg::VecR2({4., 3.});
    auto vec2 = LinAlg::VecR2({1., 2.});
    
    auto result = vec.cross(vec2);

    auto expected = 5;
    ASSERT_EQ(result, expected);
}

TEST( vector_test, vector_3d_cross ) {

    auto vec = LinAlg::VecR3({4., 3., 1.});
    auto vec2 = LinAlg::VecR3({1., 2., 2.});
    auto result = vec.cross(vec2);

    auto expected = LinAlg::VecR3({4., -7., 5.});

    ASSERT_EQ(result, expected);
}
