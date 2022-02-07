#include <boost/test/unit_test.hpp>
#include "matrix/transformation.h"
#include "tuple/tuple.h"
#include <math.h>

using namespace ray;

BOOST_AUTO_TEST_SUITE(transformationTest)

/*-----TRANSLATION TESTS-----*/

BOOST_AUTO_TEST_CASE(translatePoint) {
    auto transform = translation(5, -3, 2);
    auto p = point(-3, 4, 5);

    BOOST_CHECK_EQUAL(transform * p, point(2, 1, 7));
}

BOOST_AUTO_TEST_CASE(inverseTranslatePoint) {
    auto transform = translation(5, -3, 2).getInverse();
    auto p = point(-3, 4, 5);

    BOOST_CHECK_EQUAL(transform * p, point(-8, 7, 3));
}

BOOST_AUTO_TEST_CASE(translationDoesNotAffectVectors) {
    auto transform = translation(5, -3, 2);
    auto v = vector(-3, 4, 5);

    BOOST_CHECK_EQUAL(transform * v, v);
}

/*-----SCALING TESTS-----*/

BOOST_AUTO_TEST_CASE(scalePoint) {
    auto transform = scaling(2, 3, 4);
    auto p = point(-4, 6, 8);

    BOOST_CHECK_EQUAL(transform * p, point(-8, 18, 32));
}

BOOST_AUTO_TEST_CASE(scaleVector) {
    auto transform = scaling(2, 3, 4);
    auto v = vector(-4, 6, 8);

    BOOST_CHECK_EQUAL(transform * v, vector(-8, 18, 32));
}

BOOST_AUTO_TEST_CASE(inverseScaleVector) {
    auto transform = scaling(2, 3, 4).getInverse();
    auto v = vector(-4, 6, 8);

    BOOST_CHECK_EQUAL(transform * v, vector(-2, 2, 2));
}

BOOST_AUTO_TEST_CASE(reflectPoint) {
    auto transform = scaling(-1, 1, 1);
    auto p = point(2, 3, 4);

    BOOST_CHECK_EQUAL(transform * p, point(-2, 3, 4));
}

/*-----ROTATION TESTS-----*/

BOOST_AUTO_TEST_CASE(xRotation) {
    auto p = point(0, 1, 0);
    auto halfQuarter = rotateX(M_PI / 4);
    auto fullQuarter = rotateX(M_PI / 2);

    BOOST_CHECK_EQUAL(halfQuarter * p, point(0, sqrt(2) / 2, sqrt(2) / 2));
    BOOST_CHECK_EQUAL(fullQuarter * p, point(0, 0, 1));
}

BOOST_AUTO_TEST_CASE(xRotationInverse) {
    auto p = point(0, 1, 0);
    auto inverseHalfQuarter = rotateX(M_PI / 4).getInverse();

    BOOST_CHECK_EQUAL(inverseHalfQuarter * p, point(0, sqrt(2) / 2, -(sqrt(2) / 2)));
}

BOOST_AUTO_TEST_CASE(yRotation) {
    auto p = point(0, 0, 1);
    auto halfQuarter = rotateY(M_PI / 4);
    auto fullQuarter = rotateY(M_PI / 2);

    BOOST_CHECK_EQUAL(halfQuarter * p, point(sqrt(2) / 2, 0, sqrt(2) / 2));
    BOOST_CHECK_EQUAL(fullQuarter * p, point(1, 0, 0));
}

BOOST_AUTO_TEST_CASE(zRotation) {
    auto p = point(0, 1, 0);
    auto halfQuarter = rotateZ(M_PI / 4);
    auto fullQuarter = rotateZ(M_PI / 2);

    BOOST_CHECK_EQUAL(halfQuarter * p, point(-(sqrt(2) / 2), sqrt(2) / 2, 0));
    BOOST_CHECK_EQUAL(fullQuarter * p, point(-1, 0, 0));
}

BOOST_AUTO_TEST_CASE(shearingXInProportionToY) {
    auto transform = shearing(1, 0, 0, 0, 0, 0);
    auto p = point(2, 3, 4);

    BOOST_CHECK_EQUAL(transform * p, point(5, 3, 4));
}

BOOST_AUTO_TEST_CASE(shearingXInProportionToZ) {
    auto transform = shearing(0, 1, 0, 0, 0, 0);
    auto p = point(2, 3, 4);

    BOOST_CHECK_EQUAL(transform * p, point(6, 3, 4));
}

BOOST_AUTO_TEST_CASE(shearingYInProportionToX) {
    auto transform = shearing(0, 0, 1, 0, 0, 0);
    auto p = point(2, 3, 4);

    BOOST_CHECK_EQUAL(transform * p, point(2, 5, 4));
}

BOOST_AUTO_TEST_CASE(shearingYInProportionToZ) {
    auto transform = shearing(0, 0, 0, 1, 0, 0);
    auto p = point(2, 3, 4);

    BOOST_CHECK_EQUAL(transform * p, point(2, 7, 4));
}

BOOST_AUTO_TEST_CASE(shearingZInProportionToX) {
    auto transform = shearing(0, 0, 0, 0, 1, 0);
    auto p = point(2, 3, 4);

    BOOST_CHECK_EQUAL(transform * p, point(2, 3, 6));
}

BOOST_AUTO_TEST_CASE(shearingZInProportionToY) {
    auto transform = shearing(0, 0, 0, 0, 0, 1);
    auto p = point(2, 3, 4);

    BOOST_CHECK_EQUAL(transform * p, point(2, 3, 7));
}

BOOST_AUTO_TEST_CASE(applyingTransformationsInSequence) {
    auto p1 = point(1, 0, 1);
    auto transform1 = rotateX(M_PI / 2);
    auto transform2 = scaling(5, 5, 5);
    auto transform3 = translation(10, 5, 7);

    auto p2 = transform1 * p1;
    BOOST_CHECK_EQUAL(p2, point(1, -1, 0));

    auto p3 = transform2 * p2;
    BOOST_CHECK_EQUAL(p3, point(5, -5, 0));

    auto p4 = transform3 * p3;
    BOOST_CHECK_EQUAL(p4, point(15, 0, 7));
}

BOOST_AUTO_TEST_CASE(chainedTransformationsInReverseOrder) {
    auto p = point(1, 0, 1);
    auto transform1 = rotateX(M_PI / 2);
    auto transform2 = scaling(5, 5, 5);
    auto transform3 = translation(10, 5, 7);

    BOOST_CHECK_EQUAL((transform3 * transform2 * transform1) * p, point(15, 0, 7));
}

BOOST_AUTO_TEST_SUITE_END()