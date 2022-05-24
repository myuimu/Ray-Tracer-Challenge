#include <boost/test/unit_test.hpp>
#include "shape/cube/cube.h"
#include "intersection/intersection.h"
#include "matrix/matrix.h"
#include "matrix/transformation.h"
#include "ray/ray.h"
#include "shape/material.h"
#include "intersection/computations.h"

using namespace rayTracer;

BOOST_AUTO_TEST_SUITE(cubeTest)

BOOST_AUTO_TEST_CASE(rayIntersectsCube) {
    auto c = std::make_shared<cube>(cube());
    auto tests = std::vector<std::tuple<tuple, tuple, int, int>>{
        {point(5, 0.5, 0), vector(-1, 0, 0), 4, 6},
        {point(-5, 0.5, 0), vector(1, 0, 0), 4, 6},
        {point(0.5, 5, 0), vector(0, -1, 0), 4, 6},
        {point(0.5, -5, 0), vector(0, 1, 0), 4, 6},
        {point(0.5, 0, 5), vector(0, 0, -1), 4, 6},
        {point(0.5, 0, -5), vector(0, 0, 1), 4, 6},
        {point(0, 0.5, 0), vector(0, 0, 1), -1, 1}
    };

    for (auto test: tests) {
        auto [ origin, direction, t1, t2 ] = test;
        auto r = ray(origin, direction);
        auto xs = c->getLocalIntersections(r);

        BOOST_CHECK_EQUAL(xs.size(), 2);
        BOOST_CHECK_EQUAL(xs[0].getT(), t1);
        BOOST_CHECK_EQUAL(xs[1].getT(), t2);
    }
}

BOOST_AUTO_TEST_CASE(rayMissesCube) {
    auto c = std::make_shared<cube>(cube());
    auto tests = std::vector<std::tuple<tuple, tuple>>{
        {point(-2, 0, 0), vector(0.2673, 0.5345, 0.8018)},
        {point(0, -2, 0), vector(0.8018, 0.2673, 0.5345)},
        {point(0, 0, -2), vector(0.5345, 0.8018, 0.2673)},
        {point(2, 0, 2), vector(0, 0, -1)},
        {point(0, 2, 2), vector(0, -1, 0)},
        {point(2, 2, 0), vector(-1, 0, 0)}
    };

    for (auto test: tests) {
        auto [ origin, direction ] = test;
        auto r = ray(origin, direction);
        auto xs = c->getLocalIntersections(r);

        BOOST_CHECK_EQUAL(xs.size(), 0);
    }
}

BOOST_AUTO_TEST_CASE(cubeNormal) {
    auto c = std::make_shared<cube>(cube());
    auto tests = std::vector<std::tuple<tuple, tuple>>{
        {point(1, 0.5, -0.8), vector(1, 0, 0)},
        {point(-1, -0.2, 0.9), vector(-1, 0, 0)},
        {point(-0.4, 1, -0.1), vector(0, 1, 0)},
        {point(0.3, -1, -0.7), vector(0, -1, 0)},
        {point(-0.6, 0.3, 1), vector(0, 0, 1)},
        {point(0.4, 0.4, -1), vector(0, 0, -1)},
        {point(1, 1, 1), vector(1, 0, 0)},
        {point(-1, -1, -1), vector(-1, 0, 0)}
    };

    for (auto test: tests) {
        auto [ p, n ] = test;
        BOOST_CHECK_EQUAL(c->getLocalNormal(p), n);
    }
}

BOOST_AUTO_TEST_SUITE_END()