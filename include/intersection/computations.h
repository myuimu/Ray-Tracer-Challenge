#pragma once
#include <memory>
#include "tuple/tuple.h"
#include "ray/ray.h"

namespace rayTracer {
    class intersection;
    class shape;

    class computations {
        private:
            double t;
            std::shared_ptr<const shape> object;
            tuple point;
            tuple eyeV;
            tuple normalV;
            bool inside;
        public:
            computations(const intersection &i, const ray &r);

            const double &getT() const;
            const shape &getObject() const;
            const tuple &getPoint() const;
            const tuple &getEyeV() const;
            const tuple &getNormalV() const;
            const bool &isInside() const;
    };
};