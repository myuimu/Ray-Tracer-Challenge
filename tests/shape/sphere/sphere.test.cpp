#include <boost/test/unit_test.hpp>
#include "shape/sphere/sphere.h"
#include "intersection/intersection.h"
#include "matrix/matrix.h"
#include "matrix/transformation.h"
#include "ray/ray.h"
#include "shape/material.h"
#include "intersection/computations.h"

using namespace rayTracer;

BOOST_AUTO_TEST_SUITE(sphereTest)

BOOST_AUTO_TEST_CASE(rayIntersectsTwice) {
    auto r = ray(point(0, 0, -5), vector(0, 0, 1));
    auto s = std::make_shared<sphere>(sphere());

    auto intersections = s->getIntersections(r);

    BOOST_CHECK_EQUAL(intersections.size(), 2);
    BOOST_CHECK_EQUAL(intersections[0].getObject(), *s.get());
    BOOST_CHECK_EQUAL(intersections[1].getObject(), *s.get());
}

BOOST_AUTO_TEST_CASE(rayIntersectsOnce) {
    auto r = ray(point(0, 1, -5), vector(0, 0, 1));
    auto s = std::make_shared<sphere>(sphere());

    auto intersections = s->getIntersections(r);

    BOOST_CHECK_EQUAL(intersections.size(), 2);
    BOOST_CHECK_EQUAL(intersections[0].getT(), 5);
    BOOST_CHECK_EQUAL(intersections[1].getT(), 5);
}

BOOST_AUTO_TEST_CASE(rayDoesNotIntersect) {
    auto r = ray(point(0, 2, -5), vector(0, 0, 1));
    auto s = std::make_shared<sphere>(sphere());

    auto intersections = s->getIntersections(r);

    BOOST_CHECK_EQUAL(intersections.size(), 0);
}

BOOST_AUTO_TEST_CASE(intersectionBehindRay) {
    auto r = ray(point(0, 0, 5), vector(0, 0, 1));
    auto s = std::make_shared<sphere>(sphere());

    auto intersections = s->getIntersections(r);

    BOOST_CHECK_EQUAL(intersections.size(), 2);
    BOOST_CHECK_EQUAL(intersections[0].getT(), -6);
    BOOST_CHECK_EQUAL(intersections[1].getT(), -4);
}

BOOST_AUTO_TEST_CASE(intersectScaledSphere) {
    auto r = ray(point(0, 0, -5), vector(0, 0, 1));
    auto s = std::make_shared<sphere>(sphere());

    s->setTransform(scaling(2, 2, 2));
    auto xs = s->getIntersections(r);

    BOOST_CHECK_EQUAL(xs.size(), 2);
    BOOST_CHECK_EQUAL(xs[0].getT(), 3);
    BOOST_CHECK_EQUAL(xs[1].getT(), 7);
}

BOOST_AUTO_TEST_CASE(intersectTranslatedSphere) {
    auto r = ray(point(0, 0, -5), vector(0, 0, 1));
    auto s = std::make_shared<sphere>(sphere());

    s->setTransform(translation(5, 0, 0));
    auto xs = s->getIntersections(r);

    BOOST_CHECK_EQUAL(xs.size(), 0);
}

BOOST_AUTO_TEST_CASE(xNormal) {
    auto s = std::make_shared<sphere>(sphere());
    
    auto n = s->getNormal(point(1, 0, 0));

    BOOST_CHECK_EQUAL(n, vector(1, 0, 0));
}

BOOST_AUTO_TEST_CASE(yNormal) {
    auto s = std::make_shared<sphere>(sphere());
    
    auto n = s->getNormal(point(0, 1, 0));

    BOOST_CHECK_EQUAL(n, vector(0, 1, 0));
}

BOOST_AUTO_TEST_CASE(xzNormal) {
    auto s = std::make_shared<sphere>(sphere());
    
    auto n = s->getNormal(point(0, 0, 1));

    BOOST_CHECK_EQUAL(n, vector(0, 0, 1));
}

BOOST_AUTO_TEST_CASE(nonAxialNormal) {
    auto s = std::make_shared<sphere>(sphere());
    
    auto n = s->getNormal(point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));

    BOOST_CHECK_EQUAL(n, vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
}

BOOST_AUTO_TEST_CASE(normalIsNormalized) {
    auto s = std::make_shared<sphere>(sphere());
    
    auto n = s->getNormal(point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));

    BOOST_CHECK_EQUAL(n, n.normalized());
}

BOOST_AUTO_TEST_CASE(normalOfTranslatedSphere) {
    auto s = std::make_shared<sphere>(sphere());
    s->setTransform(translation(0, 1, 0));

    auto n = s->getNormal(point(0, 1.70711, -0.70711));

    BOOST_CHECK_EQUAL(n, vector(0, 0.70711, -0.70711));
}

BOOST_AUTO_TEST_CASE(normalOfScaledAndRotatedSphere) {
    auto s = std::make_shared<sphere>(sphere());
    s->setTransform(zRotation(M_PI / 5).scale(1, 0.5, 1));

    auto n = s->getNormal(point(0, sqrt(2) / 2, -sqrt(2) / 2));

    BOOST_CHECK_EQUAL(n, vector(0, 0.97014, -0.24254));
}

BOOST_AUTO_TEST_CASE(defaultGlassSphere) {
    auto s = getGlassSphere();

    BOOST_CHECK_EQUAL(s.getTransform(), IDENTITY_MATRIX);
    BOOST_CHECK_EQUAL(s.getMaterial().getTransparency(), 1.0);
    BOOST_CHECK_EQUAL(s.getMaterial().getRefractiveIndex(), 1.5);
}

BOOST_AUTO_TEST_CASE(prepareRefractionCalculations) {
    std::vector<std::pair<double, double>> expectedValues = {
        {1.0, 1.5},
        {1.5, 2.0},
        {2.0, 2.5},
        {2.5, 2.5},
        {2.5, 1.5},
        {1.5, 1.0}
    };
    auto glassMaterial = material();

    auto a = std::make_shared<sphere>(getGlassSphere());
    a->setTransform(scaling(2,2,2));
    glassMaterial.setRefractiveIndex(1.5);
    a->setMaterial(glassMaterial);

    auto b = std::make_shared<sphere>(getGlassSphere());
    b->setTransform(translation(0, 0, -0.25));
    glassMaterial.setRefractiveIndex(2.0);
    b->setMaterial(glassMaterial);

    auto c = std::make_shared<sphere>(getGlassSphere());
    c->setTransform(translation(0, 0, 0.25));
    glassMaterial.setRefractiveIndex(2.5);
    c->setMaterial(glassMaterial);

    auto r = ray(point(0, 0, -4), vector(0, 0, 1));
    std::vector<intersection> xs = {
        {2, a},
        {2.75, b},
        {3.25, c},
        {4.75, b},
        {5.25, c},
        {6, a}
    };

    for(int i = 0; i < 6; i++) {
        auto comps = computations(xs[i], r, xs);

        BOOST_CHECK_EQUAL(comps.getExitRefractiveIndex(), expectedValues[i].first);
        BOOST_CHECK_EQUAL(comps.getEnterRefractiveIndex(), expectedValues[i].second);
    }
}

BOOST_AUTO_TEST_SUITE_END()