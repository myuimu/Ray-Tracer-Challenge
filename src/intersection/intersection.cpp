#include "intersection/intersection.h"
#include "shape/shape.h"

using namespace rayTracer;

intersection::intersection(const double &t, const std::shared_ptr<const shape> &object):
    t{t},
    object{object}
    {}

const double &intersection::getT() const {
    return t;
}

const shape &intersection::getObject() const {
    return *object;
}

const std::shared_ptr<const shape> &intersection::getObjectPtr() const {
    return object;
}

bool intersection::operator==(const intersection &rhs) const {
    return t == rhs.t && object == rhs.object;
}

std::ostream& rayTracer::operator<<(std::ostream &os, const intersection &i) {
    os << "Intersection(" << i.getT() << "," << i.getObject() << ")" << std::endl;
    return os;
}

std::vector<rayTracer::intersection>::const_iterator rayTracer::getHit(const std::vector<intersection> &intersections) {
    int currentHit = intersections.size();
    for (int i = 0; i < intersections.size(); i++) {
        if (currentHit > i || intersections[currentHit].getT() < 0 || (
            intersections[i].getT() >= 0 && 
            intersections[i].getT() < intersections[currentHit].getT())) {
            currentHit = i;
        }
    }
    if (currentHit != intersections.size() && intersections[currentHit].getT() < 0) {
        currentHit = intersections.size();
    }
    return intersections.begin() + currentHit;
}