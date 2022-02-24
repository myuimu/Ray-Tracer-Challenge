#include <boost/test/unit_test.hpp>
#include "shape/plane/plane.h"

using namespace rayTracer;

BOOST_AUTO_TEST_SUITE(planeTest)

BOOST_AUTO_TEST_CASE(normalOfPlaneIsConstant) {
    auto p = plane();

    auto n1 = p.getNormal(point(0, 0, 0));
    auto n2 = p.getNormal(point(10, 0, -10));
    auto n3 = p.getNormal(point(-5, 0, 150));

    BOOST_CHECK_EQUAL(n1, vector(0, 1, 0));
    BOOST_CHECK_EQUAL(n2, vector(0, 1, 0));
    BOOST_CHECK_EQUAL(n3, vector(0, 1, 0));
}

BOOST_AUTO_TEST_CASE(parallelRayIntersection) {
    auto p = std::make_shared<plane>(plane());
    auto r = ray(point(0, 10, 0), vector(0, 0, 1));

    auto xs = p->getIntersections(r);

    BOOST_CHECK_EQUAL(xs.size(), 0);
}

BOOST_AUTO_TEST_CASE(coplanarRayIntersection) {
    auto p = std::make_shared<plane>(plane());
    auto r = ray(point(0, 0, 0), vector(0, 0, 1));

    auto xs = p->getIntersections(r);

    BOOST_CHECK_EQUAL(xs.size(), 0);
}

BOOST_AUTO_TEST_CASE(aboveRayIntersection) {
    auto p = std::make_shared<plane>(plane());
    auto r = ray(point(0, 1, 0), vector(0, -1, 0));

    auto xs = p->getIntersections(r);

    BOOST_CHECK_EQUAL(xs.size(), 1);
    BOOST_CHECK_EQUAL(xs[0].getT(), 1);
    BOOST_CHECK_EQUAL(xs[0].getObject(), *p.get());
}

BOOST_AUTO_TEST_CASE(belowRayIntersection) {
    auto p = std::make_shared<plane>(plane());
    auto r = ray(point(0, -1, 0), vector(0, -1, 0));

    auto xs = p->getIntersections(r);

    BOOST_CHECK_EQUAL(xs.size(), 1);
    BOOST_CHECK_EQUAL(xs[0].getT(), -1);
    BOOST_CHECK_EQUAL(xs[0].getObject(), *p.get());
}

BOOST_AUTO_TEST_SUITE_END()