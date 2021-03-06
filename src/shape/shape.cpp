#include "shape/shape.h"

using namespace rayTracer;

shape::shape():
    transform{IDENTITY_MATRIX},
    m{material()}
    {}

shape::shape(const matrix &transform, const material &m):
    transform{transform},
    m{m}
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

std::vector<intersection> shape::getIntersections(const ray &r) const {
    return getLocalIntersections(r.transform(transform.getInverse()));
}

tuple shape::getNormal(const tuple &p) const {
    auto inverseTransform = transform.getInverse();

    auto localPoint = inverseTransform * p;
    auto localNormal = getLocalNormal(localPoint);

    auto worldNormal = inverseTransform.getTranspose() * localNormal;
    return worldNormal.toVector().normalized();
}

std::ostream &rayTracer::operator<<(std::ostream &os, const shape &s) {
    os << s.toString();
    return os;
}

bool shape::isEqual(const shape &s) const {
    return transform == s.transform && m == s.m;
}

bool shape::operator==(const shape &s) const {
    if(typeid(*this) != typeid(s))
        return false;
            
    return isEqual(s);
}