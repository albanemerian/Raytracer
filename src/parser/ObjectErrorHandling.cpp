/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** ObjectErrorHandling
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <memory>
#include "ObjectErrorHandling.hpp"
#include "../../common/Exception/FileException.hpp"

ObjectErrorHandling::ObjectErrorHandling() {
}

ObjectErrorHandling::~ObjectErrorHandling() {
}

std::shared_ptr<const ShapeDefinition> ObjectErrorHandling::getShapeDefinition
(const std::string& objectName) const {
    for (const auto& def : _shapeDefinitions) {
        if (def.name == objectName) {
            return std::make_shared<ShapeDefinition>(def);
        }
    }
    throw FileException("Shape definition not found for: " + objectName);
}

bool ObjectErrorHandling::isParameterMandatory
(const std::string& parameter, const std::string& objectName) const {
    auto def = getShapeDefinition(objectName);

    return std::find(def->mandatory.begin(), def->mandatory.end(), parameter)
           != def->mandatory.end();
}

bool ObjectErrorHandling::isParameterOptional
(const std::string& parameter, const std::string& objectName) const {
    auto def = getShapeDefinition(objectName);

    return std::find(def->optional.begin(), def->optional.end(), parameter)
           != def->optional.end();
}

bool ObjectErrorHandling::isParameterValid
(const std::string& parameter, const std::string& objectName) const {
    return isParameterMandatory(parameter, objectName) ||
           isParameterOptional(parameter, objectName);
}


bool ObjectErrorHandling::checkSimpleValueValidity
(const ConfigNode& node, const std::string &parameter,
const PropertyConfig& config) const {
    if (!node.isValue && node.type != TypeValue)
        throw FileException("Invalid parameter type for " + parameter);
    if (!isValueTypeValid(node.value, config.dataType))
        throw FileException("Invalid value type for parameter " + parameter +
            ". Expected: " + getDataTypeName(config.dataType));
    return true;
}

bool ObjectErrorHandling::checkVector2DValueValidity
(const ConfigNode& node, const std::string &parameter,
const PropertyConfig& config) const {
    if (node.type != TypeGroup)
        throw FileException("Parameter " + parameter +
            " should be a Vector2D");
    for (const auto& comp : config.components) {
        if (!node.hasChild(comp))
            throw FileException("Vector2D parameter " + parameter +
                " is missing component " + comp);
        if (!node.children.at(comp).isValue)
            throw FileException("Vector2D component " + comp +
                " should be a value");
        if (!isValueTypeValid(node.children.at(comp).value, config.dataType))
            throw FileException("Vector2D component " + comp +
                " has invalid data type. Expected: " +
                getDataTypeName(config.dataType));
    }
    return true;
}

bool ObjectErrorHandling::checkVector3DValueValidity
(const ConfigNode& node, const std::string &parameter,
const PropertyConfig& config) const {
    if (node.type != TypeGroup)
        throw FileException
            ("Parameter " + parameter + " should be a Vector3D");
    for (const auto& comp : config.components) {
        if (!node.hasChild(comp))
            throw FileException("Vector3D parameter " + parameter +
                " is missing component " + comp);
        if (!node.children.at(comp).isValue)
            throw FileException("Vector3D component " +
                comp + " should be a value");
        if (!isValueTypeValid(node.children.at(comp).value, config.dataType))
            throw FileException("Vector3D component " + comp +
                " has invalid data type. Expected: "
                + getDataTypeName(config.dataType));
    }
    return true;
}

bool ObjectErrorHandling::checkParameterType
(const std::string& parameter, const ConfigNode& node) const {
    auto it = _propertyTypeMap.find(parameter);

    if (it == _propertyTypeMap.end())
        return false;
    const PropertyConfig& config = it->second;

    switch (config.format) {
        case FORMAT_SIMPLE:
            return checkSimpleValueValidity(node, parameter, config);
        case FORMAT_VECTOR2D:
            return checkVector2DValueValidity(node, parameter, config);
        case FORMAT_VECTOR3D:
            return checkVector3DValueValidity(node, parameter, config);
        default:
            throw FileException
            ("Unknown format type for parameter: " + parameter);
    }
}

