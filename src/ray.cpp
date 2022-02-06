#include <math.h>
#include "ray.h"

bool ray::equalWithError(const double &lhs, const double &rhs) {
    if (abs(lhs - rhs) < EPSILON)
        return true;
    return false;
}