/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Vector3D-test
*/

#include <criterion/criterion.h>
#include "../common/Vector3D.hpp"

Test(Vector3D, constructor_and_getters) {
    Math::Vector3D vec(1.0, 2.0, 3.0);
    cr_assert_eq(vec.getX(), 1.0);
    cr_assert_eq(vec.getY(), 2.0);
    cr_assert_eq(vec.getZ(), 3.0);
}

Test(Vector3D, setters) {
    Math::Vector3D vec;
    vec.setX(4.0);
    vec.setY(5.0);
    vec.setZ(6.0);
    cr_assert_eq(vec.getX(), 4.0);
    cr_assert_eq(vec.getY(), 5.0);
    cr_assert_eq(vec.getZ(), 6.0);
}

Test(Vector3D, length) {
    Math::Vector3D vec(3.0, 4.0, 0.0);
    cr_assert_float_eq(vec.length(), 5.0, 0.001);
}

Test(Vector3D, dot_product) {
    Math::Vector3D vec1(1.0, 2.0, 3.0);
    Math::Vector3D vec2(4.0, -5.0, 6.0);
    cr_assert_eq(vec1.dot(vec2), 12.0);
}

Test(Vector3D, cross_product) {
    Math::Vector3D vec1(1.0, 0.0, 0.0);
    Math::Vector3D vec2(0.0, 1.0, 0.0);
    Math::Vector3D result = vec1.cross(vec2);
    cr_assert_eq(result.getX(), 0.0);
    cr_assert_eq(result.getY(), 0.0);
    cr_assert_eq(result.getZ(), 1.0);
}

Test(Vector3D, normalize) {
    Math::Vector3D vec(3.0, 0.0, 4.0);
    Math::Vector3D normalized = vec.normalize();
    cr_assert_float_eq(normalized.length(), 1.0, 0.001);
    cr_assert_float_eq(normalized.getX(), 0.6, 0.001);
    cr_assert_float_eq(normalized.getZ(), 0.8, 0.001);
}

Test(Vector3D, normalize_zero_length) {
    Math::Vector3D vec(0.0, 0.0, 0.0); // Edge case: zero-length vector
    Math::Vector3D normalized = vec.normalize();
    cr_assert_eq(normalized.getX(), 0.0);
    cr_assert_eq(normalized.getY(), 0.0);
    cr_assert_eq(normalized.getZ(), 0.0);
}

Test(Vector3D, operators) {
    Math::Vector3D vec1(1.0, 2.0, 3.0);
    Math::Vector3D vec2(4.0, 5.0, 6.0);

    // Addition
    Math::Vector3D sum = vec1 + vec2;
    cr_assert_eq(sum.getX(), 5.0);
    cr_assert_eq(sum.getY(), 7.0);
    cr_assert_eq(sum.getZ(), 9.0);

    // Subtraction
    Math::Vector3D diff = vec1 - vec2;
    cr_assert_eq(diff.getX(), -3.0);
    cr_assert_eq(diff.getY(), -3.0);
    cr_assert_eq(diff.getZ(), -3.0);

    // Scalar multiplication
    Math::Vector3D scaled = vec1 * 2.0;
    cr_assert_eq(scaled.getX(), 2.0);
    cr_assert_eq(scaled.getY(), 4.0);
    cr_assert_eq(scaled.getZ(), 6.0);

    // Scalar division
    Math::Vector3D divided = vec1 / 2.0;
    cr_assert_eq(divided.getX(), 0.5);
    cr_assert_eq(divided.getY(), 1.0);
    cr_assert_eq(divided.getZ(), 1.5);
}

Test(Vector3D, scalar_multiplication_assignment) {
    Math::Vector3D vec(1.0, 2.0, 3.0);
    vec *= 2.0;
    cr_assert_eq(vec.getX(), 2.0);
    cr_assert_eq(vec.getY(), 4.0);
    cr_assert_eq(vec.getZ(), 6.0);
}

Test(Vector3D, scalar_division_assignment) {
    Math::Vector3D vec(2.0, 4.0, 6.0);
    vec /= 2.0;
    cr_assert_eq(vec.getX(), 1.0);
    cr_assert_eq(vec.getY(), 2.0);
    cr_assert_eq(vec.getZ(), 3.0);
}

