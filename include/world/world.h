#pragma once
#include <iostream>
#include <memory>
#include "light/pointLight.h"
#include "shape/shape.h"
#include "intersection/intersection.h"
#include "color/color.h"
#include "intersection/computations.h"

namespace rayTracer {
    class world {
        private:
            std::vector<std::shared_ptr<shape>> objects;
            std::vector<pointLight> lights;
        public:
            world(const std::vector<std::shared_ptr<shape>> &objects, const std::vector<pointLight> &lights);

            std::vector<intersection> getIntersections(const ray &r) const;
            color shadeHit(const computations &comps, const int &remaining = 5) const;
            color colorAt(const ray &r, const int &remaining = 5) const;
            bool isShadowed(const tuple &p, const pointLight &light) const;
            color getReflectedColor(const computations &comps, const int &remaining) const;
    };
};