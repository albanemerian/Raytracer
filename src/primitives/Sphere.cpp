/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Sphere
*/

#include <vector>
#include <memory>
#include <map>
#include <string>
#include <iostream>
#include <optional>
#include "Sphere.hpp"
#include "../../common/Ray.hpp"


Sphere::Sphere() : APrimitives(), _distance(0), radius(0) {}

Sphere::~Sphere() {
}

Sphere::Sphere(std::shared_ptr<std::map<ValueType_t, ValueType>> map,
               const std::vector<std::shared_ptr<std::map<ValueType_t,
               ValueType>>> &graphSceneList)
    : APrimitives(map, graphSceneList) {

    radius = std::get<float>(map->find(ValueType_t::RADIUS)->second);
    radius *= scale;
    _distance = 0;
}

std::optional<double> Sphere::distance(const Math::Ray &ray) const {
    Math::Vector3D scaledPosition = Math::Vector3D(_position * _invScales);
    Math::Vector3D oc = ray.getOrigin() - scaledPosition;
    double a = ray.getDirection().dot(ray.getDirection());
    double b = 2.0 * oc.dot(ray.getDirection());
    double c = oc.dot(oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return std::nullopt;
    }
    double sqrtDiscriminant = std::sqrt(discriminant);
    double t1 = (-b - sqrtDiscriminant) / (2.0 * a);
    double t2 = (-b + sqrtDiscriminant) / (2.0 * a);
    return (t1 > 0) ? t1 : t2;
}

PixelInfo Sphere::distanceInfo(const Math::Ray &ray) {
    PixelInfo pixelInfo;

    Math::Ray scaledRay = computeScaledRay(ray);

    auto t = distance(scaledRay);
    if (!t.has_value()) {
        pixelInfo._isHit = false;
        return pixelInfo;
    }

    Math::Point3D intersection = scaledRay.getOrigin() +
        scaledRay.getDirection().normalize() * t.value();

    Math::Point3D worldIntersection = Math::Point3D(
        intersection * _scales);
    Math::Vector3D normal = (worldIntersection - _position).normalize();

    pixelInfo._isHit = true;
    pixelInfo._distance = t.value();
    pixelInfo._color = _color;
    pixelInfo._pos = worldIntersection;
    pixelInfo._normalizedVector = normal;

    if (material != nullptr) {
        pixelInfo._color = material->applyMaterial
            (pixelInfo, radius, 0.0f, *this);
    }

    return pixelInfo;
}

std::optional<Math::Point3D> Sphere::getIntersection(const Math::Ray &ray)
    const {
    auto t = distance(ray);
    if (t.has_value())
        return ray.getOrigin() + ray.getDirection() * t.value();
    return std::nullopt;
}

std::optional<Math::Vector3D> Sphere::getNormal(const Math::Point3D &point)
    const {
    Math::Vector3D result(point - _position);
    if (result.length() == radius)
        return result.normalize();
    return std::nullopt;
}

Type Sphere::getType() const { return Type::SPHERE; }

extern "C" {
    std::shared_ptr<IPrimitives> createPrimitive(
        std::shared_ptr<std::map<ValueType_t, ValueType>> map,
        const std::vector<std::shared_ptr<std::map<ValueType_t,
        ValueType>>> &graphSceneList) {
        return std::make_shared<Sphere>(map, graphSceneList);
    }

    ObjectType getType() {
        return ObjectType::TYPE_PRIMITIVE;
    }

    std::string getName() {
        return "spheres";
    }
}
