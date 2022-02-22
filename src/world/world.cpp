#include "world/world.h"
#include <algorithm>

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