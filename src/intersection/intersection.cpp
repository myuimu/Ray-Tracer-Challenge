#include "intersection/intersection.h"

using namespace rayTracer;

intersection::intersection(const double &t, shape *object):
    t{t},
    object{object}
    {}

double intersection::getT() const {
    return t;
}

const shape &intersection::getObject() const {
    return *object;
}

bool intersection::operator==(const intersection &rhs) const {
    return t == rhs.t && *object == *rhs.object;
}