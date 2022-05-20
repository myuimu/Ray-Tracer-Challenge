#pragma once
#include "matrix/matrix.h"
#include "ray/ray.h"
#include "canvas/canvas.h"
#include "world/world.h"

namespace rayTracer {
    class camera {
        private:
            int hSize;
            int vSize;
            float fov;
            float halfWidth;
            float halfHeight;
            float pixelSize;
            matrix transform;
            matrix inverseTransform;

            void calculatePixelSize();
        public:
            camera(const int &hSize, const int &vSize, const float &fov, const matrix &transform);
            camera(const int &hSize, const int &vSize, const float &fov);

            const int &getHSize() const;
            const int &getVSize() const;
            const float &getFov() const;
            const matrix &getTransform() const;
            const float &getPixelSize() const;

            ray getRayForPixel(const int &x, const int &y) const;
            canvas render(const world &w) const;
    };
};