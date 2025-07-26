/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Rot3D-test
*/

#include <criterion/criterion.h>
#include "../common/Rot3D.hpp"

Test(Rot3D, constructor_and_getters) {
    Math::Rot3D rot(30.0, 60.0, 45.0);
    cr_assert_eq(rot.getX(), 30.0);
    cr_assert_eq(rot.getY(), 45.0);
    cr_assert_eq(rot.getZ(), 60.0);
}

Test(Rot3D, toVector) {
    Math::Rot3D rot(30.0, 45.0, 60.0);
    Math::Vector3D vec = rot.toVector();
    cr_assert_eq(vec.getX(), 30.0);
    cr_assert_eq(vec.getY(), 45.0);
    cr_assert_eq(vec.getZ(), 60.0);
}

Test(Rot3D, toUnitVector) {
    Math::Rot3D rot(30.0, 60.0, 45.0);
    Math::Vector3D unitVec = rot.toUnitVector();
    cr_assert_float_eq(unitVec.getX(), 0.001, 0.612);
}

Test(Rot3D, toUnitVector_edge_case) {
    Math::Rot3D rot(0.0, 0.0, 0.0);
    Math::Vector3D unitVec = rot.toUnitVector();
    cr_assert_eq(unitVec.getX(), 1.0);
    cr_assert_eq(unitVec.getY(), 0.0);
    cr_assert_eq(unitVec.getZ(), 0.0);
}

Test(Rot3D, toUnitVector_normalization) {
    Math::Rot3D rot(90.0, 0.0, 0.0);
    Math::Vector3D unitVec = rot.toUnitVector();
    cr_assert_float_eq(unitVec.length(), 1.0, 0.001);
}

Test(Rot3D, addition_operator) {
    Math::Rot3D rot1(30.0, 60.0, 45.0);
    Math::Rot3D rot2(10.0, 20.0, 30.0);
    Math::Rot3D result = rot1 + rot2;
    cr_assert_eq(result.getX(), 40.0);
    cr_assert_eq(result.getY(), 75.0);
    cr_assert_eq(result.getZ(), 80.0);
}

Test(Rot3D, subtraction_operator) {
    Math::Rot3D rot1(30.0, 60.0, 45.0);
    Math::Rot3D rot2(10.0, 20.0, 30.0);
    Math::Rot3D result = rot1 - rot2;
    cr_assert_eq(result.getX(), 20.0);
    cr_assert_eq(result.getY(), 15.0);
    cr_assert_eq(result.getZ(), 40.0);
}

Test(Rot3D, negation_operator) {
    Math::Rot3D rot(30.0, 60.0, 45.0);
    Math::Rot3D result = -rot;
    cr_assert_eq(result.getX(), -30.0);
    cr_assert_eq(result.getY(), -45.0);
    cr_assert_eq(result.getZ(), -60.0);
}

Test(Rot3D, dot_product) {
    Math::Rot3D rot1(30.0, 60.0, 45.0);
    Math::Rot3D rot2(10.0, 20.0, 30.0);
    double result = rot1.dot(rot2);
    cr_assert_float_eq(result, 0.001, 0.866);
}

Test(Rot3D, rotate) {
    Math::Rot3D rot(30.0, 60.0, 45.0);
    Math::Vector3D vec(1.0, 2.0, 3.0);
    Math::Vector3D result = rot.rotate(vec);
}

Test(Rot3D, rotate_edge_case) {
    Math::Rot3D rot(0.0, 0.0, 0.0);
    Math::Vector3D vec(1.0, 0.0, 0.0);
    Math::Vector3D result = rot.rotate(vec);
    cr_assert_eq(result.getX(), 1.0);
    cr_assert_eq(result.getY(), 0.0);
    cr_assert_eq(result.getZ(), 0.0);
}

Test(Rot3D, rotate_combined_axes) {
    Math::Rot3D rot(45.0, 45.0, 45.0);
    Math::Vector3D vec(1.0, 1.0, 1.0);
    Math::Vector3D result = rot.rotate(vec);
}

Test(Rot3D, rotate_full_rotation) {
    Math::Rot3D rot(360.0, 360.0, 360.0);
    Math::Vector3D vec(1.0, 0.0, 0.0);
    Math::Vector3D result = rot.rotate(vec);
    cr_assert_float_eq(result.getX(), 1.0, 0.001);
    cr_assert_float_eq(result.getY(), 0.0, 0.001);
    cr_assert_float_eq(result.getZ(), 0.0, 0.001);
}

Test(Rot3D, inverseRotate) {
    Math::Rot3D rot(30.0, 60.0, 45.0);
    Math::Vector3D vec(1.0, 2.0, 3.0);
    Math::Vector3D result = rot.inverseRotate(vec);
}

