#pragma once
#include "shape/pattern/pattern.h"
#include "color/color.h"

namespace rayTracer {
    class ring : public pattern {
        private:
            color color1;
            color color2;

            color getColorForPoint(const tuple &p) const;
        public:
            ring(const color &color1, const color &color2);
            ring(const color &color1, const color &color2, const matrix &transform);
    };
};