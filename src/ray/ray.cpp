#include "ray/ray.h"

using namespace rayTracer;

ray::ray(const tuple &origin, const tuple &direction):
    origin{origin},
    direction{direction}
    {}

const tuple &ray::getOrigin() const {
    return origin;
}

const tuple &ray::getDirection() const {
    return direction;
}

tuple ray::getPosition(const double &t) const {
    return origin + (direction * t);
}

ray ray::transform(const matrix &m) const {
    return ray(m * origin, m * direction);
}

bool ray::operator==(const ray &rhs) const {
    return origin == rhs.origin &&
           direction == rhs.direction;
}

std::ostream &rayTracer::operator<<(std::ostream &os, const ray &r) {
    os << "Ray(" << std::endl;
    os << "Origin: " << r.origin << std::endl;
    os << "Direction: " << r.direction << ")" << std::endl;
    return os;
}