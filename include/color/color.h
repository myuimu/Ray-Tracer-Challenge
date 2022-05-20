#pragma once
#include <iostream>
#include <string>
#include "tuple/tuple.h"

namespace rayTracer {
    class color {
        private:
            tuple colorTuple;
        public:
            color(const float &red, const float &green, const float &blue);
            color(const tuple &colorTuple);
            color();

            float getRed() const;
            float getGreen() const;
            float getBlue() const;
            std::string toString() const;

            color operator+(const color &rhs) const;
            color operator-(const color &rhs) const;
            color operator*(const float &rhs) const;
            color operator*(const color &rhs) const;

            bool operator==(const color &rhs) const;

            friend std::ostream& operator<<(std::ostream &os, const color &c);
    };
    std::ostream& operator<<(std::ostream &os, const color &c);

    inline const color BLACK = color(0, 0, 0);
    inline const color WHITE = color(1, 1, 1);
};