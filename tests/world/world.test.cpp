#include <boost/test/unit_test.hpp>
#include "ray_tracer.h"

using namespace rayTracer;

const auto SPHERE_1 = std::make_shared<sphere>(sphere(IDENTITY_MATRIX, material(color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2, 200)));
const auto SPHERE_2 = std::make_shared<sphere>(sphere(scaling(0.5, 0.5, 0.5), material()));

const auto TEST_WORLD = world(
    std::vector<std::shared_ptr<shape>>{SPHERE_1, SPHERE_2}, 
    std::vector<pointLight>{
        pointLight(point(-10, 10, -10), color(1, 1, 1))
    });

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
            std::make_shared<sphere>(sphere(IDENTITY_MATRIX, material(color(0.8, 1.0, 0.6), 1, 0.7, 0.2, 0))),
            std::make_shared<sphere>(sphere(scaling(0.5, 0.5, 0.5), material(color(1, 1, 1), 1, 0, 0, 0)))}, 
        std::vector<pointLight>{
            pointLight(point(0, 0.25, 0), color(1, 1, 1))
        });
    auto r = ray(point(0, 0, 0.75), vector(0, 0, -1));

    auto c = w.colorAt(r);
    BOOST_CHECK_EQUAL(c, color(1, 1, 1));
}

BOOST_AUTO_TEST_SUITE_END()