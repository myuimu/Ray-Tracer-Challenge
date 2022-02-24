#include "ray_tracer.h"
#include <math.h>

using namespace rayTracer;

checker::checker(const color &color1, const color &color2):
    color1{color1},
    color2{color2}
    {}

checker::checker(const color &color1, const color &color2, const matrix &transform):
    pattern(transform),
    color1{color1},
    color2{color2}
    {}

color checker::getColorForPoint(const tuple &p) const {
    return (int) (floor(p.getX()) + floor(p.getY()) + floor(p.getZ())) % 2 == 0 ? color1 : color2;
}