#include "color/color.h"
#include "ray_tracer.h"

#include <algorithm>
#include <math.h>

using namespace rayTracer;

color::color(const float &red, const float &green, const float &blue):
    colorTuple{vector(red, green, blue)}
    {}

color::color(const tuple &colorTuple):
    colorTuple(colorTuple)
    {}

color::color():
    colorTuple(tuple())
    {}

float color::getRed() const {
    return colorTuple.getX();
}

float color::getGreen() const {
    return colorTuple.getY();
}

float color::getBlue() const {
    return colorTuple.getZ();
}

std::string color::toString() const {
    auto red = std::to_string((int) round(std::clamp(getRed() * 255, 0.0f, 255.0f)));
    auto green = std::to_string((int) round(std::clamp(getGreen() * 255, 0.0f, 255.0f)));
    auto blue = std::to_string((int) round(std::clamp(getBlue() * 255, 0.0f, 255.0f)));

    return red + " " + green + " " + blue;
}

color color::operator+(const color &rhs) const {
    return color(colorTuple + rhs.colorTuple);
}

color color::operator-(const color &rhs) const {
    return color(colorTuple - rhs.colorTuple);
}

color color::operator*(const float &rhs) const {
    return color(colorTuple * rhs);
}

color color::operator*(const color &rhs) const {
    return color(
        getRed() * rhs.getRed(),
        getGreen() * rhs.getGreen(),
        getBlue() * rhs.getBlue()
    );
}

bool color::operator==(const color &rhs) const {
    return colorTuple == rhs.colorTuple;
}

std::ostream& rayTracer::operator<<(std::ostream &os, const color &c) {
    os << c.toString();
    return os;
}