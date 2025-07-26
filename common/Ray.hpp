/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Ray
*/

#include "Color.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"

#ifndef RAY_HPP_
#define RAY_HPP_

namespace Math {
class Ray {
 public:
    Ray() : _origin(), _direction() {}
    Ray(Point3D origin, Vector3D direction) : _origin(origin), _direction(direction), _refraction_index(1) {}
    Ray(Point3D origin, Vector3D direction, double Refraction_index) : _origin(origin), _direction(direction), _refraction_index( Refraction_index) {}
    ~Ray() = default;

    /* Setter */
    void setOrigin(Point3D origin) { this->_origin = origin; }
    void setDirection(Vector3D direction) { this->_direction = direction; }
    void setRefractionIndex(double Refraction_index) { this->_refraction_index = Refraction_index; }

    /* Getter */
    Point3D getOrigin() const { return this->_origin; }
    Vector3D getDirection() const { return this->_direction; }
    double getRefractionIndex() const { return this->_refraction_index; }

 private:
    Point3D _origin;
    Vector3D _direction;
    double _refraction_index;
};
} // namespace Math

class Ray {
 public:
    Ray() : _ray(), _color(), _intensity(0) {}
    Ray(Math::Point3D origin, Math::Vector3D direction, Color color, double intensity)
        : _ray(origin, direction), _color(color), _intensity(intensity) {}
    ~Ray() = default;

    /* Setter */
    void setOrigin(Math::Point3D origin);
    void setDirection(Math::Vector3D direction);
    void setColor(Color color);
    void setIntensity(double intensity);

    /* Getter */
    Math::Point3D getOrigin() const;
    Math::Vector3D getDirection() const;
    Color getColor() const;
    double getIntensity() const;

 private:
    Math::Ray _ray;
    Color _color;
    double _intensity;
};

#endif /* !RAY_HPP_ */
