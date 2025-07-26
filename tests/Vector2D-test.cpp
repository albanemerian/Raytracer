/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Vector2D-test
*/

#include <criterion/criterion.h>
#include "../common/Vector2D.hpp"

Test(Vector2D, constructor_and_getters) {
    Math::Vector2D vec(1.0, 2.0);
    cr_assert_eq(vec.getX(), 1.0);
    cr_assert_eq(vec.getY(), 2.0);
}

Test(Vector2D, setters) {
    Math::Vector2D vec;
    vec.setX(3.0);
    vec.setY(4.0);

    cr_assert_eq(vec.getX(), 3.0);
    cr_assert_eq(vec.getY(), 4.0);
}

Test(Vector2D, addition_operator) {
    Math::Vector2D vec1;
    vec1.setX(1.0);
    vec1.setY(2.0);

    cr_assert_eq(vec1.getX(), 1.0);
    cr_assert_eq(vec1.getY(), 2.0);
}



