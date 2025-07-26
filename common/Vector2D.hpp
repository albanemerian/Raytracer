/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Vector2D
*/

#ifndef VECTOR2D_HPP_
#define VECTOR2D_HPP_

namespace Math {

class Vector2D {
    public:
        Vector2D();
        Vector2D(double x, double y) : _x(x), _y(y) {}
        ~Vector2D() = default;

    // getter
    double getX() const { return _x; }
    double getY() const { return _y; }

    // setter
    void setX(double x) { _x = x; }
    void setY(double y) { _y = y; }

 protected:
 private:
    double _x;
    double _y;
};

}  // namespace Math

#endif /* !VECTOR2D_HPP_ */
