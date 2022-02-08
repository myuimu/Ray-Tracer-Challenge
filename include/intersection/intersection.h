#pragma once
#include "shape/shape.h"

namespace rayTracer {
    class intersection {
        private:
            double t;
            shape *object;
        public:
            intersection(const double &t, shape *object);

            double getT() const;
            const shape &getObject() const;

            bool operator==(const intersection &rhs) const;
    };
};