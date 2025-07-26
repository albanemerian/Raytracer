/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** PhongLight
*/

#include "PhongLight.hpp"
#include <cmath>
#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>

PhongLight::PhongLight()
    : ALight(), _direction(), _color(), _intensity(0),
      _radius(0), _shininess(32.0f) {
}

PhongLight::PhongLight(std::shared_ptr<std::map<ValueType_t, ValueType>> map,
                    std::shared_ptr<std::vector<std::shared_ptr<IPrimitives>>>
                    primitivesList)
    : ALight() {
    _primitives = primitivesList;
    if (map->find(ValueType_t::COLOR) != map->end()) {
        auto colorVector = std::get<Math::Vector3D>((*map)
        [ValueType_t::COLOR]);
        _color = Color(colorVector.getX(), colorVector.getY(),
        colorVector.getZ());
    }

    if (map->find(ValueType_t::INTENSITY) != map->end()) {
        _intensity = std::get<float>((*map)[ValueType_t::INTENSITY]);
    }

    if (map->find(ValueType_t::DIRECTION) != map->end()) {
        _direction = std::get<Math::Vector3D>((*map)
        [ValueType_t::DIRECTION]).normalize();
    }
    if (map->find(ValueType_t::RADIUS) != map->end()) {
        _radius = std::get<float>((*map)[ValueType_t::RADIUS]);
    }
    if (map->find(ValueType_t::SHININESS) != map->end()) {
        _shininess = std::get<float>((*map)[ValueType_t::SHININESS]);
    } else {
        _shininess = 0.0f;
    }
}

PhongLight::PhongLight(const Color &color, float intensity,
        const Math::Vector3D &direction, float radius, float shininess,
        std::shared_ptr<std::vector<std::shared_ptr<IPrimitives>>>
        primitivesList)
    : ALight(color, intensity, primitivesList), _direction
        (direction.normalize()), _color(color), _intensity(intensity),
        _radius(radius), _shininess(shininess) {
}

PhongLight::~PhongLight() {
}

Math::Vector3D PhongLight::getDirection() const {
    return _direction;
}



TypeLight PhongLight::getTypeLight() const {
    return TypeLight::PHONG;
}

float PhongLight::getShininess() const {
    return _shininess;
}

void PhongLight::setDirection(const Math::Vector3D &position) {
    _direction = position;
}


void PhongLight::setShininess(float shininess) {
    _shininess = shininess;
}

float PhongLight::getRadius() const {
    return _radius;
}

void PhongLight::addLight(std::shared_ptr<PixelInfo> pixelInfo,
    const Math::Ray &ray) const {
    Math::Vector3D normal = pixelInfo->_normalizedVector;
    Math::Vector3D lightDir = _direction.normalize();
    Math::Vector3D viewDir = (ray.getOrigin() - pixelInfo->_pos).normalize();

    float diff = std::max(static_cast<float>(normal.dot(lightDir)), 0.0f);

    Math::Vector3D reflectDir = (2.0f * normal.dot(lightDir) *
        normal - lightDir).normalize();

    float spec = 0.0f;
    if (diff > 0.0f && _shininess > 0.0f) {
        float dotVR = std::max(static_cast<float>
            (viewDir.dot(reflectDir)), 0.0f);
        spec = std::pow(dotVR, _shininess);
    }

    float ambientStrength = 0.0f;

    Color ambient = Color(_color) * ambientStrength;
    Color diffuse = Color(_color) * (_intensity * diff);
    Color specular = Color(255, 255, 255) * (_intensity * spec);

    Color result = pixelInfo->_color;
    result += diffuse;
    result += specular;

    pixelInfo->_color = result;
    pixelInfo->_light_intensity = _intensity;
    pixelInfo->_light_color = _color;
}

extern "C" {
    std::shared_ptr<ILight> createLight(std::shared_ptr<std::map
        <ValueType_t, ValueType>> map,
        std::vector<std::shared_ptr<IPrimitives>> &primitivesList) {
        return std::make_shared<PhongLight>(map, primitivesList);
    }

    ObjectType getType() {
        return ObjectType::TYPE_LIGHT;
    }

    std::string getName() {
        return "phong";
    }
}
