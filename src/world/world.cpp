#include "world/world.h"
#include <algorithm>
#include <iostream>

using namespace rayTracer;

world::world(const std::vector<std::shared_ptr<shape>> &objects, const std::vector<pointLight> &lights):
    objects{objects},
    lights{lights}
    {}

std::vector<intersection> world::getIntersections(const ray &r) const {
    std::vector<intersection> intersections;

    for (auto &o : objects) {
        auto oIntersections = o->getIntersections(r);
        intersections.insert(intersections.end(), oIntersections.begin(), oIntersections.end());
    }

    std::sort(intersections.begin(), intersections.end(), [](const intersection& lhs, const intersection& rhs) {
      return lhs.getT() < rhs.getT();
    });

    return intersections;
}

color world::shadeHit(const computations &comps) const {
    auto c = BLACK;

    for (auto &light : lights) {
        c = c + comps.getObject().getMaterial().getLighting(
            light, 
            comps.getObject(),
            comps.getPoint(), 
            comps.getEyeV(), 
            comps.getNormalV(),
            isShadowed(comps.getOverPoint(), light));
    }

    return c;
}

color world::colorAt(const ray &r) const {
    auto intersections = getIntersections(r);
    auto hit = getHit(intersections);

    if (hit == intersections.end()) {
        return BLACK;
    }

    auto comps = computations(*hit, r);

    return shadeHit(comps);
}

bool world::isShadowed(const tuple &p, const pointLight &light) const {
    auto v = light.getPosition() - p;
    auto distance = v.getMagnitude();
    auto direction = v.normalized();

    auto r = ray(p, direction);
    auto intersections = getIntersections(r);
    auto hit = getHit(intersections);

    if (hit != intersections.end() && (*hit).getT() < distance) {
        return true;
    }
    return false;
}