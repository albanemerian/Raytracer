/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** ValueType
*/


#include <memory>
#include <string>
#include <variant>

#include "IPrimitives.hpp"
#include "Vector2D.hpp"
#include "Vector3D.hpp"

#ifndef VALUETYPE_HPP_
#define VALUETYPE_HPP_

enum ObjectType {
    TYPE_CAMERA,
    TYPE_LIGHT,
    TYPE_PRIMITIVE,
    TYPE_IMPORTED_SCENE,
    TYPE_GRAPH,
    TYPE_MATERIAL,
    TYPE_UNDEFINED
};

using ValueType = std::variant<int, float, double, std::string, bool, Math::Vector2D, Math::Vector3D, ObjectType>;

enum ValueFormat { FORMAT_SIMPLE, FORMAT_VECTOR2D, FORMAT_VECTOR3D};

typedef enum ValueType_s {
    NAME,
    TYPE,
    POSITION,
    ROTATION,
    SCALE,
    SCALES,
    COLOR,
    COLOR_CHESS_1,
    COLOR_CHESS_2,
    RADIUS,
    FIELD_OF_VIEW,
    RESOLUTION,
    AXIS,
    HEIGHT,
    MATERIAL,
    GRAPH,
    PATH,
    AMBIENT,
    SPECULAR,
    DIFFUSE,
    REFLECTION,
    TRANSPARENCY,
    REFRACTION_INDEX,
    DIRECTION,
    INTENSITY,
    SHININESS,
    MAJOR_RADIUS,
    MINOR_RADIUS,
    ANTI_ALIASING,
    ANGLE
} ValueType_t;



#endif /* !VALUETYPE_HPP_ */
