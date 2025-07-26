/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Raytracer
*/

#include "Rot3D.hpp"

#include <cmath>

namespace Math {

Rot3D::Rot3D(const Rot3D &other)
: x_pitch(other.x_pitch), z_yaw(other.z_yaw), y_roll(other.y_roll) {}

Rot3D::Rot3D(double new_x_pitch, double new_z_yaw, double new_y_roll)
: x_pitch(new_x_pitch), z_yaw(new_z_yaw), y_roll(new_y_roll) {}

Vector3D Rot3D::toVector() const { return Vector3D(x_pitch, z_yaw, y_roll); }

Vector3D Rot3D::toUnitVector() const {
    double radX = x_pitch * M_PI / 180.0;
    double radY = y_roll * M_PI / 180.0;
    double radZ = z_yaw * M_PI / 180.0;

    double x = cos(radY) * cos(radZ);
    double y = sin(radX) * cos(radZ);
    double z = sin(radZ);

    return Vector3D(x, y, z).normalize();
}

Rot3D Rot3D::operator+(const Rot3D &other) const {
    return Rot3D(x_pitch + other.x_pitch, z_yaw + other.z_yaw,
                y_roll + other.y_roll);
}

Rot3D &Rot3D::operator+=(const Rot3D &other) {
    x_pitch += other.x_pitch;
    z_yaw += other.z_yaw;
    y_roll += other.y_roll;
    return *this;
}

Rot3D Rot3D::operator-(const Rot3D &other) const {
    return Rot3D(x_pitch - other.x_pitch, z_yaw - other.z_yaw,
                y_roll - other.y_roll);
}

Rot3D &Rot3D::operator-=(const Rot3D &other) {
    x_pitch -= other.x_pitch;
    z_yaw -= other.z_yaw;
    y_roll -= other.y_roll;
    return *this;
}

Rot3D &Rot3D::operator=(const Rot3D &other) {
    if (this != &other) {
        x_pitch = other.x_pitch;
        z_yaw = other.z_yaw;
        y_roll = other.y_roll;
    }
    return *this;
}

Rot3D Rot3D::operator-() const {
    return Rot3D(-x_pitch, -z_yaw, -y_roll);
}

double Rot3D::dot(const Rot3D &other) const {
    Vector3D thisVec = this->toUnitVector();
    Vector3D otherVec = other.toUnitVector();
    return thisVec.dot(otherVec);
}

Vector3D Rot3D::inverseRotate(const Vector3D &vec) const {
    double radX = -x_pitch * M_PI / 180.0;
    double radY = -y_roll * M_PI / 180.0;
    double radZ = -z_yaw * M_PI / 180.0;

    Vector3D result = vec;

    double sinZ = sin(radZ);
    double cosZ = cos(radZ);
    result = Vector3D(
        result.getX() * cosZ + result.getY() * sinZ,
       -result.getX() * sinZ + result.getY() * cosZ,
        result.getZ());

    double sinY = sin(radY);
    double cosY = cos(radY);
    result = Vector3D(
        result.getX() * cosY - result.getZ() * sinY,
        result.getY(),
        result.getX() * sinY + result.getZ() * cosY);

    double sinX = sin(radX);
    double cosX = cos(radX);
    result = Vector3D(
        result.getX(),
        result.getY() * cosX + result.getZ() * sinX,
        - result.getY() * sinX + result.getZ() * cosX);

    return result;
}

Vector3D Rot3D::rotate(const Vector3D &vec) const {
    double radX = x_pitch * M_PI / 180.0;
    double radY = y_roll * M_PI / 180.0;
    double radZ = z_yaw * M_PI / 180.0;

    Vector3D result = vec;

    double sinX = sin(radX);
    double cosX = cos(radX);
    result = Vector3D(
        result.getX(),
        result.getY() * cosX - result.getZ() * sinX,
        result.getY() * sinX + result.getZ() * cosX);

    double sinY = sin(radY);
    double cosY = cos(radY);
    result = Vector3D(
        result.getX() * cosY + result.getZ() * sinY,
        result.getY(),
       -result.getX() * sinY + result.getZ() * cosY);

    double sinZ = sin(radZ);
    double cosZ = cos(radZ);
    result = Vector3D(
        result.getX() * cosZ - result.getY() * sinZ,
        result.getX() * sinZ + result.getY() * cosZ,
        result.getZ());

    return result;
}

}  // namespace Math
