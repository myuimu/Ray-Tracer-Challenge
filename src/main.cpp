#include <iostream>
#include <memory>
#include <vector>
#include "ray_tracer.h"

using namespace rayTracer;

int main() {
    auto floor = std::make_shared<plane>(plane(
        IDENTITY_MATRIX, 
        material(color(1, 1, 1), 0.1, 0.7, 0.3, 200, 0.5, 0.0, 1.0,
            std::make_shared<checker>(checker(WHITE, BLACK)))));
    auto mirror = std::make_shared<plane>(plane(
        xRotation(M_PI_2).rotateY(M_PI_4).translate(0, 0, 5), 
        material(color(1, 1, 1), 0, 0.1, 0.2, 10, 1)));
    auto middle = std::make_shared<sphere>(sphere(
        translation(-0.5, 1, 0.5),
        material(color(1, 1, 1), 0.1, 0.9, 0.9, 200, 0.5, 0.5, 1.5)));
    auto right = std::make_shared<sphere>(sphere(
        scaling(0.5, 0.5, 0.5).translate(1.5, 0.5, -0.5),
        material(color(0.5, 1, 0.1), 0.1, 0.7, 0.3, 200, 0)));
    auto left = std::make_shared<sphere>(sphere(
        scaling(0.33, 0.33, 0.33).translate(-1.5, 0.33, -0.75),
        material(color(1, 0.8, 0.1), 0.1, 0.7, 0.3, 200, 0)));

    auto light = pointLight(
        point(-10, 100, -10),
        color(1, 1, 1)
    );

    auto c = camera(1000, 500, M_PI / 3, viewTransform(
        point(0, 1.5, -5),
        point(0, 1, 0),
        vector(0, 1, 0)
    ));

    auto shapes = std::vector<std::shared_ptr<shape>>{floor, mirror, middle, right, left};
    auto lights = std::vector<pointLight>{light};
    auto w = world(shapes, lights);

    std::cout << c.render(w);

    return 0;
}