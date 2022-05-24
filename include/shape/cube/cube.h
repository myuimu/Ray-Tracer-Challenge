#pragma once
#include "shape/shape.h"
#include "tuple/tuple.h"

namespace rayTracer {
    class cube: public shape {
        private:
            static std::pair<float, float> checkAxis(const float &origin, const float &direction) ;
        public:
            cube();
            cube(const matrix &transform, const material &m);

            std::string toString() const;

            std::vector<intersection> getLocalIntersections(const ray &r) const;
            tuple getLocalNormal(const tuple &p) const;

            bool isEqual(const shape &s) const;
    };
};
