/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** PropertyTypes
*/

#ifndef PROPERTYTYPES_HPP_
#define PROPERTYTYPES_HPP_

#include <map>
#include <string>
#include <vector>

#include "../../common/ValueType.hpp"

enum ValueDataType {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_BOOL,
    TYPE_DOUBLE
};

struct PropertyInfo {
    ValueType_t type;
    ValueFormat format;
    std::vector<std::string> components;
    ValueDataType dataType;
};

struct ShapeDefinition {
    std::string name;
    std::vector<std::string> mandatory;
    std::vector<std::string> optional;
    ObjectType objectType;
};

struct PropertyConfig {
    ValueType_t type;
    ValueFormat format;
    std::vector<std::string> components;
    ValueDataType dataType;
};

#endif /* !PROPERTYTYPES_HPP_ */