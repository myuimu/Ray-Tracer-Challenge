#pragma once
#include "matrix/matrix.h"

namespace rayTracer {
    class color;
    class shape;
    class tuple;

    class pattern {
        protected:
            matrix transform;

            virtual color getColorForPoint(const tuple &p) const = 0;
        public:
            pattern();
            explicit pattern(const matrix &transform);
            virtual ~pattern() = default;

            const matrix &getTransform() const;
            void setTransform(const matrix &m);

            color getColorForShape(const shape &s, const tuple &p) const;
    };

    class testPattern : public pattern {
    private:
        color getColorForPoint(const tuple &p) const;
    };
};