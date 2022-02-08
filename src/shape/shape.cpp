#include "shape/shape.h"

using namespace rayTracer;

shape::shape():
    transform{IDENTITY_MATRIX}
    {}

const matrix &shape::getTransform() const {
    return transform;
}

void shape::setTransform(const matrix &m) {
    transform = m;
}

std::ostream &rayTracer::operator<<(std::ostream &os, const shape &s) {
    os << s.toString();
    return os;
}

bool shape::isEqual(const shape &s) const {
    return transform == s.transform;
}

bool shape::operator==(const shape &s) const {
    if(typeid(*this) != typeid(s))
        return false;
            
    return isEqual(s);
}