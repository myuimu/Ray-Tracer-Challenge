#pragma once
#include <iostream>
#include <string>
#include "tuple/tuple.h"

namespace rayTracer {
    class color {
        private:
            tuple colorTuple;
        public:
            color(const double &red, const double &green, const double &blue);
            color(const tuple &colorTuple);
            color();

            double getRed() const;
            double getGreen() const;
            double getBlue() const;
            std::string toString() const;

            color operator+(const color &rhs) const;
            color operator-(const color &rhs) const;
            color operator*(const double &rhs) const;
            color operator*(const color &rhs) const;

            bool operator==(const color &rhs) const;

            friend std::ostream& operator<<(std::ostream &os, const color &c);
    };

    inline const color BLACK = color(0, 0, 0);
};