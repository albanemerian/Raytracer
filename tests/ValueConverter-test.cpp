/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** ValueConverter-test
*/
#include <criterion/criterion.h>
#include "../src/parser/ValueConverter.hpp"

Test(ValueConverter, getFloatFromVariant) {
    ValueType intValue = 42;
    ValueType floatValue = 42.5f;
    ValueType doubleValue = 42.5;

    cr_assert_eq(ValueConverter::getFloatFromVariant(intValue), 42.0f, "Failed to convert int to float.");
    cr_assert_eq(ValueConverter::getFloatFromVariant(floatValue), 42.5f, "Failed to convert float to float.");
    cr_assert_eq(ValueConverter::getFloatFromVariant(doubleValue), 42.5f, "Failed to convert double to float.");
}

Test(ValueConverter, getFloatFromVariantUnsupportedType) {
    ValueType unsupportedValue = std::string("unsupported");

    float result = ValueConverter::getFloatFromVariant(unsupportedValue);
    cr_assert_eq(result, 0.0f, "Failed to return 0.0f for unsupported ValueType.");
}

Test(ValueConverter, getVector2DFromComponents) {
    ValueType x = 10;
    ValueType y = 20.5f;

    Math::Vector2D result = ValueConverter::getVector2DFromComponents(x, y);
    cr_assert_eq(result.getX(), 10.0f, "Failed to convert x component to Vector2D.");
    cr_assert_eq(result.getY(), 20.5f, "Failed to convert y component to Vector2D.");
}

Test(ValueConverter, getVector3DFromComponents) {
    ValueType x = 1.0;
    ValueType y = 2.0f;
    ValueType z = 3;

    Math::Vector3D result = ValueConverter::getVector3DFromComponents(x, y, z);
    cr_assert_eq(result.getX(), 1.0f, "Failed to convert x component to Vector3D.");
    cr_assert_eq(result.getY(), 2.0f, "Failed to convert y component to Vector3D.");
    cr_assert_eq(result.getZ(), 3.0f, "Failed to convert z component to Vector3D.");
}

