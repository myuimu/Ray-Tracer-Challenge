#include "canvas/canvas.h"

using namespace ray;

canvas::canvas(const int &width, const int &height):
    pixels{std::vector<std::vector<color>>(height, std::vector<color>(width, color()))}
    {}

canvas::canvas(const int &width, const int &height, const color &fillColor):
    pixels{std::vector<std::vector<color>>(height, std::vector<color>(width, fillColor))}
    {}

int canvas::getWidth() const {
    if (pixels.size() > 0) {
        return pixels[0].size();
    }
    return 0;
}

int canvas::getHeight() const {
    return pixels.size();
}

const color &canvas::getPixel(const int &x, const int &y) const {
    return pixels.at(y).at(x);
}

void canvas::plot(const int &x, const int &y, const color &c) {
    pixels.at(y).at(x) = c;
}

std::ostream& ray::operator<<(std::ostream &os, const canvas &c) {
    os << "P3" << std::endl;
    os << c.getWidth() << " " << c.getHeight() << std::endl;
    os << 255 << std::endl;
    for(auto &line : c.pixels) {
        int pixelCount = 0;
        for(auto &pixel : line) {
            auto pixelString = pixel.toString();
            pixelCount += pixelString.length() + 1;
            if (pixelCount > 70) {
                pixelCount = 0;
                os << std::endl;
            }

            os << pixelString << " ";
        }
        os << std::endl;
    }
    return os;
}