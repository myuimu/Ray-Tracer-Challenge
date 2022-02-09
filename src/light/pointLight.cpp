#include "light/pointLight.h"

using namespace rayTracer;

pointLight::pointLight(const tuple &position, const color &intensity):
    position{position},
    intensity{intensity}
    {}

const tuple &pointLight::getPosition() const {
    return position;
}

const color &pointLight::getIntensity() const {
    return intensity;
}

bool pointLight::operator==(const pointLight &rhs) const {
    return position == rhs.position && intensity == rhs.intensity;
}

std::ostream &rayTracer::operator<<(std::ostream &os, const pointLight &rhs) {
    os << "pointLight(" << rhs.position << "," << rhs.intensity << ")" << std::endl;
    return os;
}