/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Color-test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../common/Color.hpp"


Test(Color, default_constructor) {
    Color color;

    cr_assert_eq(color.getRed(), 0, "Default red value is incorrect.");
    cr_assert_eq(color.getGreen(), 0, "Default green value is incorrect.");
    cr_assert_eq(color.getBlue(), 0, "Default blue value is incorrect.");
    cr_assert_eq(color.getTransparency(), 255, "Default transparency value is incorrect.");
}

Test(Color, parameterized_constructor) {
    Color color(255, 128, 64, 128);

    cr_assert_eq(color.getRed(), 255, "Red value is incorrect.");
    cr_assert_eq(color.getGreen(), 128, "Green value is incorrect.");
    cr_assert_eq(color.getBlue(), 64, "Blue value is incorrect.");
    cr_assert_eq(color.getTransparency(), 128, "Transparency value is incorrect.");
}

Test(Color, vector3d_assignment) {
    Math::Vector3D vec(255, 128, 64);
    Color color;

    color = vec;

    cr_assert_eq(color.getRed(), 255, "Red value is incorrect.");
    cr_assert_eq(color.getGreen(), 128, "Green value is incorrect.");
    cr_assert_eq(color.getBlue(), 64, "Blue value is incorrect.");
}

Test(Color, wrong_vector3d_assignment) {
    Math::Vector3D vec(256, 128, 64);
    Color color;

    cr_assert_throw(color = vec, ColorException, "Color values must be between 0 and 255");
}

Test(Color, getter_test) {
    Color color(255, 128, 64);

    color.setTransparency(0.4f);
    cr_assert_eq(color.getRed(), 255, "Red value is incorrect.");
    cr_assert_eq(color.getGreen(), 128, "Green value is incorrect.");
    cr_assert_eq(color.getBlue(), 64, "Blue value is incorrect.");
    cr_assert_eq(color.getTransparency(), 153, "Transparency value is incorrect.");
}
