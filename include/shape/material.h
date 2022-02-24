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
            double ambient;
            double diffuse;
            double specular;
            double shininess;
            std::shared_ptr<pattern> p;
        public:
            material();
            material(const color &c, 
                    const double &ambient, 
                    const double &diffuse,
                    const double &specular,
                    const double &shininess);
            material(const color &c, 
                    const double &ambient, 
                    const double &diffuse,
                    const double &specular,
                    const double &shininess,
                    const std::shared_ptr<pattern> p);
            
            const color &getColor() const;
            const double &getAmbient() const;
            const double &getDiffuse() const;
            const double &getSpecular() const;
            const double &getShininess() const;
            const pattern &getPattern() const;

            void setColor(const color &newColor);
            void setAmbient(const double &v);
            void setDiffuse(const double &v);
            void setSpecular(const double &v);
            void setShininess(const double &v);
            void setPattern(const std::shared_ptr<pattern> newPattern);

            color getLighting(const pointLight &light, const shape &object, const tuple &position, const tuple &eyeV, const tuple &normalV, const bool &inShadow) const;

            bool operator==(const material &rhs) const;

            friend std::ostream &operator<<(std::ostream &os, const material &m);
    };
    std::ostream &operator<<(std::ostream &os, const material &m);
};