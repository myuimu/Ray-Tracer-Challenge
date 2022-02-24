#include "ray_tracer.h"
#include <math.h>

using namespace rayTracer;

gradient::gradient(const color &color1, const color &color2):
    color1{color1},
    color2{color2}
    {}

gradient::gradient(const color &color1, const color &color2, const matrix &transform):
    pattern(transform),
    color1{color1},
    color2{color2}
    {}

color gradient::getColorForPoint(const tuple &p) const {
    return color1 + (color2 - color1) * (p.getX() - floor(p.getX()));
}