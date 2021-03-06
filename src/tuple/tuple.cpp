#include "tuple/tuple.h"
#include "ray_tracer.h"

using namespace rayTracer;

tuple::tuple(const float &x, const float &y, const float &z, const float &w):
    x{x},
    y{y},
    z{z},
    w{w}
    {}

tuple::tuple():
    x{0},
    y{0},
    z{0},
    w{0}
    {}

const float &tuple::getX() const {
    return x;
}

const float &tuple::getY() const {
    return y;
}

const float &tuple::getZ() const {
    return z;
}

const float &tuple::getW() const {
    return w;
}

bool tuple::isPoint() const {
    return w == 1.0;
}

bool tuple::isVector() const {
    return w == 0.0;
}

tuple tuple::toPoint() const {
    return point(x, y, z);
}

tuple tuple::toVector() const {
    return vector(x, y, z);
}

float tuple::getMagnitude() const {
    return sqrt(
        pow(x, 2) +
        pow(y, 2) +
        pow(z, 2) +
        pow(w, 2)
    );
}

tuple tuple::normalized() const {
    auto magnitude = getMagnitude();
    return tuple(
        x / magnitude,
        y / magnitude,
        z / magnitude,
        w / magnitude
    );
}

float tuple::dot(const tuple &rhs) const {
    return x * rhs.x + 
        y * rhs.y + 
        z * rhs.z + 
        w * rhs.w;
}

tuple tuple::cross(const tuple &rhs) const {
    return vector(
        y * rhs.z - z * rhs.y,
        z * rhs.x - x * rhs.z,
        x * rhs.y - y * rhs.x
    );
}

tuple tuple::reflect(const tuple &rhs) const {
    return *this - rhs * 2 * dot(rhs);
}

tuple tuple::operator+(const tuple &rhs) const {
    return tuple(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

tuple tuple::operator-(const tuple &rhs) const {
    return tuple(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

tuple tuple::operator-() const {
    return tuple(-x, -y, -z, -w);
}

tuple tuple::operator*(const float &rhs) const {
    return tuple(x * rhs, y * rhs, z * rhs, w * rhs);
}

tuple tuple::operator/(const float &rhs) const {
    return tuple(x / rhs, y / rhs, z / rhs, w / rhs);
}

bool tuple::operator==(const tuple &rhs) const {
    return equalWithError(x, rhs.x) &&
        equalWithError(y, rhs.y) &&
        equalWithError(z, rhs.z) &&
        equalWithError(w, rhs.w);
}

std::ostream& rayTracer::operator<<(std::ostream &os, const tuple &t) {
    os << "tuple(" << t.x << "," << t.y << "," << t.z << "," << t.w << ")";
    return os;
}

tuple rayTracer::point(const float &x, const float &y, const float &z) {
    return tuple(x,y,z,1.0);
}

tuple rayTracer::point() {
    return tuple(0,0,0,1);
}

tuple rayTracer::vector(const float &x, const float &y, const float &z) {
    return tuple(x,y,z,0);
}

tuple rayTracer::vector() {
    return tuple();
}