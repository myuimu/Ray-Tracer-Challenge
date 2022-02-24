#pragma once
#include "color/color.h"
#include "light/pointLight.h"
#include <iostream>

namespace rayTracer {
    class material {
        private:
            color c;
            double ambient;
            double diffuse;
            double specular;
            double shininess;
        public:
            material();
            material(const color &c, 
                    const double &ambient, 
                    const double &diffuse,
                    const double &specular,
                    const double &shininess);
            
            const color &getColor() const;
            const double &getAmbient() const;
            const double &getDiffuse() const;
            const double &getSpecular() const;
            const double &getShininess() const;

            void setColor(const color &newColor);
            void setAmbient(const double &v);
            void setDiffuse(const double &v);
            void setSpecular(const double &v);
            void setShininess(const double &v);

            color getLighting(const pointLight &light, const tuple &position, const tuple &eyeV, const tuple &normalV, const bool &inShadow) const;

            bool operator==(const material &rhs) const;

            friend std::ostream &operator<<(std::ostream &os, const material &m);
    };
    std::ostream &operator<<(std::ostream &os, const material &m);
};