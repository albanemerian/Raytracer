/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Camera
*/

#include <stdexcept>
#include "Camera.hpp"

Camera::Camera() :
    _origin(0, 0, 0),
    _screen(Math::Point3D(-2, -1, -1), Math::Vector3D(4, 0, 0),
    Math::Vector3D(0, 2, 0)),
    antiAliasing(1) {
}

Camera::Camera(const Rectangle3D& screen) :
_origin(0, 0, 0), _screen(screen), antiAliasing(1) {
}

Camera::~Camera() {
}

void Camera::updateScreen() {
    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

    float screenHeight = 2.0f * std::tan((fieldOfView / 2.0f) *
        (M_PI / 180.0f));
    float screenWidth = screenHeight * aspectRatio;

    _screen = Rectangle3D(
        Math::Point3D(-screenWidth / 2.0f, -screenHeight / 2.0f, -1.0f),
        Math::Vector3D(screenWidth, 0, 0),
        Math::Vector3D(0, screenHeight, 0));
}

void Camera::setAntiAliasing(int aa) {
    if (aa <= 0 || (aa & (aa - 1)) != 0) {
        throw std::runtime_error("Anti-aliasing value must be a power of 2");
    }
    antiAliasing = aa;
}

Math::Ray Camera::ray(double u, double v) const {
    Math::Point3D target = _screen.pointAt(u, v);
    Math::Vector3D direction = target - _origin;
    return Math::Ray(_origin, direction);
}
