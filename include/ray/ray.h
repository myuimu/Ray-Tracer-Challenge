#pragma once
#include <iostream>
#include "tuple/tuple.h"
#include "matrix/matrix.h"

namespace rayTracer {
    class ray {
        private:
            tuple origin;
            tuple direction;
        public:
            ray(const tuple &origin, const tuple &direction);

            const tuple &getOrigin() const;
            const tuple &getDirection() const;

            tuple getPosition(const double &t) const;
            ray transform(const matrix &m) const;

            bool operator==(const ray &rhs);

            friend std::ostream &operator<<(std::ostream &os, const ray &r);
    };
};