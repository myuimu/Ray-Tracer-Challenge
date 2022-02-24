#include <boost/test/unit_test.hpp>
#include "ray_tracer.h"

using namespace rayTracer;

BOOST_AUTO_TEST_SUITE(intersectionTest)

BOOST_AUTO_TEST_CASE(intersectionHasTAndObject) {
    auto s = sphere();
    auto i = intersection(3.5, std::make_shared<sphere>(s));

    BOOST_CHECK_EQUAL(i.getT(), 3.5);
    BOOST_CHECK_EQUAL(i.getObject(), s);
}

BOOST_AUTO_TEST_CASE(listOfIntersections) {
    auto s = sphere();
    auto i1 = intersection(1, std::make_shared<sphere>(s));
    auto i2 = intersection(2, std::make_shared<sphere>(s));

    auto xs = std::vector<intersection>{i1, i2};

    BOOST_CHECK_EQUAL(xs.size(), 2);
    BOOST_CHECK_EQUAL(xs[0].getT(), 1);
    BOOST_CHECK_EQUAL(xs[1].getT(), 2);
}

BOOST_AUTO_TEST_CASE(hitAllIntersectionsPositive) {
    auto s = sphere();
    auto i1 = intersection(1, std::make_shared<sphere>(s));
    auto i2 = intersection(2, std::make_shared<sphere>(s));
    auto xs = std::vector<intersection>{i1, i2};

    auto i = getHit(xs);

    BOOST_CHECK_EQUAL(*i, i1);
}

BOOST_AUTO_TEST_CASE(hitSomeIntersectionsNegative) {
    auto s = sphere();
    auto i1 = intersection(-1, std::make_shared<sphere>(s));
    auto i2 = intersection(1, std::make_shared<sphere>(s));
    auto xs = std::vector<intersection>{i1, i2};

    auto i = getHit(xs);

    BOOST_CHECK_EQUAL(*i, i2);
}

BOOST_AUTO_TEST_CASE(hitAllIntersectionsNegative) {
    auto s = sphere();
    auto i1 = intersection(1, std::make_shared<sphere>(s));
    auto i2 = intersection(2, std::make_shared<sphere>(s));
    auto xs = std::vector<intersection>{i1, i2};

    auto i = getHit(xs);

    BOOST_CHECK_EQUAL(i == xs.end(), false);
}

BOOST_AUTO_TEST_CASE(hitIsLowestNonNegativeIntersection) {
    auto s = sphere();
    auto i1 = intersection(5, std::make_shared<sphere>(s));
    auto i2 = intersection(7, std::make_shared<sphere>(s));
    auto i3 = intersection(-3, std::make_shared<sphere>(s));
    auto i4 = intersection(2, std::make_shared<sphere>(s));
    auto xs = std::vector<intersection>{i1, i2, i3, i4};

    auto i = getHit(xs);

    BOOST_CHECK_EQUAL(*i, i4);
}

BOOST_AUTO_TEST_CASE(hitShouldOffsetPoint) {
    auto r = ray(point(0, 0, -5), vector(0, 0, 1));
    auto s = std::make_shared<sphere>(sphere(translation(0, 0, 1), material()));
    auto i = intersection(5, s);

    auto comps = computations(i, r);

    BOOST_CHECK_LT(comps.getOverPoint().getZ(), -EPSILON / 2);
    BOOST_CHECK_GT(comps.getPoint().getZ(), comps.getOverPoint().getZ());
}

BOOST_AUTO_TEST_SUITE_END()