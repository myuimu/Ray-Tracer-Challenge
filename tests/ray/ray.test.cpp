#include <boost/test/unit_test.hpp>
#include "ray/ray.h"
#include "matrix/transformation.h"

using namespace rayTracer;

BOOST_AUTO_TEST_SUITE(rayTest)

/*-----CONSTRUCTOR TESTS-----*/

BOOST_AUTO_TEST_CASE(createRay) {
    auto origin = point(1, 2, 3);
    auto direction = vector(4, 5, 6);

    auto r = rayTracer::ray(origin, direction);

    BOOST_CHECK_EQUAL(r.getOrigin(), origin);
    BOOST_CHECK_EQUAL(r.getDirection(), direction);
}

/*-----OPERATOR TESTS-----*/

BOOST_AUTO_TEST_CASE(getPosition) {
    auto r = ray(point(2, 3, 4), vector(1, 0, 0));

    BOOST_CHECK_EQUAL(r.getPosition(0), point(2, 3, 4));
    BOOST_CHECK_EQUAL(r.getPosition(1), point(3, 3, 4));
    BOOST_CHECK_EQUAL(r.getPosition(-1), point(1, 3, 4));
    BOOST_CHECK_EQUAL(r.getPosition(2.5), point(4.5, 3, 4));
}

BOOST_AUTO_TEST_CASE(translateRay) {
    auto r = ray(point(1, 2, 3), vector(0, 1, 0));
    auto m = translation(3, 4, 5);

    auto r2 = r.transform(m);

    BOOST_CHECK_EQUAL(r2.getOrigin(), point(4, 6, 8));
    BOOST_CHECK_EQUAL(r2.getDirection(), vector(0, 1, 0));
}

BOOST_AUTO_TEST_CASE(scaleRay) {
    auto r = ray(point(1, 2, 3), vector(0, 1, 0));
    auto m = scaling(2, 3, 4);

    auto r2 = r.transform(m);

    BOOST_CHECK_EQUAL(r2.getOrigin(), point(2, 6, 12));
    BOOST_CHECK_EQUAL(r2.getDirection(), vector(0, 3, 0));
}

BOOST_AUTO_TEST_SUITE_END()