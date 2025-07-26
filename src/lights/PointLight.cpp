/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** PointLight
*/

#include "PointLight.hpp"
#include <cmath>
#include <map>
#include <iostream>
#include <memory>
#include <vector>
#include <string>

PointLight::PointLight() : ALight(), _position(), _radius(1.0f) {
}

PointLight::PointLight(const Color &color, float intensity,
                   const Math::Point3D &position, float radius,
                   std::shared_ptr<std::vector<std::shared_ptr<IPrimitives>>>
                   primitivesList)
            : ALight(color, intensity, primitivesList), _position(position),
            _radius(radius) {
}

PointLight::PointLight(std::shared_ptr<std::map<ValueType_t, ValueType>> map,
                      std::shared_ptr<std::vector<std::shared_ptr
                      <IPrimitives>>> primitivesList)
    : ALight() {
    _primitives = primitivesList;

    if (map->find(ValueType_t::COLOR) != map->end()) {
        auto colorVector = std::get<Math::Vector3D>((*map)[ValueType_t::COLOR]);
        _color = Color(colorVector.getX(), colorVector.getY(),
        colorVector.getZ());
    }

    if (map->find(ValueType_t::INTENSITY) != map->end()) {
        _intensity = std::get<float>((*map)[ValueType_t::INTENSITY]);
    }

    if (map->find(ValueType_t::POSITION) != map->end()) {
        _position = std::get<Math::Point3D>((*map)[ValueType_t::POSITION]);
    }
    if (map->find(ValueType_t::RADIUS) != map->end()) {
        _radius = std::get<float>((*map)[ValueType_t::RADIUS]);
    }
}

PointLight::~PointLight() {
}

Math::Point3D PointLight::getPosition() const {
    return _position;
}

float PointLight::getRadius() const {
    return _radius;
}

void PointLight::setPosition(const Math::Point3D &position) {
    _position = position;
}

void PointLight::setRadius(float radius) {
    _radius = radius;
}

TypeLight PointLight::getTypeLight() const {
    return TypeLight::POINT;
}

void PointLight::addLight(std::shared_ptr<PixelInfo> pixelInfo,
    const Math::Ray &ray) const {
    (void)ray;
    pixelInfo->_light_intensity = _intensity;
    pixelInfo->_light_color = _color;
}

extern "C" {
    std::shared_ptr<ILight> createLight(std::shared_ptr<std::map<ValueType_t,
        ValueType>> map,
        std::vector<std::shared_ptr<IPrimitives>> primitivesList) {
        return std::make_shared<PointLight>(map, primitivesList);
    }

    ObjectType getType() {
        return ObjectType::TYPE_LIGHT;
    }

    std::string getName() {
        return "point";
    }
}
