#pragma once
#include <vector>
#include <iostream>

namespace rayTracer {
    class shape;

    class intersection {
        private:
            double t;
            const shape &object;
        public:
            intersection(const double &t, const shape &object);
            intersection(const double &t, const shape &&) = delete;

            double getT() const;
            const shape &getObject() const;

            bool operator==(const intersection &rhs) const;

            friend std::ostream& operator<<(std::ostream &os, const intersection &i);
    };

    std::vector<rayTracer::intersection>::const_iterator getHit(const std::vector<intersection> &intersections);
};