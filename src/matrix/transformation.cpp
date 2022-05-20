#include "matrix/transformation.h"
#include "ray_tracer.h"
#include <math.h>

using namespace rayTracer;

matrix rayTracer::translation(const float &x, const float &y, const float &z) {
    auto values = std::vector<std::vector<float>>({
        {1, 0, 0, x},
        {0, 1, 0, y},
        {0, 0, 1, z},
        {0, 0, 0, 1}
    });
    return matrix(values);
}

matrix rayTracer::scaling(const float &x, const float &y, const float &z) {
    auto values = std::vector<std::vector<float>>({
        {x, 0, 0, 0},
        {0, y, 0, 0},
        {0, 0, z, 0},
        {0, 0, 0, 1}
    });
    return matrix(values);
}

matrix rayTracer::xRotation(const float &r) {
    auto values = std::vector<std::vector<float>>({
        {1, 0, 0, 0},
        {0, cos(r), -sin(r), 0},
        {0, sin(r), cos(r), 0},
        {0, 0, 0, 1}
    });
    return matrix(values);
}

matrix rayTracer::yRotation(const float &r) {
    auto values = std::vector<std::vector<float>>({
        {cos(r), 0, sin(r), 0},
        {0, 1, 0, 0},
        {-sin(r), 0, cos(r), 0},
        {0, 0, 0, 1}
    });
    return matrix(values);
}

matrix rayTracer::zRotation(const float &r) {
    auto values = std::vector<std::vector<float>>({
        {cos(r), -sin(r), 0, 0},
        {sin(r), cos(r), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    });
    return matrix(values);
}

matrix rayTracer::shearing(const float &xY, const float &xZ, const float &yX, const float &yZ, const float &zX, const float &zY) {
    auto values = std::vector<std::vector<float>>({
        {1, xY, xZ, 0},
        {yX, 1, yZ, 0},
        {zX, zY, 1, 0},
        {0, 0, 0, 1}
    });
    return matrix(values);
}

matrix rayTracer::viewTransform(const tuple &from, const tuple &to, const tuple &up) {
    auto forward = (to - from).normalized();
    auto upn = up.normalized();
    auto left = forward.cross(upn);
    auto trueUp = left.cross(forward);

    auto orientation = matrix(std::vector<std::vector<float>>({
        {left.getX(), left.getY(), left.getZ(), 0},
        {trueUp.getX(), trueUp.getY(), trueUp.getZ(), 0},
        {-forward.getX(), -forward.getY(), -forward.getZ(), 0},
        {0, 0, 0, 1}
    }));

    return orientation * translation(-from.getX(), -from.getY(), -from.getZ());
}