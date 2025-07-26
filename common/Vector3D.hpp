/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Vector3D
*/

#include <cmath>
#include <iostream>
#include <vector>
#include <functional>

#include "Point3D.hpp"
#include "Random.hpp"

#ifndef VECTOR3D_HPP_
#define VECTOR3D_HPP_

class Color;

namespace Math {

class Point3D;

class Vector3D {
 public:
    Vector3D();
    Vector3D(uint32_t& state);
    Vector3D(double x, double y, double z);
    Vector3D(const Math::Point3D &point);
    ~Vector3D() = default;

    /* Getter */
    double getX() const;
    double getY() const;
    double getZ() const;

    /* Setter */
    void setX(double x);
    void setY(double y);
    void setZ(double z);

    /* Methods */
    double length() const;
    double dot(const Vector3D &other) const;

    // Add cross product
    Vector3D cross(const Vector3D &other) const;

    Vector3D normalize() const;

    Vector3D RandomInHemisphere(uint32_t& state) const;

    Vector3D getAnyPerpendicular() const;

    /* Operators */
    Vector3D operator-() const;
    Vector3D operator+(const Vector3D &other) const;
    Vector3D operator-(const Vector3D &other) const;

    Vector3D operator+=(const Vector3D &other);
    Vector3D operator+=(const Color &other);
    Vector3D operator-=(const Vector3D &other);

    Vector3D operator*(const Vector3D &other) const;
    Vector3D operator*=(const Vector3D &other);

    Vector3D operator/(const Vector3D &other) const;
    Vector3D operator/=(const Vector3D &other);

    /* Operator and Scalar */
    Vector3D operator*(double scalar) const;
    Vector3D &operator*=(double scalar);
    Vector3D operator/(double scalar) const;
    Vector3D &operator/=(double scalar);

 protected:
    double x;
    double y;
    double z;

 private:
};

inline Vector3D operator*(double scalar, const Vector3D &vec) {
    return Vector3D(vec.getX() * scalar, vec.getY() * scalar,
                    vec.getZ() * scalar);
}

inline Vector3D operator/(double scalar, const Vector3D &vec) {
   return Vector3D(vec.getX() / scalar, vec.getY() / scalar,
                   vec.getZ() / scalar);
}

}  // namespace Math

#endif /* !VECTOR3D_HPP_ */
