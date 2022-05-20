#include <boost/test/unit_test.hpp>
#include "intersection/computations.h"
#include "intersection/intersection.h"
#include "shape/sphere/sphere.h"
#include "shape/plane/plane.h"
#include "tuple/tuple.h"
#include "matrix/transformation.h"
#include "ray_tracer.h"

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

BOOST_AUTO_TEST_CASE(reflectionVector) {
    auto s = plane();
    auto r = ray(point(0, 1, -1), vector(0, -M_SQRT2 / 2, M_SQRT2 / 2));
    auto i = intersection(M_SQRT2, std::make_shared<plane>(s));

    auto comps = computations(i, r);

    BOOST_CHECK_EQUAL(comps.getReflectV(), vector(0, M_SQRT2 / 2, M_SQRT2 / 2));
}

BOOST_AUTO_TEST_CASE(underPoint) {
    auto r = ray(point(0, 0, -5), vector(0, 0, 1));
    auto s = getGlassSphere();
    s.setTransform(translation(0, 0, 1));
    auto i = intersection(5, std::make_shared<sphere>(s));
    auto xs = std::vector<intersection>{i};

    auto comps = computations(i, r, xs);

    BOOST_CHECK_GT(comps.getUnderPoint().getZ(), EPSILON / 2);
    BOOST_CHECK_LT(comps.getPoint().getZ(), comps.getUnderPoint().getZ());
}

BOOST_AUTO_TEST_CASE(schlickTotalInternal) {
    auto s = std::make_shared<sphere>(getGlassSphere());
    auto r = ray(point(0, 0, M_SQRT2/2), vector(0, 1, 0));
    auto xs = std::vector<intersection>{
        intersection(-M_SQRT2/2, s),
        intersection(M_SQRT2/2, s)
    };

    auto comps = computations(xs[1], r, xs);

    BOOST_CHECK_EQUAL(comps.getReflectance(), 1.0);
}

BOOST_AUTO_TEST_CASE(schlickPerpendicular) {
    auto s = std::make_shared<sphere>(getGlassSphere());
    auto r = ray(point(0, 0, 0), vector(0, 1, 0));
    auto xs = std::vector<intersection>{
        intersection(-1, s),
        intersection(1, s)
    };

    auto comps = computations(xs[1], r, xs);

    BOOST_CHECK(equalWithError(comps.getReflectance(), 0.04));
}

BOOST_AUTO_TEST_CASE(schlickSmallAngle) {
    auto s = std::make_shared<sphere>(getGlassSphere());
    auto r = ray(point(0, 0.99, -2), vector(0, 0, 1));
    auto xs = std::vector<intersection>{intersection(1.8589, s)};

    auto comps = computations(xs[0], r, xs);

    BOOST_CHECK(equalWithError(comps.getReflectance(), 0.48873));
}

BOOST_AUTO_TEST_SUITE_END()