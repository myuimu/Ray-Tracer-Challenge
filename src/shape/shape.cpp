#include "shape/shape.h"

using namespace rayTracer;

std::ostream &rayTracer::operator<<(std::ostream &os, const shape &s) {
    os << s.toString();
    return os;
}

bool shape::operator==(const shape &s) const {
    if(typeid(*this) != typeid(s))
        return false;
            
    return isEqual(s);
}