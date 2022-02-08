#include <iostream>
#include "ray_tracer.h"

using namespace rayTracer;

int main() {
    auto rayOrigin = point(0, 0, -5);
    int wallZ = 10;
    double wallSize = 7.0;
    int canvasPixels = 100;
    double pixelSize = wallSize / canvasPixels;
    double half = wallSize / 2;

    auto wall = canvas(canvasPixels, canvasPixels);
    auto c = color(1, 0, 0);
    auto s = sphere();

    for (int y = 0; y < canvasPixels; y++) {
        auto worldY = half - (pixelSize * y);
        for (int x = 0; x < canvasPixels; x++) {
            auto worldX = -half + (pixelSize * x);
            auto position = point(worldX, worldY, wallZ);

            auto r = ray(rayOrigin, (position - rayOrigin).normalized());
            auto xs = s.getIntersections(r);

            if (getHit(xs) != xs.end()) {
                wall.plot(x, y, c);
            }
        }
    }

    std::cout << wall;

    return 0;
}