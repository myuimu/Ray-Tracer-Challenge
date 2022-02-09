#include "shape/shape.h"

using namespace rayTracer;

shape::shape():
    transform{IDENTITY_MATRIX},
    m{material()}
    {}

const matrix &shape::getTransform() const {
    return transform;
}

void shape::setTransform(const matrix &m) {
    transform = m;
}

const material &shape::getMaterial() const {
    return m;
}

void shape::setMaterial(const material &newMaterial) {
    m = newMaterial;
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