#include "intersection/computations.h"
#include "intersection/intersection.h"
#include "shape/shape.h"

using namespace rayTracer;

computations::computations(const intersection &i, const ray &r) {
    t = i.getT();
    object = i.getObjectPtr();
    point = r.getPosition(t);
    eyeV = -r.getDirection();
    normalV = object->getNormal(point);

    if (normalV.dot(eyeV) < 0) {
        inside = true;
        normalV = -normalV;
    } else {
        inside = false;
    }
}

const double &computations::getT() const {
    return t;
}

const shape &computations::getObject() const {
    return *object.get();
}

const tuple &computations::getPoint() const {
    return point;
}

const tuple &computations::getEyeV() const {
    return eyeV;
}

const tuple &computations::getNormalV() const {
    return normalV;
}

const bool &computations::isInside() const {
    return inside;
}