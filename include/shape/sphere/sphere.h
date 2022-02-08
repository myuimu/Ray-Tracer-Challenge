#pragma once
#include "shape/shape.h"
#include "tuple/tuple.h"

namespace rayTracer {
    class sphere: public shape {
        private:
            tuple origin;
            double radius;
        public:
            sphere();

            std::string toString() const;

            std::vector<double> getIntersections(const ray &r) const;

            virtual bool isEqual(const shape &s) const;
    };
};