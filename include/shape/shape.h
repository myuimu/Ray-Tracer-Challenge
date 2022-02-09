#pragma once
#include <vector>
#include "ray/ray.h"
#include "intersection/intersection.h"
#include "matrix/matrix.h"

namespace rayTracer {
    class shape {
        protected:
            matrix transform;

            virtual bool isEqual(const shape &s) const;
        public:
            shape();

            const matrix &getTransform() const;
            void setTransform(const matrix &m);

            virtual std::vector<intersection> getIntersections(const ray &r) const = 0;
            virtual tuple getNormal(const tuple &p) const = 0;
            virtual std::string toString() const = 0;

            bool operator==(const shape &s) const;
            friend std::ostream &operator<<(std::ostream &os, const shape &s);
    };
};