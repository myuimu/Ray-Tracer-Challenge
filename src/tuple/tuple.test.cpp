#define BOOST_TEST_MODULE tuple test
#include <boost/test/included/unit_test.hpp>
#include "tuple/tuple.h"

using namespace ray;

BOOST_AUTO_TEST_CASE(isPointTest) {
    auto a = tuple(4.3, -4.2, 3.1, 1.0);

    BOOST_CHECK_EQUAL(a.getX(), 4.3);
    BOOST_CHECK_EQUAL(a.getY(), -4.2);
    BOOST_CHECK_EQUAL(a.getZ(), 3.1);
    BOOST_CHECK_EQUAL(a.getW(), 1.0);
    BOOST_CHECK_EQUAL(a.isPoint(), true);
    BOOST_CHECK_EQUAL(a.isVector(), false);
}

BOOST_AUTO_TEST_CASE(isVectorTest) {
    auto a = tuple(4.3, -4.2, 3.1, 0.0);

    BOOST_CHECK_EQUAL(a.getX(), 4.3);
    BOOST_CHECK_EQUAL(a.getY(), -4.2);
    BOOST_CHECK_EQUAL(a.getZ(), 3.1);
    BOOST_CHECK_EQUAL(a.getW(), 0.0);
    BOOST_CHECK_EQUAL(a.isPoint(), false);
    BOOST_CHECK_EQUAL(a.isVector(), true);
}

BOOST_AUTO_TEST_CASE(pointGeneratorTest) {
    auto a = point(4.0, -4.0, 3.0);

    BOOST_CHECK_EQUAL(a, tuple(4.0, -4.0, 3.0, 1.0));
}

BOOST_AUTO_TEST_CASE(vectorGeneratorTest) {
    auto a = vector(4.0, -4.0, 3.0);

    BOOST_CHECK_EQUAL(a, tuple(4.0, -4.0, 3.0, 0.0));
}