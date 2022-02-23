#include <boost/test/unit_test.hpp>
#include "ray_tracer.h"
#include "math.h"
#include <memory>

using namespace rayTracer;

const auto SPHERE_1 = std::make_shared<sphere>(sphere(IDENTITY_MATRIX, material(color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2, 200)));
const auto SPHERE_2 = std::make_shared<sphere>(sphere(scaling(0.5, 0.5, 0.5), material()));

const auto TEST_WORLD = world(
    std::vector<std::shared_ptr<shape>>{SPHERE_1, SPHERE_2}, 
    std::vector<pointLight>{
        pointLight(point(-10, 10, -10), color(1, 1, 1))
    });

BOOST_AUTO_TEST_SUITE(transformationTest)

BOOST_AUTO_TEST_CASE(createCamera) {
    auto c = camera(160, 120, M_PI_2);

    BOOST_CHECK_EQUAL(c.getHSize(), 160);
    BOOST_CHECK_EQUAL(c.getVSize(), 120);
    BOOST_CHECK_EQUAL(c.getFov(), M_PI_2);
    BOOST_CHECK_EQUAL(c.getTransform(), IDENTITY_MATRIX);
}

BOOST_AUTO_TEST_CASE(horizontalPixelSize) {
    auto c = camera(200, 125, M_PI_2);

    BOOST_CHECK_EQUAL(equalWithError(c.getPixelSize(), 0.01), true);
}

BOOST_AUTO_TEST_CASE(verticalPixelSize) {
    auto c = camera(125, 200, M_PI_2);

    BOOST_CHECK_EQUAL(equalWithError(c.getPixelSize(), 0.01), true);
}

BOOST_AUTO_TEST_CASE(centerRay) {
    auto c = camera(201, 101, M_PI_2);

    auto r = c.getRayForPixel(100, 50);

    BOOST_CHECK_EQUAL(r, ray(point(0, 0, 0), vector(0, 0, -1)));
}

BOOST_AUTO_TEST_CASE(cornerRay) {
    auto c = camera(201, 101, M_PI_2);

    auto r = c.getRayForPixel(0, 0);

    BOOST_CHECK_EQUAL(r, ray(point(0, 0, 0), vector(0.66519, 0.33259, -0.66851)));
}

BOOST_AUTO_TEST_CASE(transformedCameraRay) {
    auto c = camera(201, 101, M_PI_2, translation(0, -2, 5).rotateY(M_PI_4));

    auto r = c.getRayForPixel(100, 50);

    BOOST_CHECK_EQUAL(r, ray(point(0, 2, -5), vector(sqrt(2) / 2, 0, -sqrt(2) / 2)));
}

BOOST_AUTO_TEST_CASE(renderWorld) {
    auto c = camera(11, 11, M_PI_2, viewTransform(
        point(0, 0, -5),
        point(0, 0, 0),
        vector(0, 1, 0)
    ));

    auto image = c.render(TEST_WORLD);

    BOOST_CHECK_EQUAL(image.getPixel(5, 5), color(0.38066, 0.47583, 0.2855));
}

BOOST_AUTO_TEST_SUITE_END()