#include "color/color.h"
#include "ray_tracer.h"

#include <algorithm>
#include <math.h>

using namespace rayTracer;

color::color(const double &red, const double &green, const double &blue):
    colorTuple{vector(red, green, blue)}
    {}

color::color(const tuple &colorTuple):
    colorTuple(colorTuple)
    {}

color::color():
    colorTuple(tuple())
    {}

double color::getRed() const {
    return colorTuple.getX();
}

double color::getGreen() const {
    return colorTuple.getY();
}

double color::getBlue() const {
    return colorTuple.getZ();
}

std::string color::toString() const {
    auto red = std::to_string((int) round(std::clamp(getRed() * 255, 0.0, 255.0)));
    auto green = std::to_string((int) round(std::clamp(getGreen() * 255, 0.0, 255.0)));
    auto blue = std::to_string((int) round(std::clamp(getBlue() * 255, 0.0, 255.0)));

    return red + " " + green + " " + blue;
}

color color::operator+(const color &rhs) const {
    return color(colorTuple + rhs.colorTuple);
}

color color::operator-(const color &rhs) const {
    return color(colorTuple - rhs.colorTuple);
}

color color::operator*(const double &rhs) const {
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