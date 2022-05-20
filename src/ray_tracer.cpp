#include <math.h>
#include "ray_tracer.h"

bool rayTracer::equalWithError(const float &lhs, const float &rhs) {
    if (abs(lhs - rhs) < EPSILON)
        return true;
    return false;
}