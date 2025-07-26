/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Point3D
*/

#ifndef POINT3D_HPP_
#define POINT3D_HPP_

#include "Vector3D.hpp"

namespace Math {

class Point3D {
   public:
      Point3D();
      Point3D(double x, double y, double z);
      ~Point3D() = default;

      /* Getter */
      double getX() const;
      double getY() const;
      double getZ() const;

      /* Setter */
      void setX(double x);
      void setY(double y);
      void setZ(double z);

      /* Methods */
      Point3D normalize() const;
      Point3D operator+(const Point3D &other) const;
      Point3D operator-(const Point3D &other) const;
      Point3D operator+(const Vector3D &vector) const;
      Point3D operator-(const Vector3D &vector) const;
      Point3D operator*(const Vector3D &vector) const;
      Point3D operator/(const Vector3D &vector) const;
      double dot(const Point3D &other) const;
      double dot(const Vector3D &vector) const;
      Point3D(const Vector3D &vector);
      /* Operators */
      Point3D &operator+=(const Vector3D &vector);
      Point3D &operator-=(const Vector3D &vector);

   protected:
   private:
      double x;
      double y;
      double z;
};

}  // namespace Math

#endif /* !POINT3D_HPP_ */
