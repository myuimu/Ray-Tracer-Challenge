#include <boost/test/unit_test.hpp>
#include "color/color.h"
#include "ray_tracer.h"

using namespace rayTracer;

BOOST_AUTO_TEST_SUITE(colorTest)

/*-----CONSTRUCTOR TESTS-----*/

BOOST_AUTO_TEST_CASE(colorConstructor) {
    auto c = color(-0.5, 0.4, 1.7);

    BOOST_CHECK_EQUAL(equalWithError(c.getRed(), -0.5), true);
    BOOST_CHECK_EQUAL(equalWithError(c.getGreen(), 0.4), true);
    BOOST_CHECK_EQUAL(equalWithError(c.getBlue(), 1.7), true);
}

/*-----OPERATOR TESTS-----*/

BOOST_AUTO_TEST_CASE(addColors) {
    auto c1 = color(0.9, 0.6, 0.75);
    auto c2 = color(0.7, 0.1, 0.25);

    BOOST_CHECK_EQUAL(c1 + c2, color(1.6, 0.7, 1));
}

BOOST_AUTO_TEST_CASE(subtractColors) {
    auto c1 = color(0.9, 0.6, 0.75);
    auto c2 = color(0.7, 0.1, 0.25);

    BOOST_CHECK_EQUAL(c1 - c2, color(0.2, 0.5, 0.5));
}

BOOST_AUTO_TEST_CASE(multiplyColorAndScalar) {
    auto c1 = color(0.2, 0.3, 0.4);

    BOOST_CHECK_EQUAL(c1 * 2, color(0.4, 0.6, 0.8));
}

BOOST_AUTO_TEST_CASE(multiplyColors) {
    auto c1 = color(1, 0.2, 0.4);
    auto c2 = color(0.9, 1, 0.1);

    BOOST_CHECK_EQUAL(c1 * c2, color(0.9, 0.2, 0.04));
}

BOOST_AUTO_TEST_SUITE_END()