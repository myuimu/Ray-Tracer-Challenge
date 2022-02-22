#include <boost/test/unit_test.hpp>
#include "ray_tracer.h"

using namespace rayTracer;

const auto TEST_WORLD = world(
    std::vector<std::shared_ptr<shape>>{
        std::make_shared<sphere>(sphere(IDENTITY_MATRIX, material(color(0.8, 1.0, 0.6), 0, 0.7, 0.2, 0))),
        std::make_shared<sphere>(sphere(scaling(0.5, 0.5, 0.5), material()))}, 
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


BOOST_AUTO_TEST_SUITE_END()