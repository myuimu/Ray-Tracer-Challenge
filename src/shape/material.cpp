#include "shape/material.h"

using namespace rayTracer;

material::material(const color &c, 
                    const float &ambient,
                    const float &diffuse,
                    const float &specular,
                    const float &shininess,
                    const float &reflective,
                    const float &transparency,
                    const float &refractiveIndex):
    c(c),
    ambient(ambient),
    diffuse(diffuse),
    specular(specular),
    shininess(shininess),
    reflective(reflective),
    transparency(transparency),
    refractiveIndex(refractiveIndex)
    {}

material::material(const color &c, 
                    const float &ambient,
                    const float &diffuse,
                    const float &specular,
                    const float &shininess,
                    const float &reflective,
                    const float &transparency,
                    const float &refractiveIndex,
                    const std::shared_ptr<pattern> &p):
    c(c),
    ambient(ambient),
    diffuse(diffuse),
    specular(specular),
    shininess(shininess),
    reflective(reflective),
    transparency(transparency),
    refractiveIndex(refractiveIndex) {
    setPattern(p);
}
            
const color &material::getColor() const {
    return c;
}

const float &material::getAmbient() const {
    return ambient;
}

const float &material::getDiffuse() const {
    return diffuse;
}

const float &material::getSpecular() const {
    return specular;
}

const float &material::getShininess() const {
    return shininess;
}

const float &material::getReflective() const {
    return reflective;
}

const float &material::getTransparency() const {
    return transparency;
}

const float &material::getRefractiveIndex() const {
    return refractiveIndex;
}

const pattern &material::getPattern() const {
    return *p.get();
}

void material::setColor(const color &newColor) {
    c = newColor;
}

void material::setAmbient(const float &v) {
    if(v < 0) {
        throw std::invalid_argument("Cannot set ambient value < 0!");
    }
    ambient = v;
}

void material::setDiffuse(const float &v) {
    if(v < 0) {
        throw std::invalid_argument("Cannot set diffuse value < 0!");
    }
    diffuse = v;
}

void material::setSpecular(const float &v) {
    if(v < 0) {
        throw std::invalid_argument("Cannot set specular value < 0!");
    }
    specular = v;
}

void material::setShininess(const float &v) {
    if(v < 0) {
        throw std::invalid_argument("Cannot set shininess value < 0!");
    }
    shininess = v;
}

void material::setReflective(const float &v) {
    if(v < 0) {
        throw std::invalid_argument("Cannot set reflective value < 0!");
    }
    reflective = v;
}

void material::setTransparency(const float &v) {
    if(v < 0) {
        throw std::invalid_argument("Cannot set transparency value < 0!");
    }
    shininess = v;
}

void material::setRefractiveIndex(const float &v) {
    if(v < 0) {
        throw std::invalid_argument("Cannot set refractive index value < 0!");
    }
    refractiveIndex = v;
}

void material::setPattern(const std::shared_ptr<pattern> &newPattern) {
    p = newPattern;
}

bool material::operator==(const material &rhs) const {
    return c == rhs.c && 
        ambient == rhs.ambient &&
        diffuse == rhs.diffuse &&
        specular == rhs.specular &&
        shininess == rhs.shininess;
}

color material::getLighting(const pointLight &light, const shape &object, const tuple &position, const tuple &eyeV, const tuple &normalV, const bool &inShadow) const {
    auto effectiveColor = c;
    if (p != nullptr) {
        effectiveColor = p->getColorForShape(object, position);
    }
    effectiveColor = effectiveColor * light.getIntensity();
    
    auto lightV = (light.getPosition() - position).normalized();
    auto ambientContribution = effectiveColor * ambient;

    auto lightDotNormal = lightV.dot(normalV);
    auto diffuseContribution = BLACK;
    auto specularContribution = BLACK;

    if (lightDotNormal >= 0 && !inShadow) {
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