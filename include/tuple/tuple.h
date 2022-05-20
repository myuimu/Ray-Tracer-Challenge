#pragma once
#include <iostream>
#include "math.h"

namespace rayTracer {
    class tuple {
        private:
            float x;
            float y;
            float z;
            float w;
        public:
            tuple(const float &x, const float &y, const float &z, const float &w);
            tuple();

            const float &getX() const;
            const float &getY() const;
            const float &getZ() const;
            const float &getW() const;

            bool isPoint() const;
            bool isVector() const;

            tuple toPoint() const;
            tuple toVector() const;

            float getMagnitude() const;
            tuple normalized() const;

            float dot(const tuple &rhs) const;
            tuple cross(const tuple &rhs) const;
            tuple reflect(const tuple &rhs) const;

            tuple operator+(const tuple &rhs) const;
            tuple operator-(const tuple &rhs) const;
            tuple operator-() const;
            tuple operator*(const float &rhs) const;
            tuple operator/(const float &rhs) const;

            bool operator==(const tuple &rhs) const;

            friend std::ostream& operator<<(std::ostream &os, const tuple &t);
    };
    std::ostream& operator<<(std::ostream &os, const tuple &t);

    tuple point(const float &x, const float &y, const float &z);
    tuple point();
    tuple vector(const float &x, const float &y, const float &z);
    tuple vector();
};