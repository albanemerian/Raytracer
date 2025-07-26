/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** ObjectConstructor
*/

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include "ObjectConstructor.hpp"
#include "ValueConverter.hpp"

ObjectConstructor::ObjectConstructor() : _errorHandler(), _propertyTypeMap{
        {"name", {NAME, FORMAT_SIMPLE, {}, TYPE_STRING}},
        {"position", {POSITION, FORMAT_VECTOR3D, {"x", "y", "z"}, TYPE_FLOAT}},
        {"rotation", {ROTATION, FORMAT_VECTOR3D, {"x", "y", "z"}, TYPE_FLOAT}},
        {"scale", {SCALE, FORMAT_SIMPLE, {}, TYPE_FLOAT}},
        {"scales", {SCALES, FORMAT_VECTOR3D, {"x", "y", "z"}, TYPE_FLOAT}},
        {"color", {COLOR, FORMAT_VECTOR3D, {"r", "g", "b"}, TYPE_FLOAT}},
        {"radius", {RADIUS, FORMAT_SIMPLE, {}, TYPE_FLOAT}},
        {"fieldOfView", {FIELD_OF_VIEW, FORMAT_SIMPLE, {}, TYPE_FLOAT}},
        {"resolution", {RESOLUTION, FORMAT_VECTOR2D,
            {"width", "height"}, TYPE_FLOAT}},
        {"width", {SCALE, FORMAT_SIMPLE, {}, TYPE_FLOAT}},
        {"height", {HEIGHT, FORMAT_SIMPLE, {}, TYPE_FLOAT}},
        {"axis", {AXIS, FORMAT_SIMPLE, {}, TYPE_STRING}},
        {"material", {MATERIAL, FORMAT_SIMPLE, {}, TYPE_STRING}},
        {"path", {PATH, FORMAT_SIMPLE, {}, TYPE_STRING}},
        {"major_radius", {MAJOR_RADIUS, FORMAT_SIMPLE, {}, TYPE_FLOAT}},
        {"minor_radius", {MINOR_RADIUS, FORMAT_SIMPLE, {}, TYPE_FLOAT}},
        /* Light Parameters */
        {"direction", {DIRECTION, FORMAT_VECTOR3D,
            {"x", "y", "z"}, TYPE_FLOAT}},
        {"intensity", {INTENSITY, FORMAT_SIMPLE, {}, TYPE_FLOAT}},
        {"shininess", {SHININESS, FORMAT_SIMPLE, {}, TYPE_FLOAT}},
        {"anti_aliasing", {ANTI_ALIASING, FORMAT_SIMPLE, {}, TYPE_FLOAT}},

        /* Rest of the primitves */
        {"graph", {GRAPH, FORMAT_SIMPLE, {}, TYPE_STRING}},
        {"angle", {ANGLE, FORMAT_SIMPLE, {}, TYPE_FLOAT}},
        // valeurs a rajouter si besoin
    }
    {
    initShapeDefinitions();
    _errorHandler.setPropertyTypeMap(_propertyTypeMap);
    _errorHandler.setShapeDefinitions(_shapeDefinitions);
}

