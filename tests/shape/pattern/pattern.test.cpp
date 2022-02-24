#include <boost/test/unit_test.hpp>
#include "ray_tracer.h"

using namespace rayTracer;

BOOST_AUTO_TEST_SUITE(patternTest)

BOOST_AUTO_TEST_CASE(stripeWithObjectTransformation) {
    auto p = stripe(WHITE, BLACK);
    auto s = sphere(scaling(2, 2, 2), material());

    BOOST_CHECK_EQUAL(p.getColorForShape(s, point(1.5, 0, 0)), WHITE);
}

BOOST_AUTO_TEST_CASE(stripeWithPatternTransformation) {
    auto p = stripe(WHITE, BLACK, scaling(2, 2, 2));
    auto s = sphere();

    BOOST_CHECK_EQUAL(p.getColorForShape(s, point(1.5, 0, 0)), WHITE);
}

BOOST_AUTO_TEST_CASE(stripeWithPatternAndObjectTransformation) {
    auto p = stripe(WHITE, BLACK, translation(0.5, 0, 0));
    auto s = sphere(scaling(2, 2, 2), material());

    BOOST_CHECK_EQUAL(p.getColorForShape(s, point(2.5, 0, 0)), WHITE);
}

BOOST_AUTO_TEST_CASE(gradientTest) {
    auto p = gradient(WHITE, BLACK);
    auto s = sphere();

    BOOST_CHECK_EQUAL(p.getColorForShape(s, point(0, 0, 0)), WHITE);
    BOOST_CHECK_EQUAL(p.getColorForShape(s, point(0.25, 0, 0)), color(0.75, 0.75, 0.75));
    BOOST_CHECK_EQUAL(p.getColorForShape(s, point(0.5, 0, 0)), color(0.5, 0.5, 0.5));
    BOOST_CHECK_EQUAL(p.getColorForShape(s, point(0.75, 0, 0)), color(0.25, 0.25, 0.25));
}

BOOST_AUTO_TEST_CASE(ringTest) {
    auto p = ring(WHITE, BLACK);
    auto s = sphere();

    BOOST_CHECK_EQUAL(p.getColorForShape(s, point(0, 0, 0)), WHITE);
    BOOST_CHECK_EQUAL(p.getColorForShape(s, point(1, 0, 0)), BLACK);
    BOOST_CHECK_EQUAL(p.getColorForShape(s, point(0, 0, 1)), BLACK);
    BOOST_CHECK_EQUAL(p.getColorForShape(s, point(0.708, 0, 0.708)), BLACK);
}

BOOST_AUTO_TEST_CASE(checkerTest) {
    auto p = checker(WHITE, BLACK);
    auto s = sphere();

    BOOST_CHECK_EQUAL(p.getColorForShape(s, point(0, 0, 0)), WHITE);
    BOOST_CHECK_EQUAL(p.getColorForShape(s, point(0.99, 0, 0)), WHITE);
    BOOST_CHECK_EQUAL(p.getColorForShape(s, point(1.01, 0, 0)), BLACK);
    BOOST_CHECK_EQUAL(p.getColorForShape(s, point(0, 0, 0)), WHITE);
    BOOST_CHECK_EQUAL(p.getColorForShape(s, point(0, 0.99, 0)), WHITE);
    BOOST_CHECK_EQUAL(p.getColorForShape(s, point(0, 1.01, 0)), BLACK);
    BOOST_CHECK_EQUAL(p.getColorForShape(s, point(0, 0, 0)), WHITE);
    BOOST_CHECK_EQUAL(p.getColorForShape(s, point(0, 0, 0.99)), WHITE);
    BOOST_CHECK_EQUAL(p.getColorForShape(s, point(0, 0, 1.01)), BLACK);
}

BOOST_AUTO_TEST_SUITE_END()