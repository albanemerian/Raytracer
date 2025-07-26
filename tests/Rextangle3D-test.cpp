/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Rextangle3D-test
*/

#include <criterion/criterion.h>
#include "../common/Exception/MathExeption.hpp"
#include "../common/Rectangle3D.hpp"

Test(Rectangle3D, constructor_and_getters) {
    Math::Point3D origin(1.0, 2.0, 3.0);
    Math::Vector3D bottom_side(4.0, 5.0, 6.0);
    Math::Vector3D left_side(7.0, 8.0, 9.0);
    Rectangle3D rect(origin, bottom_side, left_side);

    cr_assert_eq(rect._origin.getX(), 1.0);
    cr_assert_eq(rect._origin.getY(), 2.0);
    cr_assert_eq(rect._origin.getZ(), 3.0);
    cr_assert_eq(rect._bottom_side.getX(), 4.0);
    cr_assert_eq(rect._bottom_side.getY(), 5.0);
    cr_assert_eq(rect._bottom_side.getZ(), 6.0);
    cr_assert_eq(rect._left_side.getX(), 7.0);
    cr_assert_eq(rect._left_side.getY(), 8.0);
    cr_assert_eq(rect._left_side.getZ(), 9.0);
}

Test(Rectangle3D, pointAt) {
    Math::Point3D origin(0.0, 0.0, 0.0);
    Math::Vector3D bottom_side(1.0, 0.0, 0.0);
    Math::Vector3D left_side(0.0, 1.0, 0.0);
    Rectangle3D rect(origin, bottom_side, left_side);

    Math::Point3D point = rect.pointAt(0.5, 0.5);
    cr_assert_eq(point.getX(), 0.5);
    cr_assert_eq(point.getY(), 0.5);
    cr_assert_eq(point.getZ(), 0.0);
}

Test(Rectangle3D, width_and_height) {
    Math::Point3D origin(0.0, 0.0, 0.0);
    Math::Vector3D bottom_side(2.0, 0.0, 0.0);
    Math::Vector3D left_side(0.0, 3.0, 0.0);
    Rectangle3D rect(origin, bottom_side, left_side);

    cr_assert_eq(rect.getWidth(), 2);
    cr_assert_eq(rect.getHeight(), 3);
}

Test(Rectangle3D, constructor_with_rotation) {
    Math::Point3D origin(0.0, 0.0, 0.0);
    Math::Rot3D rotation(30.0, 45.0, 60.0);
    Rectangle3D rect(origin, rotation, 2.0, 3.0);
    cr_assert_eq(rect.getWidth(), 2);
    cr_assert_eq(rect.getHeight(), 3);
}

Test(Rectangle3D, pointAt_out_of_bounds) {
    Math::Point3D origin(0.0, 0.0, 0.0);
    Math::Vector3D bottom_side(1.0, 0.0, 0.0);
    Math::Vector3D left_side(0.0, 1.0, 0.0);
    Rectangle3D rect(origin, bottom_side, left_side);
    cr_assert_throw(rect.pointAt(1.5, 0.5), MathExeption);
}