void ObjectConstructor::initShapeDefinitions() {
    _shapeDefinitions = {
        {"camera", {"resolution", "position", "fieldOfView"},
        {"rotation", "anti_aliasing"}, TYPE_CAMERA},
        {"lights", {}, {}, TYPE_UNDEFINED},
        {"primitives", {}, {}, TYPE_UNDEFINED},
        {"graphList", {"graph"}, {}, TYPE_UNDEFINED},
        {"graph", {"name"}, {"position", "rotation", "scale", "scales",
            "color"}, TYPE_GRAPH},
        {"importScenes", {"pathsToFiles"}, {}, TYPE_UNDEFINED},

        /* Light Element */
        {"ambient", {"intensity"}, {}, TYPE_LIGHT},
        {"directional", {"direction", "color", "radius", "intensity"},
            {}, TYPE_LIGHT},
        {"phong", {"direction", "color", "radius", "intensity", "shininess"},
            {}, TYPE_LIGHT},

        /* Primitives */
        {"planes", {"position", "axis", "color"}, {"material", "rotation",
            "scale", "scales", "graph", "path"},
            TYPE_PRIMITIVE},
        {"spheres", {"position", "radius", "color"},
            {"material", "rotation", "scale", "scales", "graph", "path"},
            TYPE_PRIMITIVE},
        {"cones", {"position", "radius", "height", "color"},
            {"material", "rotation", "scale", "scales", "graph", "path"},
            TYPE_PRIMITIVE},
        {"cylinders", {"position", "radius", "height", "color"},
            {"material", "rotation", "scale", "scales", "graph", "path"},
            TYPE_PRIMITIVE},
        {"infinite-cones", {"position", "radius", "angle", "color"},
            {"material", "rotation", "scale", "scales", "graph", "path"},
            TYPE_PRIMITIVE},
        {"infinite-cylinders", {"position", "radius", "color"},
            {"material", "rotation", "scale", "scales", "graph", "path"},
            TYPE_PRIMITIVE},
        {"torus", {"position", "major_radius", "minor_radius", "color"},
            {"material", "rotation", "scale", "light", "light_color",
            "directional", "directional_color", "point", "point_color",
            "phong", "phong_color", "scales", "graph", "path"},
            TYPE_PRIMITIVE},
        /* File options */
        {"pathsToFiles", {"path"}, {}, TYPE_IMPORTED_SCENE},
    };
}

ObjectConstructor::~ObjectConstructor() {}

ValueType ObjectConstructor::convertValue(const ValueType &value,
                                      ValueDataType dataType) {
    if (dataType == TYPE_FLOAT) {
        return ValueConverter::getFloatFromVariant(value);
    } else if (dataType == TYPE_STRING &&
        std::holds_alternative<std::string>(value)) {
        return value;
    } else if (dataType == TYPE_INT && std::holds_alternative<int>(value)) {
        return value;
    }
    return value;
}

void ObjectConstructor::
handleSimpleValue(std::shared_ptr<std::map<ValueType_t, ValueType>> object,
                                      const ValueType_t &key,
                                      const ValueType &value,
                                      ValueDataType dataType) {
    (*object)[key] = convertValue(value, dataType);
}

void ObjectConstructor::handleVector2DValue(
    std::shared_ptr<std::map<ValueType_t, ValueType>> object,
    const ValueType_t &key,
    const ConfigNode &node, const std::vector<std::string> &components,
    ValueDataType dataType) {
    ValueType x = 0.0f;
    ValueType y = 0.0f;

    if (node.hasChild(components[0]))
        x = convertValue(node.children.at(components[0]).value, dataType);
    if (node.hasChild(components[1]))
        y = convertValue(node.children.at(components[1]).value, dataType);
    (*object)[key] = ValueConverter::getVector2DFromComponents(x, y);
}

void ObjectConstructor::handleVector3DValue(
    std::shared_ptr<std::map<ValueType_t, ValueType>> object,
    const ValueType_t &key,
    const ConfigNode &node, const std::vector<std::string> &components,
    ValueDataType dataType) {
    ValueType x = 0.0f;
    ValueType y = 0.0f;
    ValueType z = 0.0f;

    if (node.hasChild(components[0]))
        x = convertValue(node.children.at(components[0]).value, dataType);
    if (node.hasChild(components[1]))
        y = convertValue(node.children.at(components[1]).value, dataType);
    if (node.hasChild(components[2]))
        z = convertValue(node.children.at(components[2]).value, dataType);
    (*object)[key] = ValueConverter::getVector3DFromComponents(x, y, z);
}


