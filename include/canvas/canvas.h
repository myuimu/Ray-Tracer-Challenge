#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "color/color.h"

namespace ray {
    class canvas {
        private:
            std::vector<std::vector<color>> pixels;
        public:
            canvas(const int &width, const int &height);
            canvas(const int &width, const int &height, const color &fillColor);

            int getWidth() const;
            int getHeight() const;
            const color &getPixel(const int &x, const int &y) const;

            void plot(const int &x, const int &y, const color &c);

            friend std::ostream& operator<<(std::ostream &os, const canvas &c);
    };
};