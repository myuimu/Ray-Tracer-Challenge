#include <boost/test/unit_test.hpp>
#include "light/pointLight.h"

using namespace rayTracer;

BOOST_AUTO_TEST_SUITE(pointLightTest)

BOOST_AUTO_TEST_CASE(hasPositionAndIntensity) {
    auto intensity = color(1, 1, 1);
    auto position = point(0, 0, 0);

    auto light = pointLight(position, intensity);

    BOOST_CHECK_EQUAL(light.getPosition(), position);
    BOOST_CHECK_EQUAL(light.getIntensity(), intensity);
}

BOOST_AUTO_TEST_SUITE_END()