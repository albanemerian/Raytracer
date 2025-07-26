/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Ray
*/

#include "Ray.hpp"


// Setter
void Ray::setOrigin(Math::Point3D origin) {
    this->_ray.setOrigin(origin);
}

void Ray::setDirection(Math::Vector3D direction) {
    this->_ray.setDirection(direction);
}

void Ray::setColor(Color color) {
    this->_color = color;
}

void Ray::setIntensity(double intensity) {
    this->_intensity = intensity;
}


// Getter
Math::Point3D Ray::getOrigin() const {
    return this->_ray.getOrigin();
}

Math::Vector3D Ray::getDirection() const {
    return this->_ray.getDirection();
}

Color Ray::getColor() const {
    return this->_color;
}

double Ray::getIntensity() const {
    return this->_intensity;
}
