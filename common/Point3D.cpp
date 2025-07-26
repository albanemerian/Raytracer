/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** *$
*/

#include "Point3D.hpp"

namespace Math {

Point3D::Point3D() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}


Point3D::Point3D(double _x, double _y, double _z) {
    this->x = _x;
    this->y = _y;
    this->z = _z;
}

/* Getter */

double Point3D::getX() const { return this->x; }

double Point3D::getY() const { return this->y; }

double Point3D::getZ() const { return this->z; }

/* Setter */

void Point3D::setX(double _x) { this->x = _x; }

void Point3D::setY(double _y) { this->y = _y; }

void Point3D::setZ(double _z) { this->z = _z; }

/* Methods */
Point3D Point3D::operator+(const Point3D &other) const {
    return Point3D(this->x + other.x, this->y + other.y, this->z + other.z);
}

Point3D Point3D::operator-(const Point3D &other) const {
    return Point3D(this->x - other.x, this->y - other.y, this->z - other.z);
}

Point3D Point3D::operator+(const Vector3D &vector) const {
    return Point3D(this->x + vector.getX(), this->y + vector.getY(),
                   this->z + vector.getZ());
}

Point3D Point3D::operator-(const Vector3D &vector) const {
    return Point3D(this->x - vector.getX(), this->y - vector.getY(),
                   this->z - vector.getZ());
}

Point3D &Point3D::operator+=(const Vector3D &vector) {
    this->x += vector.getX();
    this->y += vector.getY();
    this->z += vector.getZ();
    return *this;
}

Point3D &Point3D::operator-=(const Vector3D &vector) {
    this->x -= vector.getX();
    this->y -= vector.getY();
    this->z -= vector.getZ();
    return *this;
}

Point3D::Point3D(const Vector3D &vector) {
    this->x = vector.getX();
    this->y = vector.getY();
    this->z = vector.getZ();
}

Point3D Point3D::normalize() const {
    double length = std::sqrt(x * x + y * y + z * z);
    if (length == 0) {
        return *this;
    }
    return Point3D(x / length, y / length, z / length);
}

double Point3D::dot(const Point3D &other) const {
    return this->x * other.x + this->y * other.y + this->z * other.z;
}

double Point3D::dot(const Vector3D &vector) const {
    return this->x * vector.getX() + this->y * vector.getY() +
           this->z * vector.getZ();
}

Point3D Point3D::operator*(const Vector3D &vector) const {
    return Point3D(this->x * vector.getX(), this->y * vector.getY(),
                   this->z * vector.getZ());
}

Point3D Point3D::operator/(const Vector3D &vector) const {
    return Point3D(this->x / vector.getX(), this->y / vector.getY(),
                   this->z / vector.getZ());
}

}  // namespace Math
