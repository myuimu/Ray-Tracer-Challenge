#include <boost/test/unit_test.hpp>
#include "intersection/intersection.h"
#include "shape/sphere/sphere.h"

using namespace rayTracer;

BOOST_AUTO_TEST_SUITE(intersectionTest)

BOOST_AUTO_TEST_CASE(intersectionHasTAndObject) {
    auto s = sphere();
    auto i = intersection(3.5, &s);

    BOOST_CHECK_EQUAL(i.getT(), 3.5);
    BOOST_CHECK_EQUAL(i.getObject(), s);
}

BOOST_AUTO_TEST_SUITE_END()