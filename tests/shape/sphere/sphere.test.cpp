#include <boost/test/unit_test.hpp>
#include "shape/sphere/sphere.h"
#include "intersection/intersection.h"
#include "matrix/matrix.h"
#include "matrix/transformation.h"
#include "ray/ray.h"

using namespace rayTracer;

BOOST_AUTO_TEST_SUITE(sphereTest)

BOOST_AUTO_TEST_CASE(rayIntersectsTwice) {
    auto r = ray(point(0, 0, -5), vector(0, 0, 1));
    auto s = sphere();

    auto intersections = s.getIntersections(r);

    BOOST_CHECK_EQUAL(intersections.size(), 2);
    BOOST_CHECK_EQUAL(intersections[0].getObject(), s);
    BOOST_CHECK_EQUAL(intersections[1].getObject(), s);
}

BOOST_AUTO_TEST_CASE(rayIntersectsOnce) {
    auto r = ray(point(0, 1, -5), vector(0, 0, 1));
    auto s = sphere();

    auto intersections = s.getIntersections(r);

    BOOST_CHECK_EQUAL(intersections.size(), 2);
    BOOST_CHECK_EQUAL(intersections[0].getT(), 5);
    BOOST_CHECK_EQUAL(intersections[1].getT(), 5);
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
    BOOST_CHECK_EQUAL(intersections[0].getT(), -6);
    BOOST_CHECK_EQUAL(intersections[1].getT(), -4);
}

BOOST_AUTO_TEST_CASE(defaultTransformation) {
    auto s = sphere();

    BOOST_CHECK_EQUAL(s.getTransform(), IDENTITY_MATRIX);
}

BOOST_AUTO_TEST_CASE(changeTransformation) {
    auto s = sphere();
    auto t = translation(2, 3, 4);

    s.setTransform(t);

    BOOST_CHECK_EQUAL(s.getTransform(), t);
}

BOOST_AUTO_TEST_CASE(intersectScaledSphere) {
    auto r = ray(point(0, 0, -5), vector(0, 0, 1));
    auto s = sphere();

    s.setTransform(scaling(2, 2, 2));
    auto xs = s.getIntersections(r);

    BOOST_CHECK_EQUAL(xs.size(), 2);
    BOOST_CHECK_EQUAL(xs[0].getT(), 3);
    BOOST_CHECK_EQUAL(xs[1].getT(), 7);
}

BOOST_AUTO_TEST_CASE(intersectTranslatedSphere) {
    auto r = ray(point(0, 0, -5), vector(0, 0, 1));
    auto s = sphere();

    s.setTransform(translation(5, 0, 0));
    auto xs = s.getIntersections(r);

    BOOST_CHECK_EQUAL(xs.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()