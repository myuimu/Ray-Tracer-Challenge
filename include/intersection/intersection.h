#pragma once
#include <vector>
#include <iostream>
#include <memory>

namespace rayTracer {
    class shape;

    class intersection {
        private:
            double t;
            std::shared_ptr<const shape> object;
        public:
            intersection(const double &t, const std::shared_ptr<const shape> &object);

            const double &getT() const;
            const shape &getObject() const;
            const std::shared_ptr<const shape> &getObjectPtr() const;

            bool operator==(const intersection &rhs) const;

            friend std::ostream& operator<<(std::ostream &os, const intersection &i);
    };
    std::ostream& operator<<(std::ostream &os, const intersection &i);

    std::vector<rayTracer::intersection>::const_iterator getHit(const std::vector<intersection> &intersections);
};