#pragma once

#define EPSILON 0.00001

#include "tuple/tuple.h"
#include "color/color.h"
#include "matrix/matrix.h"
#include "matrix/transformation.h"
#include "canvas/canvas.h"
#include "intersection/intersection.h"
#include "ray/ray.h"
#include "shape/shape.h"
#include "shape/sphere/sphere.h"
#include "shape/material.h"
#include "light/pointLight.h"
#include "world/world.h"
#include "intersection/computations.h"
#include "world/camera.h"
#include "shape/plane/plane.h"

namespace rayTracer {
    bool equalWithError(const double &lhs, const double &rhs);
}