#pragma once
#include "color/color.h"
#include "light/pointLight.h"
#include "shape/pattern/pattern.h"
#include <iostream>
#include <memory>

namespace rayTracer {
    class material {
        private:
            color c;
            std::shared_ptr<pattern> p;
            float ambient;
            float diffuse;
            float specular;
            float shininess;
            float reflective;
            float transparency;
            float refractiveIndex;
        public:
            explicit material(const color &c = color(1, 1, 1),
                    const float &ambient = 0.1,
                    const float &diffuse = 0.9,
                    const float &specular = 0.9,
                    const float &shininess = 200.0,
                    const float &reflective = 0.0,
                    const float &transparency = 0.0,
                    const float &refractiveIndex = 1.0);
            material(const color &c, 
                    const float &ambient,
                    const float &diffuse,
                    const float &specular,
                    const float &shininess,
                    const float &reflective,
                    const float &transparency,
                    const float &refractiveIndex,
                    const std::shared_ptr<pattern> &p);
            
            const color &getColor() const;
            const float &getAmbient() const;
            const float &getDiffuse() const;
            const float &getSpecular() const;
            const float &getShininess() const;
            const float &getReflective() const;
            const float &getTransparency() const;
            const float &getRefractiveIndex() const;
            const pattern &getPattern() const;

            void setColor(const color &newColor);
            void setAmbient(const float &v);
            void setDiffuse(const float &v);
            void setSpecular(const float &v);
            void setShininess(const float &v);
            void setReflective(const float &v);
            void setTransparency(const float &v);
            void setRefractiveIndex(const float &v);
            void setPattern(const std::shared_ptr<pattern> &newPattern);

            color getLighting(const pointLight &light, const shape &object, const tuple &position, const tuple &eyeV, const tuple &normalV, const bool &inShadow) const;

            bool operator==(const material &rhs) const;

            friend std::ostream &operator<<(std::ostream &os, const material &m);
    };
    std::ostream &operator<<(std::ostream &os, const material &m);
};