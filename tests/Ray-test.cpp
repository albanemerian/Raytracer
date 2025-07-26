#include <criterion/criterion.h>
#include "../common/Ray.hpp"

Test(Ray, default_constructor) {
    Ray ray;
    cr_assert_eq(ray.getOrigin().getX(), 0.0);
    cr_assert_eq(ray.getDirection().getX(), 0.0);
    cr_assert_eq(ray.getIntensity(), 0.0);
}

Test(Ray, parameterized_constructor) {
    Math::Point3D origin(1.0, 2.0, 3.0);
    Math::Vector3D direction(4.0, 5.0, 6.0);
    Math::Ray ray(origin, direction);
    cr_assert_eq(ray.getOrigin().getX(), 1.0);
    cr_assert_eq(ray.getDirection().getX(), 4.0);
}

Test(Ray, setters_and_getters) {
    Ray ray;
    Math::Point3D origin(1.0, 2.0, 3.0);
    Math::Vector3D direction(4.0, 5.0, 6.0);
    ray.setOrigin(origin);
    ray.setDirection(direction);
    ray.setIntensity(0.8);
    cr_assert_eq(ray.getOrigin().getX(), 1.0);
    cr_assert_eq(ray.getDirection().getX(), 4.0);
    cr_assert_eq(ray.getIntensity(), 0.8);
}

Test(Ray, constructor_parameter) {
    Math::Point3D origin(1.0, 2.0, 3.0);
    Math::Vector3D direction(4.0, 5.0, 6.0);
    Color color(255, 0, 0);
    double intensity = 0.5;
    Ray ray(origin, direction, color, intensity);
    cr_assert_eq(ray.getOrigin().getX(), 1.0);
    cr_assert_eq(ray.getDirection().getX(), 4.0);
    cr_assert_eq(ray.getColor().getRed(), 255);
    cr_assert_eq(ray.getIntensity(), 0.5);
    ray.~Ray();
}

Test(Ray, setColor) {
    Ray ray;
    Color color(255, 0, 0);
    ray.setColor(color);
    cr_assert_eq(ray.getColor().getRed(), 255);
}

Test(Ray, setIntensity) {
    Ray ray;
    ray.setIntensity(0.8);
    cr_assert_eq(ray.getIntensity(), 0.8);
}

Test(Ray, getColor) {
    Ray ray;
    Color color(255, 0, 0);
    ray.setColor(color);
    cr_assert_eq(ray.getColor().getRed(), 255);
}

Test(Ray, getIntensity) {
    Ray ray;
    ray.setIntensity(0.8);
    cr_assert_eq(ray.getIntensity(), 0.8);
}
