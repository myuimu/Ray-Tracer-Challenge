#include "tuple/tuple.h"
#include "ray.h"

ray::tuple::tuple(const double &x, const double &y, const double &z, const double &w):
    x{x},
    y{y},
    z{z},
    w{w}
    {}

bool ray::tuple::isPoint() const {
    return w == 1.0;
}

bool ray::tuple::isVector() const {
    return w == 0.0;
}

double ray::tuple::getX() const {
    return x;
}

double ray::tuple::getY() const {
    return y;
}

double ray::tuple::getZ() const {
    return z;
}

double ray::tuple::getW() const {
    return w;
}

bool ray::tuple::operator==(const tuple &rhs) const{
    return equalWithError(x, rhs.x) &&
        equalWithError(y, rhs.y) &&
        equalWithError(z, rhs.z) &&
        equalWithError(w, rhs.w);
}

std::ostream& ray::operator<<(std::ostream& os, const ray::tuple& t) {
    os << "tuple(" << t.x << "," << t.y << "," << t.z << "," << t.w << ")";
    return os;
}

ray::tuple ray::point(const double &x, const double &y, const double &z) {
    return tuple(x,y,z,1.0);
}

ray::tuple ray::vector(const double &x, const double &y, const double &z) {
    return tuple(x,y,z,0);
}