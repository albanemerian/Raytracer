/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** ICamera
*/

#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Rectangle3D.hpp"
#include "Ray.hpp"

#ifndef ICAMERA_HPP_
#define ICAMERA_HPP_

class Camera {
    public:
        Camera();
        Camera(const Camera&) = default;
        Camera(const Rectangle3D& screen);
        ~Camera();

        Math::Point3D _origin;
        Rectangle3D _screen;

        Camera& operator=(const Camera&) = default;

        void updateScreen();
        Math::Ray ray(double u, double v) const;

        /* Getter */
        Math::Point3D getOrigin() const { return _origin; }
        Math::Point3D getRotation() const { return _rotation; }
        Rectangle3D getScreen() const { return _screen; }
        Math::Vector3D getPosition() const { return _position; }
        int getWidth() const { return width; }
        int getHeight() const { return height; }
        float getFieldOfView() const { return fieldOfView; }
        int getAntiAliasing() const { return antiAliasing; }
        /* Setter */

        void setRotation(Math::Point3D rotation) { _rotation = rotation; }
        void setPosition(Math::Vector3D position) { _position = position; }
        void setResolution(int x, int y) { width = x; height = y; }
        void setHeight(int h) { height = h; }
        void setFieldOfView(float fov) { fieldOfView = fov; }
        void setAntiAliasing(int aa);

    protected:
        int width;
        int height;
        float fieldOfView;
        int antiAliasing;
        Math::Vector3D _rotation;
        Math::Vector3D _position;

    private:
};

#endif /* !ICAMERA_HPP_ */
