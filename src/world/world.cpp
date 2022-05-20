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

color world::shadeHit(const computations &comps, const int &remaining) const {
    auto c = BLACK;
    auto reflected = BLACK;
    auto refracted = BLACK;

    for (auto &light : lights) {
        c = c + comps.getObject().getMaterial().getLighting(
            light, 
            comps.getObject(),
            comps.getOverPoint(), 
            comps.getEyeV(), 
            comps.getNormalV(),
            isShadowed(comps.getOverPoint(), light));
        reflected = reflected + getReflectedColor(comps, remaining);
        refracted = refracted + getRefractedColor(comps, remaining);
    }

    if (comps.getObject().getMaterial().getReflective() > 0 && comps.getObject().getMaterial().getTransparency() > 0) {
        auto reflectance = comps.getReflectance();
        return c + reflected * reflectance + refracted * (1 - reflectance);
    }

    return c + reflected + refracted;
}

color world::colorAt(const ray &r, const int &remaining) const {
    auto intersections = getIntersections(r);
    auto hit = getHit(intersections);

    if (hit == intersections.end()) {
        return BLACK;
    }

    auto comps = computations(*hit, r, intersections);

    return shadeHit(comps, remaining);
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

color world::getReflectedColor(const computations &comps, const int &remaining) const {
    if (remaining < 1 || comps.getObject().getMaterial().getReflective() == 0) {
        return BLACK;
    }

    auto reflectRay = ray(comps.getOverPoint(), comps.getReflectV());
    auto reflectColor = colorAt(reflectRay, remaining - 1);

    return reflectColor * comps.getObject().getMaterial().getReflective();
}

color world::getRefractedColor(const computations &comps, const int &remaining) const {
    if (remaining < 1 || comps.getObject().getMaterial().getTransparency() == 0) {
        return BLACK;
    }

    auto indexRatio = comps.getExitRefractiveIndex() / comps.getEnterRefractiveIndex();
    auto cosThetaI = comps.getEyeV().dot(comps.getNormalV());
    auto sin2ThetaT = pow(indexRatio, 2) * (1 - pow(cosThetaI, 2));

    if (sin2ThetaT > 1) {
        return BLACK;
    }

    auto cosThetaT = sqrt(1.0 - sin2ThetaT);
    auto direction = comps.getNormalV() * (indexRatio * cosThetaI - cosThetaT) - comps.getEyeV() * indexRatio;
    auto refractRay = ray(comps.getUnderPoint(), direction);

    return colorAt(refractRay, remaining - 1) * comps.getObject().getMaterial().getTransparency();
}