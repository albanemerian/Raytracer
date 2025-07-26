/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** ValueConverter
*/

#include "ValueConverter.hpp"

#include <stdexcept>
#include <string>

float ValueConverter::getFloatFromVariant(const ValueType &value) {
    if (std::holds_alternative<int>(value))
        return static_cast<float>(std::get<int>(value));
    else if (std::holds_alternative<float>(value))
        return std::get<float>(value);
    else if (std::holds_alternative<double>(value))
        return static_cast<float>(std::get<double>(value));
    return 0.0f;
}

Math::Vector2D ValueConverter::getVector2DFromComponents(const ValueType &x,
                                                   const ValueType &y) {
    return Math::Vector2D(getFloatFromVariant(x), getFloatFromVariant(y));
}

Math::Vector3D ValueConverter::getVector3DFromComponents(const ValueType &x,
                                                   const ValueType &y,
                                                   const ValueType &z) {
    return Math::Vector3D(getFloatFromVariant(x), getFloatFromVariant(y),
                    getFloatFromVariant(z));
}

