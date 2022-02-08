#include "shape/sphere/sphere.h"
#include "ray_tracer.h"
#include <sstream>
#include <string>
#include <math.h>

using namespace rayTracer;

sphere::sphere():
    origin{point(0, 0, 0)},
    radius{1}
    {}

std::vector<intersection> sphere::getIntersections(const ray &r) const {
    auto newRay = r.transform(transform.getInverse());

    auto intersections = std::vector<intersection>();
    
    auto sphereToRay = newRay.getOrigin() - origin;

    auto a = newRay.getDirection().dot(newRay.getDirection());
    auto b = 2 * newRay.getDirection().dot(sphereToRay);
    auto c = sphereToRay.dot(sphereToRay) - 1;

    auto discriminant = pow(b, 2) - (4 * a * c);

    if (discriminant < 0) {
        return intersections;
    }
    intersections.push_back(intersection((-b - sqrt(discriminant))/(2 * a), *this));
    intersections.push_back(intersection((-b + sqrt(discriminant))/(2 * a), *this));

    return intersections;
}

bool sphere::isEqual(const shape &s) const {
    const sphere &sSphere = static_cast<const sphere &>(s);

    return origin == sSphere.origin && equalWithError(radius, sSphere.radius);
}

std::string sphere::toString() const {
    std::stringstream ss;
    ss << "Sphere(" << std::endl;
    ss << "Origin: " << origin << std::endl;
    ss << "Radius: " << radius << ")" << std::endl;
    return ss.str();
}