/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Rectangle3D
*/

#include "Rectangle3D.hpp"
#include "Exception/MathExeption.hpp"

Rectangle3D::Rectangle3D(const Math::Point3D& origin,
    const Math::Vector3D& bottom_side,
    const Math::Vector3D& left_side)
    : _origin(origin), _bottom_side(bottom_side), _left_side(left_side) {
}

Rectangle3D::Rectangle3D(const Math::Point3D &point,
    const  Math::Rot3D &rotation, double width, double height) {
    Math::Vector3D forward = rotation.toUnitVector();
    Math::Vector3D right =
        Math::Vector3D(forward.getZ(), 0, -forward.getX()).normalize();
    Math::Vector3D up = forward.cross(right).normalize();

    _origin = point - forward;
    _bottom_side = right * width;
    _left_side = up * height;
}

Rectangle3D::~Rectangle3D() {
}

Math::Point3D Rectangle3D::pointAt(double u, double v) const {
    if (u < 0 || u > 1 || v < 0 || v > 1) {
        throw MathExeption("u and v must be in the range [0, 1]");
    }
    return _origin + (_bottom_side * u) + (_left_side * v);
}

int Rectangle3D::getWidth() const {
    return _bottom_side.length();
}

int Rectangle3D::getHeight() const {
    return _left_side.length();
}
