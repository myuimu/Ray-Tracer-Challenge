#include "ray_tracer.h"
#include <math.h>
#include <iostream>

using namespace rayTracer;

ring::ring(const color &color1, const color &color2):
    color1{color1},
    color2{color2}
    {}

ring::ring(const color &color1, const color &color2, const matrix &transform):
    pattern(transform),
    color1{color1},
    color2{color2}
    {}

color ring::getColorForPoint(const tuple &p) const {
    return (int) floor(sqrt(pow(p.getX(), 2) + pow(p.getZ(), 2))) % 2 == 0 ? color1 : color2;
}