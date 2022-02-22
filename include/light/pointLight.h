#pragma once
#include <iostream>
#include "color/color.h"

namespace rayTracer {
    class pointLight {
        private:
            tuple position;
            color intensity;
        public:
            pointLight(const tuple &position, const color &intensity);

            const tuple &getPosition() const;
            const color &getIntensity() const;

            bool operator==(const pointLight &rhs) const;

            friend std::ostream &operator<<(std::ostream &os, const pointLight &rhs);
    };
    std::ostream &operator<<(std::ostream &os, const pointLight &rhs);
};