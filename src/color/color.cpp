#include "color/color.h"
#include "ray.h"

using namespace ray;

color::color(const double &red, const double &green, const double &blue):
    colorTuple{vector(red, green, blue)}
    {}

color::color(const tuple &colorTuple):
    colorTuple(colorTuple)
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

std::ostream& ray::operator<<(std::ostream &os, const color &c) {
    os << "color(" << c.getRed() << "," << c.getGreen() << "," << c.getBlue() << ")";
    return os;
}