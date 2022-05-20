#include "world/camera.h"

using namespace rayTracer;

camera::camera(const int &hSize, const int &vSize, const float &fov, const matrix &transform):
    hSize{hSize},
    vSize{vSize},
    fov{fov},
    transform{transform},
    inverseTransform{transform.getInverse()} {
        calculatePixelSize();
    }

camera::camera(const int &hSize, const int &vSize, const float &fov):
    hSize{hSize},
    vSize{vSize},
    fov{fov},
    transform{IDENTITY_MATRIX},
    inverseTransform{transform.getInverse()} {
        calculatePixelSize();
    }

void camera::calculatePixelSize() {
    auto halfView = tan(fov / 2);
    auto aspect = (float) hSize / (float) vSize;

    if (aspect >= 1) {
        halfWidth = halfView;
        halfHeight = halfView / aspect;
    } else {
        halfWidth = halfView * aspect;
        halfHeight = halfView;
    }

    pixelSize = (halfWidth * 2) / hSize;
}

const int &camera::getHSize() const {
    return hSize;
}

const int &camera::getVSize() const {
    return vSize;
}

const float &camera::getFov() const {
    return fov;
}

const matrix &camera::getTransform() const {
    return transform;
}

const float &camera::getPixelSize() const {
    return pixelSize;
}

ray camera::getRayForPixel(const int &x, const int &y) const {
    auto xOffset = (x + 0.5) * pixelSize;
    auto yOffset = (y + 0.5) * pixelSize;

    auto worldX = halfWidth - xOffset;
    auto worldY = halfHeight - yOffset;

    auto pixel = inverseTransform * point(worldX, worldY, -1);
    auto origin = inverseTransform * point(0, 0, 0);
    auto direction = (pixel - origin).normalized();

    return ray(origin, direction);
}

canvas camera::render(const world &w) const {
    auto image = canvas(hSize, vSize);

    for (int y = 0; y < vSize; y++) {
        for (int x = 0; x < hSize; x++) {
            auto r = getRayForPixel(x, y);
            auto c = w.colorAt(r);
            image.plot(x, y, c);
        }
    }

    return image;
}