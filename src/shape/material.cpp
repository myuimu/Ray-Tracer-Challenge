#include "shape/material.h"

using namespace rayTracer;

material::material():
    c{color(1, 1, 1)},
    ambient{0.1},
    diffuse{0.9},
    specular{0.9},
    shininess{200.0}
    {}

material::material(const color &c, 
                    const double &ambient, 
                    const double &diffuse,
                    const double &specular,
                    const double &shininess) {
    setColor(c);
    setAmbient(ambient);
    setDiffuse(diffuse);
    setSpecular(specular);
    setShininess(shininess);
}
            
const color &material::getColor() const {
    return c;
}

const double &material::getAmbient() const {
    return ambient;
}

const double &material::getDiffuse() const {
    return diffuse;
}

const double &material::getSpecular() const {
    return specular;
}

const double &material::getShininess() const {
    return shininess;
}

void material::setColor(const color &newColor) {
    c = newColor;
}

void material::setAmbient(const double &v) {
    if(v < 0) {
        throw std::invalid_argument("Cannot set ambient value < 0!");
    }
    ambient = v;
}

void material::setDiffuse(const double &v) {
    if(v < 0) {
        throw std::invalid_argument("Cannot set diffuse value < 0!");
    }
    diffuse = v;
}

void material::setSpecular(const double &v) {
    if(v < 0) {
        throw std::invalid_argument("Cannot set specular value < 0!");
    }
    specular = v;
}

void material::setShininess(const double &v) {
    if(v < 0) {
        throw std::invalid_argument("Cannot set shininess value < 0!");
    }
    shininess = v;
}

bool material::operator==(const material &rhs) const {
    return c == rhs.c && 
        ambient == rhs.ambient &&
        diffuse == rhs.diffuse &&
        specular == rhs.specular &&
        shininess == rhs.shininess;
}

color material::getLighting(const pointLight &light, const tuple &position, const tuple &eyeV, const tuple &normalV) const {
    auto effectiveColor = c * light.getIntensity();
    auto lightV = (light.getPosition() - position).normalized();
    auto ambientContribution = effectiveColor * ambient;

    auto lightDotNormal = lightV.dot(normalV);
    auto diffuseContribution = BLACK;
    auto specularContribution = BLACK;

    if (lightDotNormal >= 0) {
        diffuseContribution = effectiveColor * diffuse * lightDotNormal;

        auto reflectV = -lightV.reflect(normalV);
        auto reflectDotEye = reflectV.dot(eyeV);

        if (reflectDotEye > 0) {
            auto factor = pow(reflectDotEye, shininess);
            specularContribution = light.getIntensity() * specular * factor;
        }
    }

    return ambientContribution + diffuseContribution + specularContribution;
}

std::ostream &rayTracer::operator<<(std::ostream &os, const material &m) {
    os << "material(" << m.c << "," << m.ambient << "," << m.diffuse << "," << m.specular << "," << m.shininess << ")" << std::endl;
    return os;
}