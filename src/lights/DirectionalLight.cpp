/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** DirectionalLight
*/

#include "DirectionalLight.hpp"
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <map>


DirectionalLight::DirectionalLight() : ALight(), _direction() {
}

DirectionalLight::DirectionalLight(const Color &color, float intensity,
    const Math::Vector3D &direction, float radius,
    std::vector<std::shared_ptr<IPrimitives>> primitivesList)
    : ALight(color, intensity, std::make_shared<std::vector<std::shared_ptr
        <IPrimitives>>>(primitivesList)), _direction(direction.normalize()),
      _color(color), _intensity(intensity), _radius(radius) {
}

DirectionalLight::DirectionalLight(std::shared_ptr<std::map<ValueType_t,
    ValueType>> map, std::vector<std::shared_ptr<IPrimitives>> primitivesList)
    : ALight() {
    _primitives = std::make_shared<std::vector<std::shared_ptr
    <IPrimitives>>>(primitivesList);
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
}

DirectionalLight::~DirectionalLight() {
}

Math::Vector3D DirectionalLight::getDirection() const {
    return _direction;
}


void DirectionalLight::setDirection(const Math::Vector3D &direction) {
    _direction = direction.normalize();
}


TypeLight DirectionalLight::getTypeLight() const {
    return TypeLight::DIRECTIONAL;
}

float DirectionalLight::getRadius() const {
    return _radius;
}

void DirectionalLight::addLight(std::shared_ptr<PixelInfo> pixelInfo,
    const Math::Ray &ray) const {
    Math::Vector3D hitPoint = pixelInfo->_pos;
    (void)ray;
    Math::Vector3D lightDir = _direction;
    lightDir = lightDir.normalize();
    double dotProduct = lightDir.dot(pixelInfo->_normalizedVector);
    if (dotProduct > 0) {
        const double shadowBias = 0.1f;
        Math::Vector3D shadowRayOrigin =
            hitPoint + pixelInfo->_normalizedVector * shadowBias;
        Math::Ray shadowRay(shadowRayOrigin, lightDir);
        bool inShadow = false;
        for (const auto& primitive : *_primitives) {
            PixelInfo shadowInfo = primitive->distanceInfo(shadowRay);
            if (shadowInfo._isHit && shadowInfo._distance > shadowBias) {
                inShadow = true;
                break;
            }
        }
        if (!inShadow) {
            double lightContribution = _intensity * dotProduct;
            pixelInfo->_light_intensity += lightContribution;
            pixelInfo->_light_color += _color * lightContribution;
        }
    }
}

extern "C" {

    std::shared_ptr<ILight> createLight(std::shared_ptr<std::map<ValueType_t,
        ValueType>> map,
        std::vector<std::shared_ptr<IPrimitives>> primitivesList) {
        return std::make_shared<DirectionalLight>(map, primitivesList);
    }
    ObjectType getType() {
        return TYPE_LIGHT;
    }

    std::string getName() {
        return "directional";
    }
}
