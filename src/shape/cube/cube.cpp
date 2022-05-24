#include "ray_tracer.h"

using namespace rayTracer;

cube::cube():
    shape()
    {}

cube::cube(const matrix &transform, const material &m):
    shape(transform, m)
    {}

std::vector<intersection> cube::getLocalIntersections(const ray &r) const {
    auto xMinMax = checkAxis(r.getOrigin().getX(), r.getDirection().getX());
    auto yMinMax = checkAxis(r.getOrigin().getY(), r.getDirection().getY());
    auto zMinMax = checkAxis(r.getOrigin().getZ(), r.getDirection().getZ());

    float tMin = xMinMax.first;
    float tMax = xMinMax.second;
    if (yMinMax.first > tMin) {
        tMin = yMinMax.first;
    }
    if (yMinMax.second < tMax) {
        tMax = yMinMax.second;
    }
    if (zMinMax.first > tMin) {
        tMin = zMinMax.first;
    }
    if (zMinMax.second < tMax) {
        tMax = zMinMax.second;
    }

    if (tMin > tMax) {
        return {};
    }

    return {intersection(tMin, shared_from_this()), intersection(tMax, shared_from_this())};
}

tuple cube::getLocalNormal(const tuple &p) const {
    auto maxC = abs(p.getX());
    if (abs(p.getY()) > maxC) {
        maxC = abs(p.getY());
    }
    if (abs(p.getZ()) > maxC) {
        maxC = abs(p.getZ());
    }

    if (maxC == abs(p.getX())) {
        return vector(p.getX(), 0, 0);
    } else if (maxC == abs(p.getY())) {
        return vector(0, p.getY(), 0);
    }
    return vector(0, 0, p.getZ());
};

std::pair<float, float> cube::checkAxis(const float &origin, const float &direction) {
    auto tMin = (-1 - origin) / direction;
    auto tMax = (1 - origin) / direction;

    if (tMin > tMax) {
        return std::make_pair(tMax, tMin);
    }

    return std::make_pair(tMin, tMax);
}

bool cube::isEqual(const shape &s) const {
    return shape::isEqual(s);
}

std::string cube::toString() const {
    return "Cube()";
}