#include <algorithm>
#include "ray_tracer.h"

using namespace rayTracer;

computations::computations(const intersection &i, const ray &r): computations(i, r, std::vector<intersection>{i}) {}

computations::computations(const intersection &i, const ray &r, const std::vector<intersection> &currentIntersections) {
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

    overPoint = point + (normalV * EPSILON);
    underPoint = point - (normalV * EPSILON);
    reflectV = r.getDirection().reflect(normalV);

    std::vector<std::shared_ptr<const shape>> containers;
    for(const auto& currentIntersection: currentIntersections) {
        if (currentIntersection == i) {
            if (containers.empty()) {
                exitRefractiveIndex = 1.0;
            } else {
                exitRefractiveIndex = containers.back()->getMaterial().getRefractiveIndex();
            }
        }

        auto containerInList = std::find(containers.begin(), containers.end(), currentIntersection.getObjectPtr());
        if (containerInList != containers.end()) {
            containers.erase(containerInList);
        } else {
            containers.emplace_back(currentIntersection.getObjectPtr());
        }

        if (currentIntersection == i) {
            if (containers.empty()) {
                enterRefractiveIndex = 1.0;
            } else {
                enterRefractiveIndex = containers.back()->getMaterial().getRefractiveIndex();
            }
            break;
        }
    }
}

double computations::getReflectance() const {
    auto cos = eyeV.dot(normalV);

    if (exitRefractiveIndex > enterRefractiveIndex) {
        auto n = exitRefractiveIndex / enterRefractiveIndex;
        auto sin2T = pow(n, 2) * (1.0 - pow(cos, 2));

        if (sin2T > 1.0) {
            return 1.0;
        }

        cos = sqrt(1.0 - sin2T);
    }

    auto r0 = pow((exitRefractiveIndex - enterRefractiveIndex) / (exitRefractiveIndex + enterRefractiveIndex), 2);

    return r0 + (1 - r0) * pow(1 - cos, 5);
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

const tuple &computations::getOverPoint() const {
    return overPoint;
}

const tuple &computations::getUnderPoint() const {
    return underPoint;
}

const tuple &computations::getEyeV() const {
    return eyeV;
}

const tuple &computations::getNormalV() const {
    return normalV;
}

const tuple &computations::getReflectV() const {
    return reflectV;
}

const bool &computations::isInside() const {
    return inside;
}

const double &computations::getExitRefractiveIndex() const {
    return exitRefractiveIndex;
}

const double &computations::getEnterRefractiveIndex() const {
    return enterRefractiveIndex;
}