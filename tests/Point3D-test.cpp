/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Pointµ3D-test
*/

#include <criterion/criterion.h>
#include "../common/Point3D.hpp"

Test(Point3D, constructor_and_getters) {
    Math::Point3D point(1.0, 2.0, 3.0);
    cr_assert_eq(point.getX(), 1.0);
    cr_assert_eq(point.getY(), 2.0);
    cr_assert_eq(point.getZ(), 3.0);
}

Test(Point3D, setters) {
    Math::Point3D point;
    point.setX(4.0);
    point.setY(5.0);
    point.setZ(6.0);
    cr_assert_eq(point.getX(), 4.0);
    cr_assert_eq(point.getY(), 5.0);
    cr_assert_eq(point.getZ(), 6.0);
}

Test(Point3D, addition_operator) {
    Math::Point3D point1(1.0, 2.0, 3.0);
    Math::Point3D point2(4.0, 5.0, 6.0);
    Math::Point3D result = point1 + point2;
    cr_assert_eq(result.getX(), 5.0);
    cr_assert_eq(result.getY(), 7.0);
    cr_assert_eq(result.getZ(), 9.0);
}

Test(Point3D, subtraction_operator) {
    Math::Point3D point1(4.0, 5.0, 6.0);
    Math::Point3D point2(1.0, 2.0, 3.0);
    Math::Point3D result = point1 - point2;
    cr_assert_eq(result.getX(), 3.0);
    cr_assert_eq(result.getY(), 3.0);
    cr_assert_eq(result.getZ(), 3.0);
}

Test(Point3D, addition_with_vector) {
    Math::Point3D point(1.0, 2.0, 3.0);
    Math::Vector3D vector(4.0, 5.0, 6.0);
    Math::Point3D result = point + vector;
    cr_assert_eq(result.getX(), 5.0);
    cr_assert_eq(result.getY(), 7.0);
    cr_assert_eq(result.getZ(), 9.0);
}

Test(Point3D, subtraction_with_vector) {
    Math::Point3D point(4.0, 5.0, 6.0);
    Math::Vector3D vector(1.0, 2.0, 3.0);
    Math::Point3D result = point - vector;
    cr_assert_eq(result.getX(), 3.0);
    cr_assert_eq(result.getY(), 3.0);
    cr_assert_eq(result.getZ(), 3.0);
}

Test(Point3D, dot_product_with_point) {
    Math::Point3D point1(1.0, 2.0, 3.0);
    Math::Point3D point2(4.0, 5.0, 6.0);
    double result = point1.dot(point2);
    cr_assert_eq(result, 32.0);
}

Test(Point3D, dot_product_with_vector) {
    Math::Point3D point(1.0, 2.0, 3.0);
    Math::Vector3D vector(4.0, 5.0, 6.0);
    double result = point.dot(vector);
    cr_assert_eq(result, 32.0);
}

Test(Point3D, normalize) {
    Math::Point3D point(3.0, 4.0, 0.0);
    Math::Point3D normalized = point.normalize();
    cr_assert_float_eq(normalized.getX(), 0.6, 0.001);
    cr_assert_float_eq(normalized.getY(), 0.8, 0.001);
    cr_assert_float_eq(normalized.getZ(), 0.0, 0.001);
}

Test(Point3D, normalize_zero_length) {
    Math::Point3D point(0.0, 0.0, 0.0);
    Math::Point3D normalized = point.normalize();
    cr_assert_eq(normalized.getX(), 0.0);
    cr_assert_eq(normalized.getY(), 0.0);
    cr_assert_eq(normalized.getZ(), 0.0);
}

Test(Point3D, constructor_from_vector) {
    Math::Vector3D vector(1.0, 2.0, 3.0);
    Math::Point3D point(vector);
    cr_assert_eq(point.getX(), 1.0);
    cr_assert_eq(point.getY(), 2.0);
    cr_assert_eq(point.getZ(), 3.0);
}

Test(Point3D, addition_assignment_operator) {
    Math::Point3D point(1.0, 2.0, 3.0);
    Math::Vector3D vector(4.0, 5.0, 6.0);
    point += vector;
    cr_assert_eq(point.getX(), 5.0);
    cr_assert_eq(point.getY(), 7.0);
    cr_assert_eq(point.getZ(), 9.0);
}

Test(Point3D, subtraction_assignment_operator) {
    Math::Point3D point(4.0, 5.0, 6.0);
    Math::Vector3D vector(1.0, 2.0, 3.0);
    point -= vector;
    cr_assert_eq(point.getX(), 3.0);
    cr_assert_eq(point.getY(), 3.0);
    cr_assert_eq(point.getZ(), 3.0);
}
