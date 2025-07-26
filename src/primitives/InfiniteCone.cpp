/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** InfiniteCone
*/

#include "InfiniteCone.hpp"
#include <map>
#include <memory>
#include <vector>
#include <string>
#include <optional>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <limits>
#include "../../common/Ray.hpp"

InfiniteCone::InfiniteCone() : APrimitives(), _baseRadius(0), _angle(0),
                _distance(0) {
}

InfiniteCone::InfiniteCone(
                std::shared_ptr<std::map<ValueType_t, ValueType>> map,
               const std::vector<std::shared_ptr<std::map<ValueType_t,
               ValueType>>> &graphSceneList)
    : APrimitives(map, graphSceneList) {
    try {
        auto radiusIt = map->find(ValueType_t::RADIUS);
        auto angleIt = map->find(ValueType_t::ANGLE);
        if (radiusIt != map->end()) {
            _baseRadius = std::get<float>(radiusIt->second);
        } else {
            _baseRadius = 1.0f;
        }

        if (angleIt != map->end()) {
            _angle = std::get<float>(angleIt->second);
        } else {
            _angle = 30.0f * M_PI / 180.0f;
        }

        _baseRadius *= scale;
        _distance = 0;
    } catch (const std::exception& e) {
        std::cerr << "Error creating infinite cone: "
        << e.what() << std::endl;
        _baseRadius = 1.0f;
        _angle = 30.0f * M_PI / 180.0f;
    }
}

InfiniteCone::~InfiniteCone() {
}

/* Getter */
float InfiniteCone::getBaseRadius() const {
    return _baseRadius;
}

float InfiniteCone::getAngle() const {
    return _angle;
}

std::optional<double> InfiniteCone::distance
    (const Math::Ray &ray) const {
    if (_baseRadius <= 0)
        return std::nullopt;

    Math::Vector3D localOrigin = transformToLocal(ray);
    Math::Vector3D localDirection = localDirectionVector(ray);

    return intersectCone(localOrigin, localDirection);
}

PixelInfo InfiniteCone::distanceInfo(const Math::Ray &ray) {
    Math::Ray scaledRay = computeScaledRay(ray);

    PixelInfo pixelInfo;
    auto tOpt = distance(scaledRay);

    if (!tOpt.has_value()) {
        pixelInfo._isHit = false;
        return pixelInfo;
    }

    float t = tOpt.value();
    Math::Point3D intersection = scaledRay.getOrigin() +
        scaledRay.getDirection() * t;
    Math::Vector3D worldIntersection = intersection * _scales;

    auto normalOpt = getNormal(worldIntersection + _position);
    Math::Vector3D normal;
    if (normalOpt.has_value()) {
        normal = normalOpt.value();
    } else {
        normal = Math::Vector3D(0, 1, 0);
    }

    pixelInfo._isHit = true;
    pixelInfo._distance = t;
    pixelInfo._color = _color;
    pixelInfo._pos = worldIntersection + _position;
    pixelInfo._normalizedVector = normal.normalize();
    if (material != nullptr) {
        pixelInfo._color = material->applyMaterial
            (pixelInfo, _baseRadius, 0, *this);
    }
    return pixelInfo;
}

std::optional<Math::Point3D> InfiniteCone::getIntersection
    (const Math::Ray &ray)
    const {
    auto tOpt = distance(ray);
    if (tOpt.has_value())
        return ray.getOrigin() + ray.getDirection() * tOpt.value();
    return std::nullopt;
}

std::optional<Math::Vector3D> InfiniteCone::getNormal
    (const Math::Point3D &point)
    const {
    try {
        Math::Vector3D localPoint = _rotation.inverseRotate(point - _position);
        double cosAngle = std::cos(_angle);
        double sinAngle = std::sin(_angle);
        double r = std::sqrt(localPoint.getX() * localPoint.getX() +
                             localPoint.getZ() * localPoint.getZ());

        Math::Vector3D normal;
        if (std::abs(r) < 1e-6) {
            normal = Math::Vector3D(0, 1, 0);
        } else {
            normal = Math::Vector3D(
                localPoint.getX(),
                r * cosAngle / sinAngle,
                localPoint.getZ()).normalize();
        }
        return _rotation.rotate(normal).normalize();
    } catch (const std::exception& e) {
        return Math::Vector3D(0, 1, 0);
    }
}