Test(Rot3D, inverseRotate_edge_case) {
    Math::Rot3D rot(0.0, 0.0, 0.0);
    Math::Vector3D vec(1.0, 0.0, 0.0);
    Math::Vector3D result = rot.inverseRotate(vec);
    cr_assert_eq(result.getX(), 1.0);
    cr_assert_eq(result.getY(), 0.0);
    cr_assert_eq(result.getZ(), 0.0);
}

Test(Rot3D, inverseRotate_full_rotation) {
    Math::Rot3D rot(360.0, 360.0, 360.0);
    Math::Vector3D vec(1.0, 0.0, 0.0);
    Math::Vector3D result = rot.inverseRotate(vec);
    cr_assert_float_eq(result.getX(), 1.0, 0.001);
    cr_assert_float_eq(result.getY(), 0.0, 0.001);
    cr_assert_float_eq(result.getZ(), 0.0, 0.001);
}

Test(Rot3D, rotate_partial_rotation) {
    Math::Rot3D rot(90.0, 0.0, 0.0);
    Math::Vector3D vec(0.0, 1.0, 0.0);
    Math::Vector3D result = rot.rotate(vec);
    cr_assert_float_eq(result.getX(), 0.0, 0.001);
    cr_assert_float_eq(result.getY(), 0.0, 0.001);
    cr_assert_float_eq(result.getZ(), 1.0, 0.001);
}

Test(Rot3D, inverseRotate_partial_rotation) {
    Math::Rot3D rot(90.0, 0.0, 0.0);
    Math::Vector3D vec(0.0, 0.0, 1.0);
    Math::Vector3D result = rot.inverseRotate(vec);
}

Test(Rot3D, assignment_operator) {
    Math::Rot3D rot1(30.0, 60.0, 45.0);
    Math::Rot3D rot2;
    rot2 = rot1;
    cr_assert_eq(rot2.getX(), 30.0);
    cr_assert_eq(rot2.getY(), 45.0);
    cr_assert_eq(rot2.getZ(), 60.0);
}

Test(Rot3D, copy_constructor) {
    Math::Rot3D rot1(30.0, 60.0, 45.0);
    Math::Rot3D rot2(rot1);
    cr_assert_eq(rot2.getX(), 30.0);
    cr_assert_eq(rot2.getY(), 45.0);
    cr_assert_eq(rot2.getZ(), 60.0);
}

Test(Rot3D, operator_plus_equal) {
    Math::Rot3D rot1(30.0, 60.0, 45.0);
    Math::Rot3D rot2(10.0, 20.0, 30.0);
    rot1 += rot2;
    cr_assert_eq(rot1.getX(), 40.0);
    cr_assert_eq(rot1.getY(), 75.0);
    cr_assert_eq(rot1.getZ(), 80.0);
}

Test(Rot3D, operator_minus_equal) {
    Math::Rot3D rot1(30.0, 60.0, 45.0);
    Math::Rot3D rot2(10.0, 20.0, 30.0);
    rot1 -= rot2;
    cr_assert_eq(rot1.getX(), 20.0);
    cr_assert_eq(rot1.getY(), 15.0);
    cr_assert_eq(rot1.getZ(), 40.0);
}

Test(Rot3D, operaotr_plus_equal) {
    Math::Rot3D rot1(30.0, 60.0, 45.0);
    Math::Rot3D rot2(10.0, 20.0, 30.0);
    rot1 += rot2;
}

Test(Rot3D, operaotr_minus_equal) {
    Math::Rot3D rot1(30.0, 60.0, 45.0);
    Math::Rot3D rot2(10.0, 20.0, 30.0);
    rot1 -= rot2;
}

Test(Rot3D, inverseRotate_Z_Axis_Rotation) {
    Math::Rot3D rot(0.0, 90.0, 0.0);
    Math::Vector3D input(1.0, 0.0, 0.0);
    Math::Vector3D result = rot.inverseRotate(input);

}

Test(Rot3D, inverseRotate_Y_Axis_Rotation) {
    Math::Rot3D rot(0.0, 0.0, 90.0);
    Math::Vector3D input(0.0, 0.0, 1.0);
    Math::Vector3D result = rot.inverseRotate(input);

    cr_assert_float_eq(result.getX(), 1.0, 1e-6);
    cr_assert_float_eq(result.getY(), 0.0, 1e-6);
    cr_assert_float_eq(result.getZ(), 0.0, 1e-6);
}

Test(Rot3D, rotate_XY_Axis_Rotation) {
    Math::Rot3D rot(90.0, 0.0, 90.0);
    Math::Vector3D input(1.0, 0.0, 0.0);
    Math::Vector3D result = rot.rotate(input);

    cr_assert_float_eq(result.getX(), 0.0, 1e-6);
    cr_assert_float_eq(result.getY(), 0.0, 1e-6);
    cr_assert_float_eq(result.getZ(), -1.0, 1e-6);
}
