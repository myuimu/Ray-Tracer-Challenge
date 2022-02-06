#pragma once
#include <iostream>

namespace ray {
    class tuple {
        private:
            double x;
            double y;
            double z;
            double w;
        public:
            tuple(const double &x, const double &y, const double &z, const double &w);
        
            bool isPoint() const;
            bool isVector() const;

            double getX() const;
            double getY() const;
            double getZ() const;
            double getW() const;

            bool operator==(const tuple &rhs) const;
            friend std::ostream& operator<<(std::ostream& os, const tuple& t);
    };

    tuple point(const double &x, const double &y, const double &z);
    tuple vector(const double &x, const double &y, const double &z);
};