Type InfiniteCone::getType() const {
    return Type::CONE;
}

void InfiniteCone::setBaseRadius(float radius) {
    _baseRadius = radius;
}

void InfiniteCone::setAngle(float angle) {
    _angle = angle;
}

Math::Vector3D InfiniteCone::transformToLocal(const Math::Ray &ray) const {
    Math::Vector3D scaledPosition = Math::Vector3D(
        _position.getX() / _scales.getX(),
        _position.getY() / _scales.getY(),
        _position.getZ() / _scales.getZ());

    return _rotation.inverseRotate(ray.getOrigin() - scaledPosition);
}

Math::Vector3D InfiniteCone::localDirectionVector(const Math::Ray &ray) const {
    return _rotation.inverseRotate(ray.getDirection()).normalize();
}

std::optional<double> InfiniteCone::intersectCone(
    const Math::Vector3D &localOrigin,
    const Math::Vector3D &localDirection) const {
    double tanAlpha2 = std::pow(std::tan(_angle), 2);
    double a = localDirection.getX() * localDirection.getX() +
              localDirection.getZ() * localDirection.getZ() -
              tanAlpha2 * localDirection.getY() * localDirection.getY();
    double b = 2.0 * (localOrigin.getX() * localDirection.getX() +
              localOrigin.getZ() * localDirection.getZ() -
              tanAlpha2 * localOrigin.getY() * localDirection.getY());
    double c = localOrigin.getX() * localOrigin.getX() +
              localOrigin.getZ() * localOrigin.getZ() -
              tanAlpha2 * localOrigin.getY() * localOrigin.getY();

    if (std::abs(a) < 1e-6) {
        if (std::abs(b) < 1e-6) {
            return std::nullopt;
        }
        double t = -c / b;
        if (t > 0.0 && isPointOnCone(localOrigin + localDirection * t)) {
            return t;
        }
        return std::nullopt;
    }

    double discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0) {
        return std::nullopt;
    }

    double sqrt_disc = std::sqrt(discriminant);
    double t1 = (-b - sqrt_disc) / (2.0 * a);
    double t2 = (-b + sqrt_disc) / (2.0 * a);

    double t_min = -1.0;
    if (t1 > 0.0 && isPointOnCone(localOrigin + localDirection * t1))
        t_min = t1;
    if (t2 > 0.0 && (t_min < 0.0 || t2 < t_min) &&
        isPointOnCone(localOrigin + localDirection * t2)) {
        t_min = t2;
    }

    if (t_min > 0.0) {
        return t_min;
    }
    return std::nullopt;
}

bool InfiniteCone::isPointOnCone(const Math::Point3D &hitPoint) const {
    double r2 = hitPoint.getX() * hitPoint.getX() +
                hitPoint.getZ() * hitPoint.getZ();
    double h = hitPoint.getY();
    double expected_r2 = std::pow(h * std::tan(_angle), 2);
    const double EPSILON = 1e-3;
    bool onSurface = std::abs(r2 - expected_r2) < EPSILON;
    int coneDirection = 1;
    return onSurface && (coneDirection * h > 0);
}

extern "C" {
    std::shared_ptr<IPrimitives>createPrimitive(
        std::shared_ptr<std::map<ValueType_t, ValueType>> map,
        const std::vector<std::shared_ptr<std::map<ValueType_t,
        ValueType>>> &graphSceneList) {
        return std::make_shared<InfiniteCone>(map, graphSceneList);
    }

    ObjectType getType() {
        return ObjectType::TYPE_PRIMITIVE;
    }

    std::string getName() {
        return "infinite-cones";
    }
}
