#include "ray_tracer.h"
#include <math.h>

using namespace rayTracer;

stripe::stripe(const color &color1, const color &color2):
    color1{color1},
    color2{color2}
    {}

stripe::stripe(const color &color1, const color &color2, const matrix &transform):
    pattern(transform),
    color1{color1},
    color2{color2}
    {}

color stripe::getColorForPoint(const tuple &p) const {
    return (int) floor(p.getX()) % 2 == 0 ? color1 : color2;
}