#pragma once

#define EPSILON 0.00001

#include "tuple/tuple.h"
#include "color/color.h"
#include "matrix/matrix.h"
#include "matrix/transformation.h"

namespace rayTracer {
    bool equalWithError(const double &lhs, const double &rhs);
}