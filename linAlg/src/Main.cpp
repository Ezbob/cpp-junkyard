
#define CATCH_CONFIG_MAIN
#include "test/Catch2.hpp"
#include <iostream>
#include "linAlg.hpp"

TEST_CASE( "Vector initialization with single scalar", "[vec.initWith]" ) {
    auto scalarIniter = 2.;
    auto vec = LinAlg::VecR3::initWith(scalarIniter);

    REQUIRE(vec[0] == scalarIniter);
    REQUIRE(vec[1] == scalarIniter);
    REQUIRE(vec[2] == scalarIniter);
}


TEST_CASE( "Vector initialization with zeroes", "[vec.zeroes]" ) {
    auto vec = LinAlg::VecR3::zeroes();

    REQUIRE(vec[0] == 0);
    REQUIRE(vec[1] == 0);
    REQUIRE(vec[2] == 0);
}


TEST_CASE( "Vector initialization with ones", "[vec.ones]" ) {
    auto vec = LinAlg::VecR3::ones();

    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 1);
    REQUIRE(vec[2] == 1);
}


TEST_CASE( "Vector-vector addition", "[vec.add]" ) {

    auto vec = LinAlg::VecR2({2., 3.});
    auto vec2 = LinAlg::VecR2({1., 2.});

    auto result = vec.add(vec2);

    REQUIRE(result[0] == 3);
    REQUIRE(result[1] == 5);
}

TEST_CASE( "Vector-vector addition with operator", "[vec.+]" ) {

    auto vec = LinAlg::VecR2({2., 3.});
    auto vec2 = LinAlg::VecR2({1., 2.});

    auto result = vec + vec2;

    REQUIRE(result[0] == 3);
    REQUIRE(result[1] == 5);
}

TEST_CASE( "Vector-scalar addition", "[vec.add]" ) {

    auto vec = LinAlg::VecR2({2., 3.});
    auto scalar = 3.;

    auto result = vec.add(scalar);

    REQUIRE(result[0] == 5);
    REQUIRE(result[1] == 6);
}


TEST_CASE( "Vector-scalar addition with operator", "[vec.+]" ) {

    auto vec = LinAlg::VecR2({2., 3.});
    auto scalar = 3.;

    auto result = vec + scalar;

    REQUIRE(result[0] == 5);
    REQUIRE(result[1] == 6);
}


TEST_CASE( "Vector-vector subtraction", "[vec.sub]" ) {

    auto vec = LinAlg::VecR2({2., 3.});
    auto vec2 = LinAlg::VecR2({1., 2.});

    auto result = vec.sub(vec2);

    REQUIRE(result[0] == 1);
    REQUIRE(result[1] == 1);
}


TEST_CASE( "Vector-vector subtraction with operator", "[vec.-]" ) {

    auto vec = LinAlg::VecR2({2., 3.});
    auto vec2 = LinAlg::VecR2({1., 2.});

    auto result = vec - vec2;

    REQUIRE(result[0] == 1);
    REQUIRE(result[1] == 1);
}


TEST_CASE( "Vector-scalar subtraction", "[vec.sub]" ) {

    auto vec = LinAlg::VecR2({2., 3.});
    auto scalar = 3.;

    auto result = vec.sub(scalar);

    REQUIRE(result[0] == -1.);
    REQUIRE(result[1] == 0);
}


TEST_CASE( "Vector-scalar subtraction with operator", "[vec.-]" ) {

    auto vec = LinAlg::VecR2({2., 3.});
    auto scalar = 3.;

    auto result = vec - scalar;

    REQUIRE(result[0] == -1);
    REQUIRE(result[1] == 0);
}


TEST_CASE( "Vector-vector multiplication", "[vec.mul]" ) {

    auto vec = LinAlg::VecR2({2., 3.});
    auto vec2 = LinAlg::VecR2({1., 2.});

    auto result = vec.mul(vec2);

    REQUIRE(result[0] == 2);
    REQUIRE(result[1] == 6);
}


TEST_CASE( "Vector-vector multiplication with operator", "[vec.*]" ) {

    auto vec = LinAlg::VecR2({2., 3.});
    auto vec2 = LinAlg::VecR2({1., 2.});

    auto result = vec * vec2;

    REQUIRE(result[0] == 2);
    REQUIRE(result[1] == 6);
}


TEST_CASE( "Vector-scalar multiplication", "[vec.mul]" ) {

    auto vec = LinAlg::VecR2({2., 3.});
    auto scalar = 2.;

    auto result = vec.mul(scalar);

    REQUIRE(result[0] == 4);
    REQUIRE(result[1] == 6);
}


TEST_CASE( "Vector-scalar multiplication with operator", "[vec.*]" ) {

    auto vec = LinAlg::VecR2({2., 3.});
    auto scalar = 2.;

    auto result = vec * scalar;

    REQUIRE(result[0] == 4);
    REQUIRE(result[1] == 6);
}


TEST_CASE( "Vector-scalar division", "[vec.div]" ) {

    auto vec = LinAlg::VecR2({2., 3.});
    auto scalar = 2.;

    auto result = vec.div(scalar);

    REQUIRE(result[0] == 1);
    REQUIRE(result[1] == 1.5);
}


TEST_CASE( "Vector-scalar division with operator", "[vec./]" ) {

    auto vec = LinAlg::VecR2({2., 3.});
    auto scalar = 2.;

    auto result = vec / scalar;

    REQUIRE(result[0] == 1);
    REQUIRE(result[1] == 1.5);
}


TEST_CASE( "Vector dot product", "[vec.dot]" ) {

    auto vec = LinAlg::VecR2({2., 3.});
    auto vec2 = LinAlg::VecR2({2., 4.});

    auto result = vec.dot(vec2);

    REQUIRE(result == 16.);
}

TEST_CASE( "Vector magnitude", "[vec.mag]" ) {

    auto vec = LinAlg::VecR2({4., 3.});
    auto result = vec.mag();

    REQUIRE(result == 5.);
}
