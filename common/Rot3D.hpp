/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Raytracer
*/

#ifndef ROT3D_HPP
#define ROT3D_HPP

#include "Vector3D.hpp"

namespace Math {
class Rot3D {
 public:
    double x_pitch;
    double z_yaw;
    double y_roll;

    Rot3D(double x_pitch = 0, double z_yaw = 0, double y_roll = 0);
    Rot3D(const Rot3D &other);
    Vector3D toVector() const;

    Rot3D operator+(const Rot3D &other) const;
    Rot3D &operator+=(const Rot3D &other);
    Rot3D operator-(const Rot3D &other) const;
    Rot3D &operator-=(const Rot3D &other);
    Rot3D operator-() const;
    Vector3D toUnitVector() const;
    Vector3D rotate(const Vector3D &vec) const;
    Vector3D inverseRotate(const Vector3D &vec) const;
    Rot3D &operator=(const Rot3D &other);

    double dot(const Rot3D &other) const;

    double getX() const { return x_pitch; }
    double getY() const { return y_roll; }
    double getZ() const { return z_yaw; }
};
}  // namespace Math

#endif  // ROT3D_HPP