void ObjectConstructor::fillObject(const ConfigNode &node,
    std::shared_ptr<std::map<ValueType_t, ValueType>> object) {
    for (const auto &child : node.children) {
        auto propIt = _propertyTypeMap.find(child.first);
        if (propIt != _propertyTypeMap.end()) {
            ValueType_t key = propIt->second.type;
            ValueFormat format = propIt->second.format;
            std::vector<std::string> components = propIt->second.components;
            ValueDataType dataType = propIt->second.dataType;
            if (child.second.isValue && format == FORMAT_SIMPLE) {
                handleSimpleValue(object, key, child.second.value, dataType);
            } else if (child.second.type == TypeGroup) {
                if (format == FORMAT_VECTOR2D) {
                    handleVector2DValue(object, key, child.second, components,
                                        dataType);
                } else if (format == FORMAT_VECTOR3D) {
                    handleVector3DValue(object, key, child.second, components,
                                        dataType);
                }
            }
        } else if (child.second.type == TypeGroup ||
                   child.second.type == TypeArray) {
            fillObject(child.second, object);
        }
    }
}

void ObjectConstructor::createObject(const ConfigNode& node) {
    if (!verifyObjectValidity(node, node._name)) {
        return;
    }
    if (node.type == TypeArray) {
        for (const auto &child : node.children) {
            createObject(child.second);
        }
    } else if (node.type == TypeGroup) {
        auto object = std::make_shared<std::map<ValueType_t, ValueType>>();
        for (const auto& shapeDef : _shapeDefinitions) {
            if (shapeDef.name == node._name) {
                (*object)[TYPE] = shapeDef.objectType;
                break;
            }
        }
        fillObject(node, object);
        _objects.push_back(object);
    }
}

bool ObjectConstructor::createMaterials(const ConfigNode &node) {
    if (node._name == "materials") {
        for (const auto &materialPair : node.children) {
            const std::string &materialName = materialPair.first;
            const ConfigNode &materialNode = materialPair.second;
            if (materialNode.type == TypeGroup) {
                auto object =
                std::make_shared<std::map<ValueType_t, ValueType>>();
                (*object)[NAME] = materialName;
                (*object)[TYPE] = TYPE_MATERIAL;
                for (const auto &propPair : materialNode.children) {
                    const std::string &propName = propPair.first;
                    const ConfigNode &propNode = propPair.second;
                    auto propIt = _propertyTypeMap.find(propName);
                    if (propIt != _propertyTypeMap.end()) {
                        ValueType_t key = propIt->second.type;
                        ValueFormat format = propIt->second.format;
                        std::vector<std::string> components =
                            propIt->second.components;
                        ValueDataType dataType = propIt->second.dataType;

                        if (propNode.isValue && format == FORMAT_SIMPLE) {
                            handleSimpleValue
                            (object, key, propNode.value, dataType);
                        } else if (propNode.type == TypeGroup) {
                            if (format == FORMAT_VECTOR2D) {
                                handleVector2DValue
                                (object, key, propNode, components, dataType);
                            } else if (format == FORMAT_VECTOR3D) {
                                handleVector3DValue
                                (object, key, propNode, components, dataType);
                            }
                        }
                    }
                }
                _objects.push_back(object);
            }
        }
        return true;
    }
    return false;
}

void ObjectConstructor::createObjects(const ConfigNode &node) {
    if (createMaterials(node))
        return;
    for (const auto &child : node.children) {
        if (child.second.type == TypeArray || child.second.type == TypeGroup ||
            child.second.type == TypeList) {
            if (!verifyObjectValidity(child.second, child.first)) {
                std::cout << "Invalid object: " << child.first << std::endl;
                continue;
            }
            for (const auto& arrayItem : child.second.children) {
                auto object = std::make_shared
                    <std::map<ValueType_t, ValueType>>();
                (*object)[NAME] = child.first;
                for (const auto& shapeDef : _shapeDefinitions) {
                    if (shapeDef.name == child.first) {
                        (*object)[TYPE] = shapeDef.objectType;
                        break;
                    }
                }
                fillObject(arrayItem.second, object);
                _objects.push_back(object);
            }
        } else if (child.second.type == TypeValue) {
            auto object = std::make_shared<std::map<ValueType_t, ValueType>>();
            (*object)[NAME] = child.first;
            auto propIt = _propertyTypeMap.find(child.first);
            if (propIt != _propertyTypeMap.end()) {
                ValueType_t key = propIt->second.type;
                ValueFormat format = propIt->second.format;
                ValueDataType dataType = propIt->second.dataType;
                for (const auto& shapeDef : _shapeDefinitions) {
                    if (shapeDef.name == child.first) {
                        (*object)[TYPE] = shapeDef.objectType;
                        break;
                    }
                }
                if (child.second.isValue && format == FORMAT_SIMPLE) {
                    handleSimpleValue(object, key, child.second.value,
                                      dataType);
                }
            }
            _objects.push_back(object);
        }
    }
}