bool ObjectErrorHandling::checkArrayValidity
(const ConfigNode& node, const std::string& objectName) {
    if (node.type != TypeArray) {
        return false;
    }
    for (const auto& child : node.children) {
        if (!verifyObjectValidity(child.second, objectName)) {
            std::cout << "Invalid array element for " << objectName
            << std::endl;
            return false;
        }
    }
    return true;
}

bool ObjectErrorHandling::checkMandatoryParameters
(const ConfigNode& node, const std::string& objectName) const {
    auto def = getShapeDefinition(objectName);

    for (const auto& param : def->mandatory) {
        if (!node.hasChild(param))
            throw FileException("Missing mandatory parameter: " + param);
        if (!checkParameterType(param, node.children.at(param)))
            throw FileException
            ("Invalid parameter type for mandatory parameter: " + param);
    }
    return true;
}

bool ObjectErrorHandling::checkOptionalParameters
(const ConfigNode& node, const std::string& objectName) const {
    auto def = getShapeDefinition(objectName);

    for (const auto& param : def->optional) {
        if (node.hasChild(param)) {
            if (!checkParameterType(param, node.children.at(param))) {
                std::cerr << "Invalid parameter type for optional parameter: "
                << param << std::endl;
                return false;
            }
        }
    }
    return true;
}

bool ObjectErrorHandling::checkUnknownParameters
(const ConfigNode& node, const std::string& objectName) const {
    auto def = getShapeDefinition(objectName);

    for (const auto& child : node.children) {
        if (!isParameterValid(child.first, objectName)) {
            std::cerr << "Unknown parameter: " << child.first << std::endl;
            return false;
        }
    }
    return true;
}

bool ObjectErrorHandling::checkGroupValidity
(const ConfigNode& node, const std::string& objectName) {
    if (node.type != TypeGroup)
        return false;
    if (!checkMandatoryParameters(node, objectName) ||
        !checkOptionalParameters(node, objectName) ||
        !checkUnknownParameters(node, objectName))
        return false;
    return true;
}

bool ObjectErrorHandling::checkListValidity
(const ConfigNode& node, const std::string& objectName) {
    if (node.type != TypeList)
        throw FileException("Invalid list type for " + objectName);
    for (const auto& child : node.children) {
        if (!verifyObjectValidity(child.second, objectName))
            throw FileException("Invalid list element for " + objectName);
    }
    return true;
}

bool ObjectErrorHandling::checkValueValidity
(const ConfigNode& node, const std::string& objectName) {
    (void)objectName;
    if (node.type == TypeValue)
        return true;
    throw FileException("Invalid value type for " + objectName);
}

bool ObjectErrorHandling::verifyObjectValidity
(const ConfigNode& node, const std::string& objectName) {
    if (node.type == TypeArray) {
        return checkArrayValidity(node, objectName);
    } else if (node.type == TypeGroup) {
        return checkGroupValidity(node, objectName);
    } else if (node.type == TypeList) {
        return checkListValidity(node, objectName);
    } else if (node.type == TypeValue) {
        return checkValueValidity(node, objectName);
    }
    return false;
}

void ObjectErrorHandling::setShapeDefinitions
(std::vector<ShapeDefinition> shapeDefinitions) {
    _shapeDefinitions = shapeDefinitions;
}

void ObjectErrorHandling::setPropertyTypeMap
(const std::map<std::string, PropertyConfig>& propertyTypeMap) {
    _propertyTypeMap = propertyTypeMap;
}

bool ObjectErrorHandling::isValueTypeValid(const ValueType& value,
ValueDataType expectedType) const {
    switch (expectedType) {
        case TYPE_FLOAT:
            return std::holds_alternative<float>(value) ||
                    std::holds_alternative<double>(value) ||
                    std::holds_alternative<int>(value);
        case TYPE_INT:
            return std::holds_alternative<int>(value);
        case TYPE_STRING:
            return std::holds_alternative<std::string>(value);
        default:
            return true;
    }
}

std::string ObjectErrorHandling::getDataTypeName(ValueDataType type) const {
    // pour plus de precision sur les exeptions
    switch (type) {
        case TYPE_FLOAT:
            return "float";
        case TYPE_INT:
            return "int";
        case TYPE_STRING:
            return "string";
        default:
            return "unknown";
    }
}
