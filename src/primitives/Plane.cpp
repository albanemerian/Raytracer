/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Plane
*/

#include <vector>
#include <memory>
#include <map>
#include <string>
#include <optional>
#include "Plane.hpp"
#include "../../common/Ray.hpp"

Plane::Plane()
    : APrimitives(), _distance(0), _normal(0, 1, 0) {}

Plane::Plane(std::shared_ptr<std::map<ValueType_t, ValueType>> map,
               const std::vector<std::shared_ptr<std::map<ValueType_t,
               ValueType>>> &graphSceneList)
    : APrimitives(map, graphSceneList) {
    _distance = 0;
    auto it = map->find(ValueType_t::AXIS);
    if (it != map->end()) {
        _axe = std::get<std::string>(it->second);
    } else {
        _axe = "";
    }
    updateNormal();
}

Plane::~Plane() {
}

void Plane::setRotation(const Math::Rot3D &newRotation) {
    _rotation = newRotation;
    updateNormal();
}

void Plane::updateNormal() {
    _normal = _rotation.rotate(Math::Vector3D(0, 1, 0)).normalize();
}

std::optional<double> Plane::distance(const Math::Ray &ray) const {
    Math::Vector3D scaledPosition = Math::Vector3D(
        _position / _scales);

    Math::Vector3D scaledNormal = Math::Vector3D(
        _normal / _scales).normalize();

    double denom = scaledNormal.dot(ray.getDirection());

    if (std::abs(denom) > 1e-6) {
        Math::Vector3D originToPlane = scaledPosition - ray.getOrigin();
        double t = scaledNormal.dot(originToPlane) / denom;
        if (t >= 0) {
            return t;
        }
    }
    return std::nullopt;
}

PixelInfo Plane::distanceInfo(const Math::Ray &ray) {
    PixelInfo pixelInfo;
    Math::Ray scaledRay = computeScaledRay(ray);
    Math::Vector3D scaledPosition = Math::Vector3D(_position * _invScales);
    Math::Vector3D scaledNormal = Math::Vector3D(
        _normal.getX() * _invScales.getX(),
        _normal.getY() * _invScales.getY(),
        _normal.getZ() * _invScales.getZ()).normalize();
    auto tOpt = distance(scaledRay);
    if (!tOpt.has_value()) {
        pixelInfo._isHit = false;
        return pixelInfo;
    }
    double t = tOpt.value();
    Math::Vector3D hitPoint = scaledRay.getOrigin() +
        scaledRay.getDirection() * t;

    if (scaledRay.getDirection().dot(scaledNormal) > 0) {
        scaledNormal = -scaledNormal;
    }
    Math::Vector3D worldHit = hitPoint * _scales;
    pixelInfo._isHit = true;
    pixelInfo._distance = t;
    pixelInfo._color = _color;
    pixelInfo._pos = worldHit;
    pixelInfo._normalizedVector = scaledNormal.normalize();
    if (material != nullptr) {
        pixelInfo._color = material->applyMaterial
            (pixelInfo, 0.0f, 0.0f, *this);
    }

    return pixelInfo;
}

std::optional<Math::Point3D> Plane::getIntersection(const Math::Ray &ray)
    const {
    auto tOpt = distance(ray);
    if (tOpt.has_value())
        return ray.getOrigin() + ray.getDirection() * tOpt.value();
    return std::nullopt;
}

std::optional<Math::Vector3D> Plane::getNormal(const Math::Point3D &point)
    const {
    (void)point;
    return _normal;
}

Type Plane::getType() const { return Type::PLANE; }

extern "C" {
    std::shared_ptr<IPrimitives> createPrimitive(
        std::shared_ptr<std::map<ValueType_t, ValueType>> map,
        const std::vector<std::shared_ptr<std::map<ValueType_t,
        ValueType>>> &graphSceneList) {
        return std::make_shared<Plane>(map, graphSceneList);
    }

    ObjectType getType() {
        return ObjectType::TYPE_PRIMITIVE;
    }

    std::string getName() {
        return "planes";
    }
}
