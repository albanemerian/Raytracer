/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Cone
*/

#include "Cone.hpp"
#include <map>
#include <memory>
#include <vector>
#include <string>
#include <optional>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <limits>

Cone::Cone() : APrimitives(), _baseRadius(0), _height(0),
                _distance(0) {
}

Cone::Cone(std::shared_ptr<std::map<ValueType_t, ValueType>> map,
               const std::vector<std::shared_ptr<std::map<ValueType_t,
               ValueType>>> &graphSceneList)
    : APrimitives(map, graphSceneList) {
    try {
        auto radiusIt = map->find(ValueType_t::RADIUS);
        auto heightIt = map->find(ValueType_t::HEIGHT);
        if (radiusIt != map->end()) {
            _baseRadius = std::get<float>(radiusIt->second);
        }

        if (heightIt != map->end()) {
            _height = std::get<float>(heightIt->second);
        }

        _baseRadius *= scale;
        _height *= scale;
        _distance = 0;
    } catch (const std::exception& e) {
        std::cerr << "Error creating cone: " << e.what() << std::endl;
        _baseRadius = 1.0f;
        _height = 1.0f;
    }
}

Cone::~Cone() {
}

/* Getter */
float Cone::getBaseRadius() const {
    return _baseRadius;
}

float Cone::getHeight() const {
    return _height;
}

std::optional<double> Cone::distance(const Math::Ray &ray) const {
    if (_baseRadius <= 0 || _height <= 0) {
        return std::nullopt;
    }

    Math::Vector3D localOrigin = transformToLocal(ray);
    Math::Vector3D localDirection = localDirectionVector(ray);

    auto t_cone = intersectConeBody(localOrigin, localDirection);
    auto t_base = intersectConeBase(localOrigin, localDirection);

    if (t_cone.has_value() && t_base.has_value()) {
        return std::min(t_cone.value(), t_base.value());
    } else if (t_cone.has_value()) {
        return t_cone.value();
    } else if (t_base.has_value()) {
        return t_base.value();
    }
    return std::nullopt;
}

PixelInfo Cone::distanceInfo(const Math::Ray &ray) {
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

    Math::Vector3D localPoint = _rotation.inverseRotate(
        intersection - _position);
    bool isOnBase = std::abs(localPoint.getY()) < 0.001;

    Math::Vector3D worldIntersection = intersection * _scales;

    Math::Vector3D normal;
    if (isOnBase) {
        normal = _rotation.rotate(Math::Vector3D(0, -1, 0));
    } else {
        auto normalOpt = getNormal(worldIntersection + _position);
        if (normalOpt.has_value()) {
            normal = normalOpt.value();
        } else {
            Math::Vector3D toAxis(0, intersection.getY(), 0);
            Math::Vector3D radial = intersection - toAxis;
            normal = radial.normalize();
        }
    }

    pixelInfo._isHit = true;
    pixelInfo._distance = t;
    pixelInfo._color = _color;
    pixelInfo._pos = worldIntersection + _position;
    pixelInfo._normalizedVector = normal.normalize();
    if (material != nullptr) {
        pixelInfo._color = material->applyMaterial
            (pixelInfo, _baseRadius, _height, *this);
    }

    return pixelInfo;
}

std::optional<Math::Point3D> Cone::getIntersection(const Math::Ray &ray)
    const {
    auto tOpt = distance(ray);
    if (tOpt.has_value())
        return ray.getOrigin() + ray.getDirection() * tOpt.value();
    return std::nullopt;
}

std::optional<Math::Vector3D> Cone::getNormal(const Math::Point3D &point)
    const {
    try {
        Math::Vector3D localPoint = _rotation.inverseRotate(point - _position);
        Math::Vector3D normal;
        const double EPSILON = 1e-4;

        if (std::abs(localPoint.getY()) < EPSILON) {
            normal = Math::Vector3D(0, -1, 0);
        } else {
            Math::Vector3D axisPoint(0, localPoint.getY(), 0);
            Math::Vector3D toSurface = localPoint - axisPoint;
            double theta = std::atan2(_baseRadius, _height);

            Math::Vector3D axisDir(0, 1, 0);
            Math::Vector3D radialComponent = toSurface.normalize();
            double axialFactor = std::tan(theta);

            normal = radialComponent - axisDir * axialFactor;
            normal = normal.normalize();
        }
        return _rotation.rotate(normal).normalize();
    } catch (const std::exception& e) {
        return Math::Vector3D(0, 1, 0);
    }
}

