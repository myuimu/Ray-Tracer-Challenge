#pragma once
#include <iostream>
#include "matrix/matrix.h"

namespace ray {
    matrix translation(const double &x, const double &y, const double &z);
    matrix scaling(const double &x, const double &y, const double &z);
    matrix rotateX(const double &r);
    matrix rotateY(const double &r);
    matrix rotateZ(const double &r);
    matrix shearing(const double &xY, const double &xZ, const double &yX, const double &yZ, const double &zX, const double &zY);
}