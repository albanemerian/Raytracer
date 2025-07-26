/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** ValueConverter
*/

#ifndef VALUECONVERTER_HPP_
#define VALUECONVERTER_HPP_

#include "../../common/Vector2D.hpp"
#include "../../common/Vector3D.hpp"
#include "PropertyTypes.hpp"

class ValueConverter {
 public:
    static float getFloatFromVariant(const ValueType &value);
    static Math::Vector2D getVector2DFromComponents(const ValueType &x,
                                              const ValueType &y);
    static Math::Vector3D getVector3DFromComponents(const ValueType &x,
                                              const ValueType &y,
                                              const ValueType &z);
};

#endif /* !VALUECONVERTER_HPP_ */