/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Vector3D
*/

#include "Vector3D.hpp"
#include "Color.hpp"

namespace Math {

Vector3D::Vector3D() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}


Vector3D::Vector3D(uint32_t& state) {
    this->x = Math::Random::normalDistribution(state);
    this->y = Math::Random::normalDistribution(state);
    this->z = Math::Random::normalDistribution(state);
}

Vector3D::Vector3D(double _x, double _y, double _z) {
    this->x = _x;
    this->y = _y;
    this->z = _z;
}

Vector3D::Vector3D(const Math::Point3D &point) {
    this->x = point.getX();
    this->y = point.getY();
    this->z = point.getZ();
}

/* Getter */
double Vector3D::getX() const { return this->x; }

double Vector3D::getY() const { return this->y; }

double Vector3D::getZ() const { return this->z; }

/* Setter */

void Vector3D::setX(double _x) { this->x = _x; }

void Vector3D::setY(double _y) { this->y = _y; }

void Vector3D::setZ(double _z) { this->z = _z; }

/* Methods */

double Vector3D::length() const {
    return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

double Vector3D::dot(const Vector3D &other) const {
    return this->x * other.x + this->y * other.y + this->z * other.z;
}

Vector3D Vector3D::normalize() const {
    double len = this->length();
    if (len == 0) return *this;
    return Vector3D(this->x / len, this->y / len, this->z / len);
}

Vector3D Vector3D::cross(const Vector3D &other) const {
    return Vector3D(this->y * other.z - this->z * other.y,
                    this->z * other.x - this->x * other.z,
                    this->x * other.y - this->y * other.x);
}

Vector3D Vector3D::RandomInHemisphere(uint32_t& state) const {
    Vector3D randomVector(state);
    randomVector = randomVector.normalize();

    if (this->dot(randomVector) < 0.0f)
        randomVector = -randomVector;
    return randomVector;
}

Vector3D Vector3D::getAnyPerpendicular() const {
    if (std::abs(this->x) > std::abs(this->y)) {
        // Use (z, 0, -x) if x is not close to zero
        return Vector3D(this->z, 0, -this->x).normalize();
    } else {
        // Use (0, -z, y) otherwise
        return Vector3D(0, -this->z, this->y).normalize();
    }
}

/* Operator */


Vector3D Vector3D::operator-() const {
    return Vector3D(-x, -y, -z);
}

Vector3D Vector3D::operator+(const Vector3D &other) const {
    return Vector3D(this->x + other.x, this->y + other.y, this->z + other.z);
}

Vector3D Vector3D::operator-(const Vector3D &other) const {
    return Vector3D(this->x - other.x, this->y - other.y, this->z - other.z);
}

Vector3D Vector3D::operator+=(const Vector3D &other) {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
}

Vector3D Vector3D::operator+=(const Color &other) {
    this->x += other.getRed();
    this->y += other.getGreen();
    this->z += other.getBlue();
    return *this;
}


Vector3D Vector3D::operator-=(const Vector3D &other) {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return *this;
}

Vector3D Vector3D::operator*(const Vector3D &other) const {
    return Vector3D(this->x * other.x, this->y * other.y, this->z * other.z);
}

Vector3D Vector3D::operator*=(const Vector3D &other) {
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
    return *this;
}

Vector3D Vector3D::operator/(const Vector3D &other) const {
    return Vector3D(this->x / other.x, this->y / other.y, this->z / other.z);
}

Vector3D Vector3D::operator/=(const Vector3D &other) {
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;
    return *this;
}

/* Operator with scalar */

Vector3D Vector3D::operator*(double scalar) const {
    return Vector3D(this->x * scalar, this->y * scalar, this->z * scalar);
}

Vector3D &Vector3D::operator*=(double scalar) {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    return *this;
}

Vector3D Vector3D::operator/(double scalar) const {
    return Vector3D(this->x / scalar, this->y / scalar, this->z / scalar);
}

Vector3D &Vector3D::operator/=(double scalar) {
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
    return *this;
}

}  // namespace Math
