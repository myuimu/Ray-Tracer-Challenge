#include "matrix/transformation.h"
#include "ray_tracer.h"
#include <math.h>

using namespace rayTracer;

matrix rayTracer::translation(const double &x, const double &y, const double &z) {
    auto values = std::vector<std::vector<double>>({
        {1, 0, 0, x},
        {0, 1, 0, y},
        {0, 0, 1, z},
        {0, 0, 0, 1}
    });
    return matrix(values);
}

matrix rayTracer::scaling(const double &x, const double &y, const double &z) {
    auto values = std::vector<std::vector<double>>({
        {x, 0, 0, 0},
        {0, y, 0, 0},
        {0, 0, z, 0},
        {0, 0, 0, 1}
    });
    return matrix(values);
}

matrix rayTracer::xRotation(const double &r) {
    auto values = std::vector<std::vector<double>>({
        {1, 0, 0, 0},
        {0, cos(r), -sin(r), 0},
        {0, sin(r), cos(r), 0},
        {0, 0, 0, 1}
    });
    return matrix(values);
}

matrix rayTracer::yRotation(const double &r) {
    auto values = std::vector<std::vector<double>>({
        {cos(r), 0, sin(r), 0},
        {0, 1, 0, 0},
        {-sin(r), 0, cos(r), 0},
        {0, 0, 0, 1}
    });
    return matrix(values);
}

matrix rayTracer::zRotation(const double &r) {
    auto values = std::vector<std::vector<double>>({
        {cos(r), -sin(r), 0, 0},
        {sin(r), cos(r), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    });
    return matrix(values);
}

matrix rayTracer::shearing(const double &xY, const double &xZ, const double &yX, const double &yZ, const double &zX, const double &zY) {
    auto values = std::vector<std::vector<double>>({
        {1, xY, xZ, 0},
        {yX, 1, yZ, 0},
        {zX, zY, 1, 0},
        {0, 0, 0, 1}
    });
    return matrix(values);
}