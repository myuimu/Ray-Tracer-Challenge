#include <boost/test/unit_test.hpp>
#include "intersection/computations.h"
#include "intersection/intersection.h"
#include "shape/sphere/sphere.h"
#include "tuple/tuple.h"

using namespace rayTracer;

BOOST_AUTO_TEST_SUITE(computationsTest)

BOOST_AUTO_TEST_CASE(precomputeIntersectionState) {
    auto r = ray(point(0, 0, -5), vector(0, 0, 1));
    auto s = sphere();
    auto i = intersection(4, std::make_shared<sphere>(s));

    auto comps = computations(i, r);

    BOOST_CHECK_EQUAL(comps.getT(), i.getT());
    BOOST_CHECK_EQUAL(comps.getObject(), i.getObject());
    BOOST_CHECK_EQUAL(comps.getPoint(), point(0, 0, -1));
    BOOST_CHECK_EQUAL(comps.getEyeV(), vector(0, 0, -1));
    BOOST_CHECK_EQUAL(comps.getNormalV(), vector(0, 0, -1));
}

BOOST_AUTO_TEST_CASE(intersectionOutside) {
    auto r = ray(point(0, 0, -5), vector(0, 0, 1));
    auto s = sphere();
    auto i = intersection(4, std::make_shared<sphere>(s));

    auto comps = computations(i, r);

    BOOST_CHECK_EQUAL(comps.isInside(), false);
}

BOOST_AUTO_TEST_CASE(intersectioninside) {
    auto r = ray(point(0, 0, 0), vector(0, 0, 1));
    auto s = sphere();
    auto i = intersection(1, std::make_shared<sphere>(s));

    auto comps = computations(i, r);

    BOOST_CHECK_EQUAL(comps.getPoint(), point(0, 0, 1));
    BOOST_CHECK_EQUAL(comps.getEyeV(), vector(0, 0, -1));
    BOOST_CHECK_EQUAL(comps.getNormalV(), vector(0, 0, -1));
    BOOST_CHECK_EQUAL(comps.isInside(), true);
}

BOOST_AUTO_TEST_SUITE_END()