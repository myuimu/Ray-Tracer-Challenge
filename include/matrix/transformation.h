#pragma once
#include <iostream>
#include "matrix/matrix.h"

namespace rayTracer {
    matrix translation(const double &x, const double &y, const double &z);
    matrix scaling(const double &x, const double &y, const double &z);
    matrix xRotation(const double &r);
    matrix yRotation(const double &r);
    matrix zRotation(const double &r);
    matrix shearing(const double &xY, const double &xZ, const double &yX, const double &yZ, const double &zX, const double &zY);
    matrix viewTransform(const tuple &from, const tuple &to, const tuple &up);
}