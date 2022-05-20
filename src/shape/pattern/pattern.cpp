#include "ray_tracer.h"

using namespace rayTracer;

pattern::pattern():
    transform{IDENTITY_MATRIX}
    {}

pattern::pattern(const matrix &transform):
    transform{transform}
    {}

const matrix &pattern::getTransform() const {
    return transform;
}

void pattern::setTransform(const matrix &m) {
    transform = m;
}

color pattern::getColorForShape(const shape &s, const tuple &p) const {
    auto objectPoint = s.getTransform().getInverse() * p;
    auto patternPoint = transform.getInverse() * objectPoint;
    return getColorForPoint(patternPoint);
}

color testPattern::getColorForPoint(const tuple &p) const {
    return color(p.getX(), p.getY(), p.getZ());
}