Test(Vector3D, operator_times) {
    Math::Vector3D vec1(1.0, 2.0, 3.0);
    Math::Vector3D vec2(4.0, 5.0, 6.0);
    Math::Vector3D result = vec1 * vec2;
    cr_assert_eq(result.getX(), 4.0);
    cr_assert_eq(result.getY(), 10.0);
    cr_assert_eq(result.getZ(), 18.0);
}

Test(Vector3D, operator_minus) {
    Math::Vector3D vec1(1.0, 2.0, 3.0);
    Math::Vector3D vec2(4.0, 5.0, 6.0);
    Math::Vector3D result = vec1 - vec2;
    cr_assert_eq(result.getX(), -3.0);
    cr_assert_eq(result.getY(), -3.0);
    cr_assert_eq(result.getZ(), -3.0);
}

Test(Vector3D, operator_plus_equal) {
    Math::Vector3D vec1(1.0, 2.0, 3.0);
    Math::Vector3D vec2(4.0, 5.0, 6.0);
    vec1 += vec2;
    cr_assert_eq(vec1.getX(), 5.0);
    cr_assert_eq(vec1.getY(), 7.0);
    cr_assert_eq(vec1.getZ(), 9.0);
}

Test(Vector3D, operator_minus_equal) {
    Math::Vector3D vec1(5.0, 7.0, 9.0);
    Math::Vector3D vec2(1.0, 2.0, 3.0);
    vec1 -= vec2;
    cr_assert_eq(vec1.getX(), 4.0);
    cr_assert_eq(vec1.getY(), 5.0);
    cr_assert_eq(vec1.getZ(), 6.0);
}

Test(Vector3D, operator_times_equal) {
    Math::Vector3D vec1(1.0, 2.0, 3.0);
    Math::Vector3D vec2(4.0, 5.0, 6.0);
    vec1 *= vec2;
    cr_assert_eq(vec1.getX(), 4.0);
    cr_assert_eq(vec1.getY(), 10.0);
    cr_assert_eq(vec1.getZ(), 18.0);
}

Test(Vector3D, division_operator) {
    Math::Vector3D vec1(4.0, 6.0, 8.0);
    Math::Vector3D vec2(2.0, 3.0, 4.0);
    Math::Vector3D result = vec1 / vec2;
    cr_assert_eq(result.getX(), 2.0);
    cr_assert_eq(result.getY(), 2.0);
    cr_assert_eq(result.getZ(), 2.0);
}

Test(Vector3D, division_assignment_operator) {
    Math::Vector3D vec1(4.0, 6.0, 8.0);
    Math::Vector3D vec2(2.0, 3.0, 4.0);
    vec1 /= vec2;
    cr_assert_eq(vec1.getX(), 2.0);
    cr_assert_eq(vec1.getY(), 2.0);
    cr_assert_eq(vec1.getZ(), 2.0);
}

Test(Vector3D, scalar_division_operator) {
    Math::Vector3D vec(4.0, 6.0, 8.0);
    Math::Vector3D result = vec / 2.0;
    cr_assert_eq(result.getX(), 2.0);
    cr_assert_eq(result.getY(), 3.0);
    cr_assert_eq(result.getZ(), 4.0);
}

Test(Vector3D, scalar_division_assignment_operator) {
    Math::Vector3D vec(4.0, 6.0, 8.0);
    vec /= 2.0;
    cr_assert_eq(vec.getX(), 2.0);
    cr_assert_eq(vec.getY(), 3.0);
    cr_assert_eq(vec.getZ(), 4.0);
}

Test(Vector3D, operator_unary_minus) {
    Math::Vector3D vec(1.0, -2.0, 3.0);
    Math::Vector3D result = -vec;
    cr_assert_eq(result.getX(), -1.0);
    cr_assert_eq(result.getY(), 2.0);
    cr_assert_eq(result.getZ(), -3.0);
}

Test(Vector3D, scalar_multiplication_left) {
    Math::Vector3D vec(1.0, 2.0, 3.0);
    Math::Vector3D result = 2.0 * vec;
    cr_assert_eq(result.getX(), 2.0);
    cr_assert_eq(result.getY(), 4.0);
    cr_assert_eq(result.getZ(), 6.0);
}
