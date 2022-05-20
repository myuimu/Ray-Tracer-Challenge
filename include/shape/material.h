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
            double ambient;
            double diffuse;
            double specular;
            double shininess;
            double reflective;
            double transparency;
            double refractiveIndex;
        public:
            explicit material(const color &c = color(1, 1, 1),
                    const double &ambient = 0.1,
                    const double &diffuse = 0.9,
                    const double &specular = 0.9,
                    const double &shininess = 200.0,
                    const double &reflective = 0.0,
                    const double &transparency = 0.0,
                    const double &refractiveIndex = 1.0);
            material(const color &c, 
                    const double &ambient, 
                    const double &diffuse,
                    const double &specular,
                    const double &shininess,
                    const double &reflective,
                    const double &transparency,
                    const double &refractiveIndex,
                    const std::shared_ptr<pattern> &p);
            
            const color &getColor() const;
            const double &getAmbient() const;
            const double &getDiffuse() const;
            const double &getSpecular() const;
            const double &getShininess() const;
            const double &getReflective() const;
            const double &getTransparency() const;
            const double &getRefractiveIndex() const;
            const pattern &getPattern() const;

            void setColor(const color &newColor);
            void setAmbient(const double &v);
            void setDiffuse(const double &v);
            void setSpecular(const double &v);
            void setShininess(const double &v);
            void setReflective(const double &v);
            void setTransparency(const double &v);
            void setRefractiveIndex(const double &v);
            void setPattern(const std::shared_ptr<pattern> &newPattern);

            color getLighting(const pointLight &light, const shape &object, const tuple &position, const tuple &eyeV, const tuple &normalV, const bool &inShadow) const;

            bool operator==(const material &rhs) const;

            friend std::ostream &operator<<(std::ostream &os, const material &m);
    };
    std::ostream &operator<<(std::ostream &os, const material &m);
};