#include <boost/test/unit_test.hpp>
#include "shape/shape.h"
#include "matrix/transformation.h"
#include <math.h>

using namespace rayTracer;

auto localRay = ray(point(), vector());
auto localPoint = point();

namespace rayTracer {
    class testShape : public shape {
        private:
            std::string toString() const {return "testShape";}
            std::vector<intersection> getLocalIntersections(const ray &r) const {
                localRay = r;
                return std::vector<intersection>();
            }
            tuple getLocalNormal(const tuple &p) const {
                localPoint = p;
                return p.toVector();
            }
        public:
            testShape() {}
    };
};

BOOST_AUTO_TEST_SUITE(shapeTest)

BOOST_AUTO_TEST_CASE(shapeHasDefaultTransformation) {
    auto s = testShape();

    BOOST_CHECK_EQUAL(s.getTransform(), IDENTITY_MATRIX);
}

BOOST_AUTO_TEST_CASE(shapeHasDefaultMaterial) {
    auto s = testShape();

    BOOST_CHECK_EQUAL(s.getMaterial(), material());
}

BOOST_AUTO_TEST_CASE(assigningMaterial) {
    auto s = testShape();
    auto m = material(color(1, 1, 1), 1, 0.9, 0.9, 200.0);

    s.setMaterial(m);

    BOOST_CHECK_EQUAL(s.getMaterial(), m);
}

BOOST_AUTO_TEST_CASE(intersectScaledShape) {
    auto r = ray(point(0, 0, -5), vector(0, 0, 1));
    auto s = testShape();

    s.setTransform(scaling(2, 2, 2));
    s.getIntersections(r);

    BOOST_CHECK_EQUAL(localRay.getOrigin(), point(0, 0, -2.5));
    BOOST_CHECK_EQUAL(localRay.getDirection(), vector(0, 0, 0.5));
}

BOOST_AUTO_TEST_CASE(intersectTranslatedShape) {
    auto r = ray(point(0, 0, -5), vector(0, 0, 1));
    auto s = testShape();

    s.setTransform(translation(5, 0, 0));
    s.getIntersections(r);

    BOOST_CHECK_EQUAL(localRay.getOrigin(), point(-5, 0, -5));
    BOOST_CHECK_EQUAL(localRay.getDirection(), vector(0, 0, 1));
}

BOOST_AUTO_TEST_CASE(translatedNormal) {
    auto s = testShape();

    s.setTransform(translation(0, 1, 0));
    auto n = s.getNormal(point(0, 1.70711, -0.70711));

    BOOST_CHECK_EQUAL(n, vector(0, 0.70711, -0.70711));
}

BOOST_AUTO_TEST_CASE(scaledRotatedNormal) {
    auto s = testShape();

    s.setTransform(zRotation(M_PI / 5).scale(1, 0.5, 1));
    auto n = s.getNormal(point(0, sqrt(2) / 2, -sqrt(2) / 2));

    BOOST_CHECK_EQUAL(n, vector(0, 0.97014, -0.24254));
}

BOOST_AUTO_TEST_SUITE_END()