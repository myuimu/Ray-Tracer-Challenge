#pragma once
#include <iostream>
#include "math.h"

namespace ray {
    class tuple {
        private:
            double x;
            double y;
            double z;
            double w;
        public:
            tuple(const double &x, const double &y, const double &z, const double &w);

            double getX() const;
            double getY() const;
            double getZ() const;
            double getW() const;

            bool isPoint() const;
            bool isVector() const;

            double getMagnitude() const;
            tuple normalized() const;

            double dot(const tuple &rhs) const;
            tuple cross(const tuple &rhs) const;

            tuple operator+(const tuple &rhs) const;
            tuple operator-(const tuple &rhs) const;
            tuple operator-() const;
            tuple operator*(const double &rhs) const;
            tuple operator/(const double &rhs) const;

            bool operator==(const tuple &rhs) const;

            friend std::ostream& operator<<(std::ostream &os, const tuple &t);
    };

    tuple point(const double &x, const double &y, const double &z);
    tuple vector(const double &x, const double &y, const double &z);
};