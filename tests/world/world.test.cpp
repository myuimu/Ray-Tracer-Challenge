#include <boost/test/unit_test.hpp>
#include "ray_tracer.h"

using namespace rayTracer;

const auto SPHERE_1 = std::make_shared<sphere>(sphere(IDENTITY_MATRIX, material(color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2, 200, 0)));
const auto SPHERE_2 = std::make_shared<sphere>(sphere(scaling(0.5, 0.5, 0.5), material()));
const auto TEST_LIGHT = pointLight(point(-10, 10, -10), color(1, 1, 1));

const auto TEST_WORLD = world(
    std::vector<std::shared_ptr<shape>>{SPHERE_1, SPHERE_2}, 
    std::vector<pointLight>{TEST_LIGHT});

BOOST_AUTO_TEST_SUITE(worldTest)

BOOST_AUTO_TEST_CASE(getWorldIntersections) {
    auto r = ray(point(0, 0, -5), vector(0, 0, 1));

    auto xs = TEST_WORLD.getIntersections(r);

    BOOST_CHECK_EQUAL(xs.size(), 4);
    BOOST_CHECK_EQUAL(xs[0].getT(), 4);
    BOOST_CHECK_EQUAL(xs[1].getT(), 4.5);
    BOOST_CHECK_EQUAL(xs[2].getT(), 5.5);
    BOOST_CHECK_EQUAL(xs[3].getT(), 6);
}

BOOST_AUTO_TEST_CASE(shadeIntersection) {
    auto r = ray(point(0, 0, -5), vector(0, 0, 1));
    auto i = intersection(4, SPHERE_1);

    auto comps = computations(i, r);
    auto c = TEST_WORLD.shadeHit(comps);

    BOOST_CHECK_EQUAL(c, color(0.38066, 0.47583, 0.2855));
}

BOOST_AUTO_TEST_CASE(shadeIntersectionFromInside) {
    auto w = world(
        std::vector<std::shared_ptr<shape>>{SPHERE_1, SPHERE_2}, 
        std::vector<pointLight>{
            pointLight(point(0, 0.25, 0), color(1, 1, 1))
        }
    );
    auto r = ray(point(0, 0, 0), vector(0, 0, 1));
    auto i = intersection(0.5, SPHERE_2);

    auto comps = computations(i, r);
    auto c = w.shadeHit(comps);

    BOOST_CHECK_EQUAL(c, color(0.90498, 0.90498, 0.90498));
}

BOOST_AUTO_TEST_CASE(rayMissesObjects) {
    auto r = ray(point(0, 0, -5), vector(0, 1, 0));

    auto c = TEST_WORLD.colorAt(r);

    BOOST_CHECK_EQUAL(c, BLACK);
}

BOOST_AUTO_TEST_CASE(rayHits) {
    auto r = ray(point(0, 0, -5), vector(0, 0, 1));

    auto c = TEST_WORLD.colorAt(r);

    BOOST_CHECK_EQUAL(c, color(0.38066, 0.47583, 0.2855));
}

BOOST_AUTO_TEST_CASE(intersectionBehindRay) {
    auto w = world(
        std::vector<std::shared_ptr<shape>>{
            std::make_shared<sphere>(sphere(IDENTITY_MATRIX, material(color(0.8, 1.0, 0.6), 1, 0.7, 0.2, 0, 0))),
            std::make_shared<sphere>(sphere(scaling(0.5, 0.5, 0.5), material(color(1, 1, 1), 1, 0, 0, 0, 0)))}, 
        std::vector<pointLight>{
            pointLight(point(0, 0.25, 0), color(1, 1, 1))
        });
    auto r = ray(point(0, 0, 0.75), vector(0, 0, -1));

    auto c = w.colorAt(r);
    BOOST_CHECK_EQUAL(c, color(1, 1, 1));
}

BOOST_AUTO_TEST_CASE(noShadowWhenNothingBetwenLightAndPoint) {
    auto p = point(0, 10, 0);

    BOOST_CHECK_EQUAL(TEST_WORLD.isShadowed(p, TEST_LIGHT), false);
}

BOOST_AUTO_TEST_CASE(shadowedWhenObjectBetweenPointAndLight) {
    auto p = point(10, -10, 10);

    BOOST_CHECK_EQUAL(TEST_WORLD.isShadowed(p, TEST_LIGHT), true);
}

BOOST_AUTO_TEST_CASE(noShadowWhenObjectBehindLight) {
    auto p = point(-20, 20, -20);

    BOOST_CHECK_EQUAL(TEST_WORLD.isShadowed(p, TEST_LIGHT), false);
}

