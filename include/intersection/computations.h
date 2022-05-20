#pragma once
#include <memory>
#include "tuple/tuple.h"
#include "ray/ray.h"

namespace rayTracer {
    class intersection;
    class shape;

    class computations {
        private:
            float t;
            std::shared_ptr<const shape> object;
            tuple point;
            tuple overPoint;
            tuple underPoint;
            tuple eyeV;
            tuple normalV;
            tuple reflectV;
            bool inside;
            float exitRefractiveIndex;
            float enterRefractiveIndex;
        public:
            computations(const intersection &i, const ray &r);
            computations(const intersection &i, const ray &r, const std::vector<intersection> &currentIntersections);

            float getReflectance() const;

            const float &getT() const;
            const shape &getObject() const;
            const tuple &getPoint() const;
            const tuple &getOverPoint() const;
            const tuple &getUnderPoint() const;
            const tuple &getEyeV() const;
            const tuple &getNormalV() const;
            const tuple &getReflectV() const;
            const bool &isInside() const;
            const float &getExitRefractiveIndex() const;
            const float &getEnterRefractiveIndex() const;
    };
};