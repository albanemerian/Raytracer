/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** InfiniteCylinder
*/

#include "InfiniteCylinder.hpp"
#include <map>
#include <memory>
#include <iostream>
#include <algorithm>
#include <string>
#include <optional>
#include <vector>
#include <cmath>
#include "../../common/Ray.hpp"

InfiniteCylinder::InfiniteCylinder() : APrimitives(),
    _baseRadius(0), _distance(0) {
}

InfiniteCylinder::~InfiniteCylinder() {
}

InfiniteCylinder::InfiniteCylinder(
                std::shared_ptr<std::map<ValueType_t, ValueType>> map,
               const std::vector<std::shared_ptr<std::map<ValueType_t,
               ValueType>>> &graphSceneList)
    : APrimitives(map, graphSceneList) {
    _baseRadius = std::get<float>(map->find(ValueType_t::RADIUS)->second);
    _baseRadius *= scale;
    _distance = 0;
}

/* Getter */
float InfiniteCylinder::getBaseRadius() const {
    return _baseRadius;
}

Type InfiniteCylinder::getType() const {
    return Type::CYLINDER;
}


/* Setter */

void InfiniteCylinder::setBaseRadius(float radius) {
    _baseRadius = radius;
}

/* Methods */

std::optional<double> InfiniteCylinder::distance(const Math::Ray &ray) const {
    Math::Vector3D localOrigin = _rotation.inverseRotate
        (ray.getOrigin() - _position);
    Math::Vector3D localDir = _rotation.inverseRotate
        (ray.getDirection());

    Math::Vector3D oc(localOrigin.getX(), 0, localOrigin.getZ());
    float a = localDir.getX() * localDir.getX() + localDir.getZ() *
        localDir.getZ();
    float b = 2.0f * (oc.getX() * localDir.getX() + oc.getZ() *
        localDir.getZ());
    float c = oc.getX() * oc.getX() + oc.getZ() * oc.getZ() -
        _baseRadius * _baseRadius;

    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return std::nullopt;
    }

    float sqrtDiscriminant = std::sqrt(discriminant);
    float t0 = (-b - sqrtDiscriminant) / (2.0f * a);
    return t0;
}

PixelInfo InfiniteCylinder::distanceInfo(const Math::Ray &ray) {
    PixelInfo pixelInfo;
    Math::Ray scaledRay = computeScaledRay(ray);
    Math::Vector3D localOrigin = _rotation.inverseRotate
        (scaledRay.getOrigin() - _position);
    Math::Vector3D localDir = _rotation.inverseRotate
        (scaledRay.getDirection());

    auto t = distance(scaledRay);
    if (!t.has_value()) {
        pixelInfo._isHit = false;
        return pixelInfo;
    }

    Math::Vector3D localIntersection = localOrigin + localDir * t.value();
    Math::Vector3D localNormal = Math::Vector3D(localIntersection.getX(),
        0, localIntersection.getZ()).normalize();

    Math::Vector3D worldIntersection = Math::Vector3D(
        localIntersection * _scales);
    Math::Vector3D worldNormal = Math::Vector3D(
        localNormal * _invScales).normalize();

    pixelInfo._isHit = true;
    pixelInfo._distance = t.value();
    pixelInfo._pos = _rotation.rotate(worldIntersection) + _position;
    pixelInfo._normalizedVector = _rotation.rotate(worldNormal).normalize();
    pixelInfo._color = _color;
    if (material != nullptr) {
        pixelInfo._color = material->applyMaterial
            (pixelInfo, _baseRadius, 20.0f, *this);
    }

    return pixelInfo;
}

std::optional<Math::Point3D> InfiniteCylinder::getIntersection
    (const Math::Ray &ray)
    const {
    auto t = distance(ray);
    if (t.has_value())
        return ray.getOrigin() + ray.getDirection() * t.value();
    return std::nullopt;
}

std::optional<Math::Vector3D> InfiniteCylinder::getNormal
    (const Math::Point3D &point)
    const {
    Math::Vector3D cylinderDir = Math::Vector3D(0, 1, 0);
    if (_rotation.x_pitch != 0 || _rotation.z_yaw != 0 ||
        _rotation.y_roll != 0) {
        cylinderDir = _rotation.toUnitVector();
    }
    Math::Vector3D pointToCenter = point - _position;
    double heightOnAxis = pointToCenter.dot(cylinderDir);
    Math::Point3D projectionOnAxis = _position + cylinderDir * heightOnAxis;
    Math::Vector3D normal = point - projectionOnAxis;
    return normal.normalize();
}


extern "C" {
    std::shared_ptr<IPrimitives> createPrimitive(
        std::shared_ptr<std::map<ValueType_t, ValueType>> map,
        const std::vector<std::shared_ptr<std::map<ValueType_t,
        ValueType>>> &graphSceneList) {
        return std::make_shared<InfiniteCylinder>(map, graphSceneList);
    }

    ObjectType getType() {
        return ObjectType::TYPE_PRIMITIVE;
    }

    std::string getName() {
        return "infinite-cylinders";
    }
}
