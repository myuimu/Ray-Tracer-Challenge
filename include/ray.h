#pragma once

#define EPSILON 0.00001

#include "tuple/tuple.h"
#include "color/color.h"

namespace ray {
    bool equalWithError(const double &lhs, const double &rhs);
}