#pragma once
#include <iostream>
#include <memory>
#include "light/pointLight.h"
#include "shape/shape.h"
#include "intersection/intersection.h"

namespace rayTracer {
    class world {
        private:
            std::vector<std::shared_ptr<shape>> objects;
            std::vector<pointLight> lights;
        public:
            world();
            world(const std::vector<std::shared_ptr<shape>> &objects, const std::vector<pointLight> &lights);

            std::vector<intersection> getIntersections(const ray &r) const;
    };
};