const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>
&ObjectConstructor::getObjects()
    const {
    return _objects;
}

bool ObjectConstructor::verifyObjectValidity
    (const ConfigNode& node, const std::string& objectName) {
    if (_errorHandler.verifyObjectValidity(node, objectName)) {
        return true;
    } else {
        std::cout << "Object " << objectName << " is invalid." << std::endl;
    }
    return false;
}


void ObjectConstructor::printObjectMap() const {
    std::cout << "===== DEBUG: Object Map Contents =====" << std::endl;
    std::cout << "Total objects: " << _objects.size() << std::endl;

    for (size_t i = 0; i < _objects.size(); i++) {
        std::cout << "Object #" << i << ":" << std::endl;
        const auto& object = _objects[i];
        if (!object) {
            std::cout << "  [ERROR] Null object pointer." << std::endl;
            continue;
        }

        for (const auto& [key, value] : *object) {
            std::cout << "  ";

            switch (key) {
                case NAME: std::cout << "NAME"; break;
                case POSITION: std::cout << "POSITION"; break;
                case ROTATION: std::cout << "ROTATION"; break;
                case SCALE: std::cout << "SCALE"; break;
                case COLOR: std::cout << "COLOR"; break;
                case RADIUS: std::cout << "RADIUS"; break;
                case FIELD_OF_VIEW: std::cout << "FIELD_OF_VIEW"; break;
                case RESOLUTION: std::cout << "RESOLUTION"; break;
                case AXIS: std::cout << "AXIS"; break;
                case SCALES: std::cout << "SCALES"; break;
                case GRAPH: std::cout << "GRAPH"; break;
                case TYPE: std::cout << "TYPE"; break;
                case MATERIAL: std::cout << "MATERIAL"; break;
                case PATH: std::cout << "PATH"; break;
                case DIRECTION: std::cout << "DIRECTION"; break;
                case INTENSITY: std::cout << "INTENSITY"; break;
                case SHININESS: std::cout << "SHININESS"; break;
                default: std::cout << "UNKNOWN "; break;
            }

            std::cout << " = ";

            if (std::holds_alternative<int>(value)) {
                std::cout << std::get<int>(value);
            } else if (std::holds_alternative<float>(value)) {
                std::cout << std::get<float>(value);
            } else if (std::holds_alternative<double>(value)) {
                std::cout << std::get<double>(value);
            } else if (std::holds_alternative<std::string>(value)) {
                std::cout << "\"" << std::get<std::string>(value) << "\"";
            } else if (std::holds_alternative<bool>(value)) {
                std::cout << (std::get<bool>(value) ? "true" : "false");
            } else if (std::holds_alternative<Math::Vector2D>(value)) {
                const Math::Vector2D& vec = std::get<Math::Vector2D>(value);
                std::cout << "Vector2D(" << vec.getX() << ", " <<
                vec.getY() << ")";
            } else if (std::holds_alternative<Math::Vector3D>(value)) {
                const Math::Vector3D& vec = std::get<Math::Vector3D>(value);
                std::cout << "Vector3D(" << vec.getX() << ", " << vec.getY()
                << ", " << vec.getZ() << ")";
            } else {
                std::cout << "[ERROR] Unknown value type.";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << "====================================" << std::endl;
}


