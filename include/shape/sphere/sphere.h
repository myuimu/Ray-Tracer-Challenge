#pragma once
#include "shape/shape.h"
#include "tuple/tuple.h"

namespace rayTracer {
    class sphere: public shape {
        private:
            tuple origin;
            float radius;
        public:
            sphere();
            sphere(const matrix &transform, const material &m);

            std::string toString() const;

            std::vector<intersection> getLocalIntersections(const ray &r) const;
            tuple getLocalNormal(const tuple &p) const;

            bool isEqual(const shape &s) const;
    };

    sphere getGlassSphere();
};