BOOST_AUTO_TEST_CASE(noShadowWhenPointBetweenObjectAndLight) {
    auto p = point(-2, 2, -2);

    BOOST_CHECK_EQUAL(TEST_WORLD.isShadowed(p, TEST_LIGHT), false);
}

BOOST_AUTO_TEST_CASE(shadeHitIntersectionInShadow) {
    auto s1 = std::make_shared<sphere>(sphere());
    auto s2 = std::make_shared<sphere>(sphere(translation(0, 0, 10), material()));
    auto light = pointLight(point(0, 0, -10), color(1, 1, 1));
    auto w = world(
        std::vector<std::shared_ptr<shape>>{s1, s2},
        std::vector<pointLight>{light});
    auto r = ray(point(0, 0, 5), vector(0, 0, 1));
    auto i = intersection(4, s2);

    auto comps = computations(i, r);
    auto c = w.shadeHit(comps);

    BOOST_CHECK_EQUAL(c, color(0.1, 0.1, 0.1));
}

BOOST_AUTO_TEST_CASE(reflectedColorOfNonreflectiveMaterial) {
    auto r = ray(point(0, 0, 0), vector(0, 0, 1));
    auto s = std::make_shared<sphere>(sphere(IDENTITY_MATRIX, material(color(1, 1, 1), 1, 0.9, 0.9, 200, 0)));
    auto w = world(
        std::vector<std::shared_ptr<shape>>{SPHERE_1, s}, 
        std::vector<pointLight>{TEST_LIGHT});
    auto i = intersection(1, s);

    auto comps = computations(i, r);
    auto c = w.getReflectedColor(comps, 1);

    BOOST_CHECK_EQUAL(c, color(0, 0, 0));
}

BOOST_AUTO_TEST_CASE(reflectedColorOfReflectiveMaterial) {
    auto r = ray(point(0, 0, -3), vector(0, -sqrt(2) / 2, sqrt(2) / 2));
    auto s = std::make_shared<plane>(plane(translation(0, -1, 0), material(color(1, 1, 1), 0.1, 0.9, 0.9, 200, 0.5)));
    auto w = world(
        std::vector<std::shared_ptr<shape>>{SPHERE_1, SPHERE_2, s}, 
        std::vector<pointLight>{TEST_LIGHT});
    auto i = intersection(sqrt(2), s);

    auto comps = computations(i, r);
    auto c = w.getReflectedColor(comps, 1);

    BOOST_CHECK_EQUAL(c, color(0.19032, 0.2379, 0.14274));
}

BOOST_AUTO_TEST_CASE(shadeHitReflectiveMaterial) {
    auto r = ray(point(0, 0, -3), vector(0, -sqrt(2) / 2, sqrt(2) / 2));
    auto s = std::make_shared<plane>(plane(translation(0, -1, 0), material(color(1, 1, 1), 0.1, 0.9, 0.9, 200, 0.5)));
    auto w = world(
        std::vector<std::shared_ptr<shape>>{SPHERE_1, SPHERE_2, s}, 
        std::vector<pointLight>{TEST_LIGHT});
    auto i = intersection(sqrt(2), s);

    auto comps = computations(i, r);
    auto c = w.shadeHit(comps);

    BOOST_CHECK_EQUAL(c, color(0.87677, 0.92436, 0.82918));
}

BOOST_AUTO_TEST_CASE(avoidInfiniteRecursion) {
    auto w = world(
        std::vector<std::shared_ptr<shape>>{
            std::make_shared<plane>(plane(translation(0, -1, 0), material(color(1, 1, 1), 0.1, 0.9, 0.9, 200, 1))),
            std::make_shared<plane>(plane(translation(0, 1, 0), material(color(1, 1, 1), 0.1, 0.9, 0.9, 200, 1)))
        },
        std::vector<pointLight>{pointLight(point(0, 0, 0), color(1, 1, 1))}
    );
    auto r = ray(point(0, 0, 0), vector(0, 1, 0));
    BOOST_REQUIRE_NO_THROW(w.colorAt(r));
}

BOOST_AUTO_TEST_CASE(limitRecursion) {
    auto r = ray(point(0, 0, -3), vector(0, -sqrt(2) / 2, sqrt(2) / 2));
    auto s = std::make_shared<plane>(plane(translation(0, -1, 0), material(color(1, 1, 1), 0.1, 0.9, 0.9, 200, 0.5)));
    auto w = world(
        std::vector<std::shared_ptr<shape>>{SPHERE_1, SPHERE_2, s}, 
        std::vector<pointLight>{TEST_LIGHT});
    auto i = intersection(sqrt(2), s);

    auto comps = computations(i, r);
    auto c = w.getReflectedColor(comps, 0);

    BOOST_CHECK_EQUAL(c, color(0, 0, 0));
}

BOOST_AUTO_TEST_SUITE_END()