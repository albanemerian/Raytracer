/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Header
*/

#include "Point3D.hpp"
#include "Rot3D.hpp"
#include "Vector3D.hpp"

#ifndef RECTANGLE3D_HPP_
    #define RECTANGLE3D_HPP_

class Rectangle3D {
    public:
        Rectangle3D(const Math::Point3D& origin, const Math::Vector3D& bottom_side, const Math::Vector3D& left_side);
        Rectangle3D(const Math::Point3D &point, const  Math::Rot3D &rotation, double width = 1, double height = 1);
        ~Rectangle3D();

        Math::Point3D _origin;
        Math::Vector3D _bottom_side;
        Math::Vector3D _left_side;
        int getWidth() const;
        int getHeight() const;
        Math::Point3D pointAt(double u, double v) const;

    protected:
    private:
};

#endif /* !RECTANGLE3D_HPP_ */
