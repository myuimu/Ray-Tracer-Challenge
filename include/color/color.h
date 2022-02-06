#pragma once
#include <iostream>
#include "tuple/tuple.h"

namespace ray {
    class color {
        private:
            tuple colorTuple;
        public:
            color(const double &red, const double &green, const double &blue);
            color(const tuple &colorTuple);

            double getRed() const;
            double getGreen() const;
            double getBlue() const;

            color operator+(const color &rhs) const;
            color operator-(const color &rhs) const;
            color operator*(const double &rhs) const;
            color operator*(const color &rhs) const;

            bool operator==(const color &rhs) const;

            friend std::ostream& operator<<(std::ostream &os, const color &c);
    };
};