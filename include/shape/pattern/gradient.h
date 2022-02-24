#pragma once
#include "shape/pattern/pattern.h"
#include "color/color.h"

namespace rayTracer {
    class gradient : public pattern {
        private:
            color color1;
            color color2;

            color getColorForPoint(const tuple &p) const;
        public:
            gradient(const color &color1, const color &color2);
            gradient(const color &color1, const color &color2, const matrix &transform);
    };
};