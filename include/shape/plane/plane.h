#pragma once
#include "shape/shape.h"

namespace rayTracer {
    class plane : public shape {
        private:
            std::string toString() const;
            std::vector<intersection> getLocalIntersections(const ray &r) const;
            tuple getLocalNormal(const tuple &p) const;
    };
};