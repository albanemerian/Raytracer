
/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** FactoryManager
*/

#include <memory>
#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "FactoryManager.hpp"
#include "../parser/PropertyTypes.hpp"

FactoryManager::FactoryManager() {
    initializeFactories();
}

void FactoryManager::initializeFactories() {
    _primitiveFactory = std::make_shared<PrimitiveFactory>();
    _cameraFactory = std::make_shared<CameraFactory>();
    _lightsFactory = std::make_shared<LightFactory>();
    _ambientLight = 0.0f;
}
void FactoryManager::createObjectsFromConfig(
    const std::vector<std::shared_ptr<std::map<ValueType_t,
    ValueType>>>& objectsConfig) {
    std::vector<std::shared_ptr<std::map<ValueType_t,
    ValueType>>> _graphSceneList;
    std::vector<std::shared_ptr<IPrimitives>> primitivesList;

    for (const auto& objectConfig : objectsConfig) {
        if (objectConfig->find(ValueType_t::TYPE) != objectConfig->end()) {
            int type = std::get<ObjectType>((*objectConfig)
                [ValueType_t::TYPE]);
            if (type == TYPE_GRAPH) {
                _graphSceneList.push_back(objectConfig);
            }
        }
    }
    for (const auto& objectConfig : objectsConfig) {
        if (objectConfig->find(ValueType_t::TYPE) != objectConfig->end()) {
            int type = std::get<ObjectType>((*objectConfig)
                [ValueType_t::TYPE]);
            std::string name = "default";

            if (objectConfig->find(ValueType_t::NAME) != objectConfig->end())
                name = std::get<std::string>((*objectConfig)
                [ValueType_t::NAME]);

            if (type == TYPE_PRIMITIVE) {
                primitivesList.push_back(
                    _primitiveFactory->createSimple(name, objectConfig,
                        _graphSceneList));
            } else if (type == TYPE_GRAPH) {
                continue;
            } else if (type == TYPE_LIGHT) {
                continue;
            } else if (type == TYPE_CAMERA) {
                _camera = _cameraFactory->createSimple(name, objectConfig,
                    _graphSceneList);
            } else if (type == TYPE_IMPORTED_SCENE) {
                continue;
            } else {
                std::cerr << "Object name: " << name << std::endl;
            }
        } else {
            std::cerr << "Object type not found in config." << std::endl;
        }
    }
    for (const auto &objectConfig : objectsConfig) {
        if (objectConfig->find(ValueType_t::TYPE) != objectConfig->end()) {
            int type = std::get<ObjectType>((*objectConfig)
                [ValueType_t::TYPE]);
            std::string name = "default";

            if (objectConfig->find(ValueType_t::NAME) != objectConfig->end())
                name = std::get<std::string>((*objectConfig)
                [ValueType_t::NAME]);
            if (type == TYPE_LIGHT) {
                _lights.push_back(
                    _lightsFactory->create(name, objectConfig,
                        _graphSceneList, primitivesList));
            }
            if (name == "ambient") {
                _ambientLight = std::get<float>((*objectConfig)
                    [ValueType_t::INTENSITY]);
            }
        }
    }
    // After collecting all primitives, build the graph
    auto root = std::make_shared<GraphsNodePrimitive>();
    root->_primitives = nullptr;
    for (const auto& prim : primitivesList) {
        auto node = std::make_shared<GraphsNodePrimitive>();
        node->_primitives = prim;
        root->_children.push_back(node);
    }
    _primitives = root;
}
