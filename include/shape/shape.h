#pragma once
#include <vector>
#include "ray/ray.h"

namespace rayTracer {
    class shape {
        private:
            virtual bool isEqual(const shape &s) const = 0;
        public:
            virtual std::vector<double> getIntersections(const ray &r) const = 0;

            virtual std::string toString() const = 0;

            bool operator==(const shape &s) const;

            friend std::ostream &operator<<(std::ostream &os, const shape &s);
    };
};