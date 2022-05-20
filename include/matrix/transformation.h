#pragma once
#include <iostream>
#include "matrix/matrix.h"

namespace rayTracer {
    matrix translation(const float &x, const float &y, const float &z);
    matrix scaling(const float &x, const float &y, const float &z);
    matrix xRotation(const float &r);
    matrix yRotation(const float &r);
    matrix zRotation(const float &r);
    matrix shearing(const float &xY, const float &xZ, const float &yX, const float &yZ, const float &zX, const float &zY);
    matrix viewTransform(const tuple &from, const tuple &to, const tuple &up);
}