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
    auto s = std::make_shared<sphere>(sphere());
    auto m = material();
    m.setColor(color(1, 0.2, 1));
    s->setMaterial(m);
    auto lightPosition = point(-10, 10, -10);
    auto lightColor = color(1, 1, 1);
    auto light = pointLight(lightPosition, lightColor);

    for (int y = 0; y < canvasPixels; y++) {
        auto worldY = half - (pixelSize * y);
        for (int x = 0; x < canvasPixels; x++) {
            auto worldX = -half + (pixelSize * x);
            auto position = point(worldX, worldY, wallZ);

            auto r = ray(rayOrigin, (position - rayOrigin).normalized());
            auto xs = s->getIntersections(r);

            auto hit = getHit(xs);
            if (hit != xs.end()) {
                auto point = r.getPosition((*hit).getT());
                auto normal = (*hit).getObject().getNormal(point);
                auto eye = -r.getDirection();

                wall.plot(x, y, (*hit).getObject().getMaterial().getLighting(light, point, eye, normal));
            }
        }
    }

    std::cout << wall;

    return 0;
}