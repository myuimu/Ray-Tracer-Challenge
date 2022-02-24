#include <iostream>
#include <memory>
#include <vector>
#include "ray_tracer.h"

using namespace rayTracer;

int main() {
    auto floor = std::make_shared<plane>(plane());
    auto middle = std::make_shared<sphere>(sphere(
        translation(-0.5, 1, 0.5),
        material(material(color(0.1, 1, 0.5), 0.1, 0.7, 0.3, 200, 
            std::make_shared<checker>(checker(WHITE, BLACK, scaling(0.5, 0.5, 0.5)))))));
    auto right = std::make_shared<sphere>(sphere(
        scaling(0.5, 0.5, 0.5).translate(1.5, 0.5, -0.5),
        material(material(color(0.5, 1, 0.1), 0.1, 0.7, 0.3, 200))));
    auto left = std::make_shared<sphere>(sphere(
        scaling(0.33, 0.33, 0.33).translate(-1.5, 0.33, -0.75),
        material(material(color(1, 0.8, 0.1), 0.1, 0.7, 0.3, 200))));

    auto light = pointLight(
        point(-10, 10, -10),
        color(1, 1, 1)
    );

    auto c = camera(500, 250, M_PI / 3, viewTransform(
        point(0, 1.5, -5),
        point(0, 1, 0),
        vector(0, 1, 0)
    ));

    auto spheres = std::vector<std::shared_ptr<shape>>{floor, middle, right, left};
    auto lights = std::vector<pointLight>{light};
    auto w = world(spheres, lights);

    std::cout << c.render(w);

    return 0;
}