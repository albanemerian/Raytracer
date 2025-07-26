/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Cylinder
*/

#include <map>
#include <memory>
#include <iostream>
#include <algorithm>
#include <string>
#include <optional>
#include <vector>
#include "Cylinder.hpp"
#include "../../common/Ray.hpp"


Cylinder::Cylinder() :
    APrimitives(), _baseRadius(0), _height(0), _distance(0) {
}

Cylinder::~Cylinder() {
}

Cylinder::Cylinder(std::shared_ptr<std::map<ValueType_t, ValueType>> map,
               const std::vector<std::shared_ptr<std::map<ValueType_t,
               ValueType>>> &graphSceneList)
    : APrimitives(map, graphSceneList) {
    _baseRadius = std::get<float>(map->find(ValueType_t::RADIUS)->second);
    _height = std::get<float>(map->find(ValueType_t::HEIGHT)->second);

    _baseRadius *= scale;
    _height *= scale;
    _distance = 0;
}

/* Getter */
float Cylinder::getBaseRadius() const {
    return _baseRadius;
}

float Cylinder::getHeight() const {
    return _height;
}

Type Cylinder::getType() const {
    return Type::CYLINDER;
}


/* Setter */

void Cylinder::setBaseRadius(float radius) {
    _baseRadius = radius;
}

void Cylinder::setHeight(float height) {
    _height = height;
}

/* Methods */

std::optional<double> Cylinder::getSideIntersection(
    const Math::Vector3D &localOrigin, const Math::Vector3D &localDir) const {
    Math::Vector3D oc(localOrigin.getX(), 0, localOrigin.getZ());
    float a = localDir.getX() * localDir.getX() + localDir.getZ() *
        localDir.getZ();
    if (std::abs(a) < 1e-6) {
        return std::nullopt;
    }

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
    float t1 = (-b + sqrtDiscriminant) / (2.0f * a);

    float y0 = localOrigin.getY() + t0 * localDir.getY();
    float y1 = localOrigin.getY() + t1 * localDir.getY();

    bool hit0 = (y0 >= 0 && y0 <= _height && t0 > 0);
    bool hit1 = (y1 >= 0 && y1 <= _height && t1 > 0);

    if (hit0) {
        return t0;
    } else if (hit1) {
        return t1;
    }
    return std::nullopt;
}

std::optional<double> Cylinder::getBaseIntersection(
    const Math::Vector3D &localOrigin, const Math::Vector3D &localDir) const {
    if (std::abs(localDir.getY()) < 1e-6) {
        return std::nullopt;
    }

    float t = -localOrigin.getY() / localDir.getY();
    if (t <= 0) {
        return std::nullopt;
    }

    float x = localOrigin.getX() + t * localDir.getX();
    float z = localOrigin.getZ() + t * localDir.getZ();
    float distanceFromCenter = std::sqrt(x * x + z * z);
    if (distanceFromCenter <= _baseRadius) {
        return t;
    }
    return std::nullopt;
}

std::optional<double> Cylinder::getCapIntersection(
    const Math::Vector3D &localOrigin, const Math::Vector3D &localDir) const {
    if (std::abs(localDir.getY()) < 1e-6) {
        return std::nullopt;
    }

    float t = (_height - localOrigin.getY()) / localDir.getY();
    if (t <= 0) {
        return std::nullopt;
    }

    float x = localOrigin.getX() + t * localDir.getX();
    float z = localOrigin.getZ() + t * localDir.getZ();
    float distanceFromCenter = std::sqrt(x * x + z * z);
    if (distanceFromCenter <= _baseRadius) {
        return t;
    }
    return std::nullopt;
}

std::optional<double> Cylinder::distance(const Math::Ray &ray) const {
    Math::Vector3D localOrigin = _rotation.inverseRotate
        (ray.getOrigin() - _position);
    Math::Vector3D localDir = _rotation.inverseRotate
        (ray.getDirection());

    std::optional<double> tSide = getSideIntersection(localOrigin, localDir);
    std::optional<double> tBase = getBaseIntersection(localOrigin, localDir);
    std::optional<double> tCap = getCapIntersection(localOrigin, localDir);

    std::optional<double> tClosest = std::nullopt;
    if (tSide.has_value())
        tClosest = tSide;
    if (tBase.has_value() && (!tClosest.has_value() ||
        tBase.value() < tClosest.value()))
        tClosest = tBase;
    if (tCap.has_value() && (!tClosest.has_value() ||
        tCap.value() < tClosest.value()))
        tClosest = tCap;
    return tClosest;
}

PixelInfo Cylinder::distanceInfo(const Math::Ray &ray) {
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
    Math::Vector3D localNormal = calculateLocalNormal(localIntersection);

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
            (pixelInfo, _baseRadius, _height, *this);
    }
    return pixelInfo;
}

std::optional<Math::Point3D> Cylinder::getIntersection(const Math::Ray &ray)
    const {
    auto t = distance(ray);
    if (t.has_value())
        return ray.getOrigin() + ray.getDirection() * t.value();
    return std::nullopt;
}

std::optional<Math::Vector3D> Cylinder::getNormal(const Math::Point3D &point)
    const {
    Math::Vector3D localPoint = _rotation.inverseRotate(point - _position);
    Math::Vector3D localNormal = calculateLocalNormal(localPoint);

    return _rotation.rotate(localNormal);
}

Math::Vector3D Cylinder::calculateLocalNormal(
    const Math::Vector3D &localPoint) const {
    const float epsilon = 1e-6;

    if (std::abs(localPoint.getY()) < epsilon) {
        return Math::Vector3D(0, -1, 0);
    }

    if (std::abs(localPoint.getY() - _height) < epsilon) {
        return Math::Vector3D(0, 1, 0);
    }
    return Math::Vector3D(localPoint.getX(), 0, localPoint.getZ()).normalize();
}

extern "C" {
    std::shared_ptr<IPrimitives>createPrimitive(
        std::shared_ptr<std::map<ValueType_t, ValueType>> map,
        const std::vector<std::shared_ptr<std::map<ValueType_t,
        ValueType>>> &graphSceneList) {
        return std::make_shared<Cylinder>(map, graphSceneList);
    }

    ObjectType getType() {
        return ObjectType::TYPE_PRIMITIVE;
    }

    std::string getName() {
        return "cylinders";
    }
}
