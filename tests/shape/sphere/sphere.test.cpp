#include <boost/test/unit_test.hpp>
#include "shape/sphere/sphere.h"
#include "ray_tracer.h"

using namespace rayTracer;

BOOST_AUTO_TEST_SUITE(sphereTest)

BOOST_AUTO_TEST_CASE(rayIntersectsTwice) {
    auto r = ray(point(0, 0, -5), vector(0, 0, 1));
    auto s = sphere();

    auto intersections = s.getIntersections(r);

    BOOST_CHECK_EQUAL(intersections.size(), 2);
    BOOST_CHECK_EQUAL(equalWithError(intersections[0], 4), true);
    BOOST_CHECK_EQUAL(equalWithError(intersections[1], 6), true);
}

BOOST_AUTO_TEST_CASE(rayIntersectsOnce) {
    auto r = ray(point(0, 1, -5), vector(0, 0, 1));
    auto s = sphere();

    auto intersections = s.getIntersections(r);

    BOOST_CHECK_EQUAL(intersections.size(), 2);
    BOOST_CHECK_EQUAL(equalWithError(intersections[0], 5), true);
    BOOST_CHECK_EQUAL(equalWithError(intersections[1], 5), true);
}

BOOST_AUTO_TEST_CASE(rayDoesNotIntersect) {
    auto r = ray(point(0, 2, -5), vector(0, 0, 1));
    auto s = sphere();

    auto intersections = s.getIntersections(r);

    BOOST_CHECK_EQUAL(intersections.size(), 0);
}

BOOST_AUTO_TEST_CASE(intersectionBehindRay) {
    auto r = ray(point(0, 0, 5), vector(0, 0, 1));
    auto s = sphere();

    auto intersections = s.getIntersections(r);

    BOOST_CHECK_EQUAL(intersections.size(), 2);
    BOOST_CHECK_EQUAL(equalWithError(intersections[0], -6), true);
    BOOST_CHECK_EQUAL(equalWithError(intersections[1], -4), true);
}

BOOST_AUTO_TEST_SUITE_END()