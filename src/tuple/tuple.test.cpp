#include <boost/test/unit_test.hpp>
#include "tuple/tuple.h"

using namespace ray;

BOOST_AUTO_TEST_SUITE(tupleTest)

/*-----CONSTRUCTOR TESTS-----*/

// A tuple with w=1.0 is a point
BOOST_AUTO_TEST_CASE(isPoint) {
    auto a = tuple(4.3, -4.2, 3.1, 1);

    BOOST_CHECK_EQUAL(a.getX(), 4.3);
    BOOST_CHECK_EQUAL(a.getY(), -4.2);
    BOOST_CHECK_EQUAL(a.getZ(), 3.1);
    BOOST_CHECK_EQUAL(a.getW(), 1);
    BOOST_CHECK_EQUAL(a.isPoint(), true);
    BOOST_CHECK_EQUAL(a.isVector(), false);
}

// A tuple with w=0 is a vector
BOOST_AUTO_TEST_CASE(isVector) {
    auto a = tuple(4.3, -4.2, 3.1, 0);

    BOOST_CHECK_EQUAL(a.getX(), 4.3);
    BOOST_CHECK_EQUAL(a.getY(), -4.2);
    BOOST_CHECK_EQUAL(a.getZ(), 3.1);
    BOOST_CHECK_EQUAL(a.getW(), 0);
    BOOST_CHECK_EQUAL(a.isPoint(), false);
    BOOST_CHECK_EQUAL(a.isVector(), true);
}

// point() creates tuples with w=1
BOOST_AUTO_TEST_CASE(pointGenerator) {
    auto p = point(4, -4, 3);

    BOOST_CHECK_EQUAL(p, tuple(4, -4, 3, 1));
}

// point() creates tuples with w=0
BOOST_AUTO_TEST_CASE(vectorGenerator) {
    auto v = vector(4, -4, 3);

    BOOST_CHECK_EQUAL(v, tuple(4, -4, 3, 0));
}

/*-----OPERATOR TESTS-----*/

// Adding two tuples
BOOST_AUTO_TEST_CASE(tupleAdd) {
    auto a1 = tuple(3, -2, 5, 1);
    auto a2 = tuple(-2, 3, 1, 0);

    BOOST_CHECK_EQUAL(a1 + a2, tuple(1, 1, 6, 1));
}

// Subtracting two points
BOOST_AUTO_TEST_CASE(pointSubtract) {
    auto p1 = point(3, 2, 1);
    auto p2 = point(5, 6, 7);

    BOOST_CHECK_EQUAL(p1 - p2, vector(-2, -4, -6));
}

// Subtracting a vector from a point
BOOST_AUTO_TEST_CASE(tupleMinusVector) {
    auto p = point(3, 2, 1);
    auto v = vector(5, 6, 7);

    BOOST_CHECK_EQUAL(p - v, point(-2, -4, -6));
}

// Subtracting two vectors
BOOST_AUTO_TEST_CASE(vectorSubtract) {
    auto v1 = vector(3, 2, 1);
    auto v2 = vector(5, 6, 7);

    BOOST_CHECK_EQUAL(v1 - v2, vector(-2, -4, -6));
}

// Subtracting a vector from the zero vector
BOOST_AUTO_TEST_CASE(zeroMinusVector) {
    auto zero = vector(0, 0, 0);
    auto v = vector(1, -2, 3);

    BOOST_CHECK_EQUAL(zero - v, vector(-1, 2, -3));
}

// Negating a tuple
BOOST_AUTO_TEST_CASE(negateTuple) {
    auto a = tuple(1, -2, 3, -4);

    BOOST_CHECK_EQUAL(-a, tuple(-1, 2, -3, 4));
}

// Multiplying a tuple by a scalar
BOOST_AUTO_TEST_CASE(tupleScalarMultiply) {
    auto a = tuple(1, -2, 3, -4);

    BOOST_CHECK_EQUAL(a * 3.5, tuple(3.5, -7, 10.5, -14));
}

// Multiplying a tuple by a fraction
BOOST_AUTO_TEST_CASE(tupleFractionMultiply) {
    auto a = tuple(1, -2, 3, -4);

    BOOST_CHECK_EQUAL(a * 0.5, tuple(0.5, -1, 1.5, -2));
}

// Dividing a tuple by a scalar
BOOST_AUTO_TEST_CASE(tupleScalarDivide) {
    auto a = tuple(1, -2, 3, -4);

    BOOST_CHECK_EQUAL(a / 2, tuple(0.5, -1, 1.5, -2));
}

/*-----VECTOR COMPUTATION TESTS-----*/

BOOST_AUTO_TEST_CASE(xMagnitute) {
    auto v = vector(1, 0, 0);

    BOOST_CHECK_EQUAL(v.getMagnitude(), 1);
}

BOOST_AUTO_TEST_CASE(yMagnitute) {
    auto v = vector(0, 1, 0);

    BOOST_CHECK_EQUAL(v.getMagnitude(), 1);
}

BOOST_AUTO_TEST_CASE(zMagnitute) {
    auto v = vector(0, 0, 1);

    BOOST_CHECK_EQUAL(v.getMagnitude(), 1);
}

BOOST_AUTO_TEST_CASE(positiveMagnitude) {
    auto v = vector(1, 2, 3);

    BOOST_CHECK_EQUAL(v.getMagnitude(), sqrt(14));
}

BOOST_AUTO_TEST_CASE(negativeMagnitude) {
    auto v = vector(-1, -2, -3);

    BOOST_CHECK_EQUAL(v.getMagnitude(), sqrt(14));
}

BOOST_AUTO_TEST_CASE(normalizeXOnlyVector) {
    auto v = vector(4, 0, 0);

    BOOST_CHECK_EQUAL(v.normalized(), vector(1, 0, 0));
}

BOOST_AUTO_TEST_CASE(normalizeXYZVector) {
    auto v = vector(1, 2, 3);

    BOOST_CHECK_EQUAL(v.normalized(), vector(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14)));
}

BOOST_AUTO_TEST_CASE(normalizedVectorMagnitude) {
    auto v = vector(1, 2, 3);

    BOOST_CHECK_EQUAL(v.normalized().getMagnitude(), 1);
}

/*-----VECTOR PRODUCT TESTS-----*/

BOOST_AUTO_TEST_CASE(dotProduct) {
    auto a = vector(1, 2, 3);
    auto b = vector(2, 3, 4);

    BOOST_CHECK_EQUAL(a.dot(b), 20);
}

BOOST_AUTO_TEST_CASE(crossProduct) {
    auto a = vector(1, 2, 3);
    auto b = vector(2, 3, 4);

    BOOST_CHECK_EQUAL(a.cross(b), vector(-1, 2, -1));
    BOOST_CHECK_EQUAL(b.cross(a), vector(1, -2, 1));
}

BOOST_AUTO_TEST_SUITE_END()