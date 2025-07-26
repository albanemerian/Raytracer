/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** ALight
*/

#include <memory>
#include "ALight.hpp"

ALight::ALight() : _color(), _intensity(0.0f) {
}

ALight::ALight(const Color &color, float intensity) : _color(color),
    _intensity(intensity) {
}

ALight::ALight(const Color &color, float intensity, std::shared_ptr
    <std::vector<std::shared_ptr<IPrimitives>>> primitivesList)
    : _color(color), _intensity(intensity), _primitives(primitivesList) {
}

ALight::~ALight() {
}

Color ALight::getColor() const {
    return _color;
}

float ALight::getIntensity() const {
    return _intensity;
}

void ALight::setColor(const Color &color) {
    _color = color;
}

void ALight::setIntensity(float intensity) {
    _intensity = intensity;
}
