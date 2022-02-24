#include "ray_tracer.h"

using namespace rayTracer;

plane::plane() {}

plane::plane(const matrix &transform, const material &m):
    shape(transform, m)
    {}

std::string plane::toString() const {
    return "Plane";
}

std::vector<intersection> plane::getLocalIntersections(const ray &r) const {
    if (abs(r.getDirection().getY()) < EPSILON) {
        return std::vector<intersection>();
    }

    auto t = -r.getOrigin().getY() / r.getDirection().getY();
    return std::vector<intersection>{intersection(t, shared_from_this())};
}

tuple plane::getLocalNormal(const tuple &p) const {
    return vector(0, 1, 0);
}