Type Cone::getType() const {
    return Type::CONE;
}

void Cone::setBaseRadius(float radius) {
    _baseRadius = radius;
}

void Cone::setHeight(float height) {
    _height = height;
}

Math::Vector3D Cone::transformToLocal(const Math::Ray &ray) const {
    Math::Vector3D scaledPosition = Math::Vector3D(
        _position.getX() / _scales.getX(),
        _position.getY() / _scales.getY(),
        _position.getZ() / _scales.getZ());

    return _rotation.inverseRotate(ray.getOrigin() - scaledPosition);
}

Math::Vector3D Cone::localDirectionVector(const Math::Ray &ray) const {
    return _rotation.inverseRotate(ray.getDirection()).normalize();
}

std::optional<double> Cone::intersectConeBody(const Math::Vector3D &localOrigin,
    const Math::Vector3D &localDirection) const {
    float k = _baseRadius / _height;
    k *= k;

    double a = localDirection.getX() * localDirection.getX() +
        localDirection.getZ() * localDirection.getZ() -
        k * localDirection.getY() * localDirection.getY();

    double b = 2.0 * (localDirection.getX() * localOrigin.getX() +
        localDirection.getZ() * localOrigin.getZ() -
        k * localDirection.getY() * (localOrigin.getY() - _height));

    double c = localOrigin.getX() * localOrigin.getX() +
        localOrigin.getZ() * localOrigin.getZ() -
        k * (localOrigin.getY() - _height) * (localOrigin.getY() - _height);

    if (std::abs(a) < 1e-6) {
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
    if (t1 > 0.0) t_min = t1;
    if (t2 > 0.0 && (t_min < 0.0 || t2 < t_min)) t_min = t2;

    if (t_min > 0.0) {
        Math::Point3D hitPoint = localOrigin + localDirection * t_min;
        if (hitPoint.getY() >= 0.0 && hitPoint.getY() <= _height) {
            if (isPointOnConeBody(hitPoint)) {
                return t_min;
            }
        }
    }
    return std::nullopt;
}

bool Cone::isPointOnConeBody(const Math::Point3D &hitPoint) const {
    double radius_at_height = _baseRadius * (1.0 - hitPoint.getY() / _height);
    double dist_from_axis = std::sqrt(hitPoint.getX() * hitPoint.getX() +
        hitPoint.getZ() * hitPoint.getZ());
    const double EPSILON = 1e-3;

    return std::abs(dist_from_axis - radius_at_height) < EPSILON;
}

std::optional<double> Cone::intersectConeBase(const Math::Vector3D &localOrigin,
    const Math::Vector3D &localDirection) const {
    if (std::abs(localDirection.getY()) < 1e-6) {
        return std::nullopt;
    }

    double t = -localOrigin.getY() / localDirection.getY();
    if (t <= 0.0) {
        return std::nullopt;
    }

    Math::Point3D hitPoint = localOrigin + localDirection * t;
    double dist_from_axis = std::sqrt(hitPoint.getX() * hitPoint.getX() +
        hitPoint.getZ() * hitPoint.getZ());
    if (dist_from_axis <= _baseRadius) {
        return t;
    }
    return std::nullopt;
}

extern "C" {
    std::shared_ptr<IPrimitives>createPrimitive(std::shared_ptr<std::map
        <ValueType_t, ValueType>> map,
        const std::vector<std::shared_ptr<std::map<ValueType_t,
        ValueType>>> &graphSceneList) {
        return std::make_shared<Cone>(map, graphSceneList);
    }

    ObjectType getType() {
        return ObjectType::TYPE_PRIMITIVE;
    }

    std::string getName() {
        return "cones";
    }
}
