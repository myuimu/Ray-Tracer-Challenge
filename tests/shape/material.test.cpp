#include <boost/test/unit_test.hpp>
#include "shape/material.h"
#include "shape/sphere/sphere.h"
#include <math.h>

using namespace rayTracer;

BOOST_AUTO_TEST_SUITE(materialTest)

BOOST_AUTO_TEST_CASE(defaultMaterial) {
    auto m = material();

    BOOST_CHECK_EQUAL(m.getColor(), color(1, 1, 1));
    BOOST_CHECK_EQUAL(m.getAmbient(), 0.1);
    BOOST_CHECK_EQUAL(m.getDiffuse(), 0.9);
    BOOST_CHECK_EQUAL(m.getSpecular(), 0.9);
    BOOST_CHECK_EQUAL(m.getShininess(), 200.0);
}

BOOST_AUTO_TEST_CASE(lightingTest1) {
    auto object = sphere();
    auto m = material();
    auto position = point(0, 0, 0);
    auto eyeV = vector(0, 0, -1);
    auto normalV = vector(0, 0, -1);
    auto light = pointLight(point(0, 0, -10), color(1, 1, 1));
    auto inShadow = false;

    auto result = m.getLighting(light, object, position, eyeV, normalV, inShadow);

    BOOST_CHECK_EQUAL(result, color(1.9, 1.9, 1.9));
}

BOOST_AUTO_TEST_CASE(lightingTest2) {
    auto object = sphere();
    auto m = material();
    auto position = point(0, 0, 0);
    auto eyeV = vector(0, 0, -1);
    auto normalV = vector(0, 0, -1);
    auto light = pointLight(point(0, 0, -10), color(1, 1, 1));
    auto inShadow = false;

    auto result = m.getLighting(light, object, position, eyeV, normalV, inShadow);

    BOOST_CHECK_EQUAL(result, color(1.9, 1.9, 1.9));
}

BOOST_AUTO_TEST_CASE(lightingTest3) {
    auto object = sphere();
    auto m = material();
    auto position = point(0, 0, 0);
    auto eyeV = vector(0, M_SQRT2 / 2, M_SQRT2 / 2);
    auto normalV = vector(0, 0, -1);
    auto light = pointLight(point(0, 0, -10), color(1, 1, 1));
    auto inShadow = false;

    auto result = m.getLighting(light, object, position, eyeV, normalV, inShadow);

    BOOST_CHECK_EQUAL(result, color(1.0, 1.0, 1.0));
}

BOOST_AUTO_TEST_CASE(lightingTest4) {
    auto object = sphere();
    auto m = material();
    auto position = point(0, 0, 0);
    auto eyeV = vector(0, 0, -1);
    auto normalV = vector(0, 0, -1);
    auto light = pointLight(point(0, 10, -10), color(1, 1, 1));
    auto inShadow = false;

    auto result = m.getLighting(light, object, position, eyeV, normalV, inShadow);

    BOOST_CHECK_EQUAL(result, color(0.7364, 0.7364, 0.7364));
}

BOOST_AUTO_TEST_CASE(lightingTest5) {
    auto object = sphere();
    auto m = material();
    auto position = point(0, 0, 0);
    auto eyeV = vector(0, -M_SQRT2 / 2, -M_SQRT2 / 2);
    auto normalV = vector(0, 0, -1);
    auto light = pointLight(point(0, 10, -10), color(1, 1, 1));
    auto inShadow = false;

    auto result = m.getLighting(light, object, position, eyeV, normalV, inShadow);

    BOOST_CHECK_EQUAL(result, color(1.6364, 1.6364, 1.6364));
}

BOOST_AUTO_TEST_CASE(lightingTest6) {
    auto object = sphere();
    auto m = material();
    auto position = point(0, 0, 0);
    auto eyeV = vector(0, 0, -1);
    auto normalV = vector(0, 0, -1);
    auto light = pointLight(point(0, 0, 10), color(1, 1, 1));
    auto inShadow = false;

    auto result = m.getLighting(light, object, position, eyeV, normalV, inShadow);

    BOOST_CHECK_EQUAL(result, color(0.1, 0.1, 0.1));
}

BOOST_AUTO_TEST_CASE(lightingInShadow) {
    auto object = sphere();
    auto m = material();
    auto position = point(0, 0, 0);
    auto eyeV = vector(0, 0, -1);
    auto normalV = vector(0, 0, -1);
    auto light = pointLight(point(0, 0, -10), color(1, 1, 1));
    auto inShadow = true;

    auto result = m.getLighting(light, object, position, eyeV, normalV, inShadow);

    BOOST_CHECK_EQUAL(result, color(0.1, 0.1, 0.1));
}

BOOST_AUTO_TEST_CASE(defaultReflective) {
    auto m = material();

    BOOST_CHECK_EQUAL(m.getReflective(), 0);
}

BOOST_AUTO_TEST_CASE(defaultTransparencyAndRefractiveIndex) {
    auto m = material();

    BOOST_CHECK_EQUAL(m.getTransparency(), 0.0);
    BOOST_CHECK_EQUAL(m.getRefractiveIndex(), 1.0);
}

BOOST_AUTO_TEST_SUITE_END()