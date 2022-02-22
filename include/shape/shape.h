#pragma once
#include <vector>
#include "ray/ray.h"
#include "intersection/intersection.h"
#include "matrix/matrix.h"
#include "material.h"

namespace rayTracer {
    class shape : public std::enable_shared_from_this<shape>{
        protected:
            matrix transform;
            material m;

            virtual bool isEqual(const shape &s) const;
        public:
            shape();
            shape(const matrix &transform, const material &m);
            virtual ~shape() = default;

            const matrix &getTransform() const;
            void setTransform(const matrix &m);

            const material &getMaterial() const;
            void setMaterial(const material &newMaterial);

            virtual std::vector<intersection> getIntersections(const ray &r) const = 0;
            virtual tuple getNormal(const tuple &p) const = 0;
            virtual std::string toString() const = 0;

            bool operator==(const shape &s) const;
            friend std::ostream &operator<<(std::ostream &os, const shape &s);
    };
};