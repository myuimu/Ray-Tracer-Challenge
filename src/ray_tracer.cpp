#include <math.h>
#include "ray_tracer.h"

bool ray::equalWithError(const double &lhs, const double &rhs) {
    if (abs(lhs - rhs) < EPSILON)
        return true;
    return false;
}