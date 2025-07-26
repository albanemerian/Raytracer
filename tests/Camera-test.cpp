/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Camera-test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../common/Camera.hpp"
#include "../common/Point3D.hpp"
#include "../common/Vector3D.hpp"
#include "../common/Rectangle3D.hpp"
#include "../common/Ray.hpp"

Test(Camera, default_constructor) {
    Camera camera;

    cr_assert(camera.getOrigin().getX() == 0 && camera.getOrigin().getY() == 0 && camera.getOrigin().getZ() == 0,
              "Default origin is incorrect.");
}

Test(Camera, parameterized_constructor) {
    Rectangle3D screen(Math::Point3D(-1, -1, -1), Math::Vector3D(2, 0, 0), Math::Vector3D(0, 2, 0));
    Camera camera(screen);

    cr_assert(camera.getOrigin().getX() == 0 && camera.getOrigin().getY() == 0 && camera.getOrigin().getZ() == 0,
              "Origin is incorrect.");
}

Test(Camera, update_screen) {
    Camera camera;
    camera.setFieldOfView(90.0f);
    camera.setResolution(1920, 1080);
    camera.setRotation(Math::Point3D(0, 0, 0));
    camera.updateScreen();

    float aspectRatio = 1920.0f / 1080.0f;
    float screenHeight = 2.0f * std::tan((90.0f / 2.0f) * (M_PI / 180.0f));
    float screenWidth = screenHeight * aspectRatio;

    cr_assert(camera.getRotation().getX() == 0 && camera.getRotation().getY() == 0 && camera.getRotation().getZ() == 0,
              "Rotation is incorrect.");
    camera.setPosition(Math::Vector3D(0, 0, 0));
    cr_assert(camera.getPosition().getX() == 0 && camera.getPosition().getY() == 0 && camera.getPosition().getZ() == 0,
              "Position is incorrect.");
    cr_assert(camera.getFieldOfView() == 90.0f,
              "Field of view is incorrect.");
    cr_assert(camera.getWidth() == 1920,
              "Width is incorrect.");
    cr_assert(camera.getHeight() == 1080,
                "Height is incorrect.");
}

Test(Camera, ray_generation) {
    Camera camera;
    Math::Ray ray = camera.ray(0.5, 0.5);

    cr_assert(ray.getOrigin().getX() == 0 && ray.getOrigin().getY() == 0 && ray.getOrigin().getZ() == 0,
              "Ray origin is incorrect.");
}

