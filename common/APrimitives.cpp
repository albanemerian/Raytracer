/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** APrimitives
*/
#include <memory>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <utility>
#include "APrimitives.hpp"
#include "material/IMaterial.hpp"
#include "../src/Raytracer.hpp"
#include "Random.hpp"

void APrimitives::getRot(std::shared_ptr<std::map<ValueType_t,
    ValueType>> map) {
    auto it = map->find(ValueType_t::ROTATION);

    if (it != map->end()) {
        auto rotVec = std::get<Math::Vector3D>(it->second);
        _rotation = Math::Rot3D(rotVec.getX(), rotVec.getY(),
        rotVec.getZ());
    } else {
        _rotation = Math::Rot3D(0, 0, 0);
    }
}

void APrimitives::getPos(std::shared_ptr<std::map<ValueType_t,
    ValueType>> map) {
    auto positionVector = std::get<Math::Vector3D>(
        map->find(ValueType_t::POSITION)->second);
    _position = Math::Point3D(positionVector.getX(),
                             positionVector.getY(),
                             positionVector.getZ());
}

void APrimitives::getCol(std::shared_ptr<std::map<ValueType_t,
    ValueType>> map) {
    if (map->find(ValueType_t::COLOR) != map->end()) {
        auto colorVector = std::get<Math::Vector3D>(
            map->find(ValueType_t::COLOR)->second);
        _color = Color();
        _color = Math::Vector3D(colorVector.getX(),
                                colorVector.getY(),
                                colorVector.getZ());
    } else {
        _color = Math::Vector3D(0, 0, 0);
    }
}

void APrimitives::computeInvScales() {
    _invScales = Math::Vector3D(1.0 / _scales);
}

void APrimitives::getScales(std::shared_ptr<std::map<ValueType_t,
    ValueType>> map) {
    auto it = map->find(ValueType_t::SCALE);
    if (it != map->end()) {
        scale = std::get<float>(it->second);
    } else {
        scale = 1;
    }
    it = map->find(ValueType_t::SCALES);
    if (it != map->end()) {
        auto scalesVector = std::get<Math::Vector3D>(it->second);
        _scales = Math::Vector3D(scalesVector.getX(),
                                 scalesVector.getY(),
                                 scalesVector.getZ());
    } else {
        _scales = Math::Vector3D(1, 1, 1);
    }
    computeInvScales();
}

/* Graph Methods */

void APrimitives::getGraphScale(const std::shared_ptr<std::map<ValueType_t,
    ValueType>> &graph) {
    auto it = graph->find(ValueType_t::SCALES);

    if (it != graph->end()) {
        auto scalesVector = std::get<Math::Vector3D>(it->second);
        Math::Vector3D temp = Math::Vector3D(scalesVector.getX(),
                                 scalesVector.getY(),
                                 scalesVector.getZ());
        _scales = Math::Vector3D(_scales.getX() * temp.getX(),
                             _scales.getY() * temp.getY(),
                             _scales.getZ() * temp.getZ());
        computeInvScales();
    }
}

void APrimitives::getPosGraph(const std::shared_ptr<std::map<ValueType_t,
    ValueType>> &graph) {
    auto it = graph->find(ValueType_t::POSITION);
    if (it != graph->end()) {
        auto positionVector = std::get<Math::Vector3D>(it->second);
        Math::Point3D temp = Math::Point3D(positionVector.getX(),
                                 positionVector.getY(),
                                 positionVector.getZ());
        _position = Math::Point3D(_position.getX() + temp.getX(),
                                 _position.getY() + temp.getY(),
                                 _position.getZ() + temp.getZ());
    }
}

void APrimitives::getRotGraph(const std::shared_ptr<std::map<ValueType_t,
    ValueType>> &graph) {
    auto it = graph->find(ValueType_t::ROTATION);
    if (it != graph->end()) {
        auto rotVec = std::get<Math::Vector3D>(it->second);
        Math::Rot3D temp = Math::Rot3D(rotVec.getX(), rotVec.getY(),
                                rotVec.getZ());
        _rotation = Math::Rot3D(_rotation.getX() + temp.getX(),
                                _rotation.getY() + temp.getY(),
                                _rotation.getZ() + temp.getZ());
    }
}

void APrimitives::getGraph(std::shared_ptr<std::map<ValueType_t,
    ValueType>> map, const std::vector<std::shared_ptr<std::map<ValueType_t,
    ValueType>>> &graphSceneList) {
    if (graphSceneList.empty()) {
        return;
    }

    auto it = map->find(ValueType_t::GRAPH);
    if (it != map->end()) {
        _graph = std::get<std::string>(it->second);
    } else {
        _graph = "";
        return;
    }

    for (const auto &graph : graphSceneList) {
        if (graph->find(ValueType_t::NAME) != graph->end()) {
            std::string graphName = std::get<std::string>((*graph)
            [ValueType_t::NAME]);
            if (graphName == _graph) {
                it = graph->find(ValueType_t::SCALE);
                if (it != graph->end()) {
                    float temp = std::get<float>(it->second);
                    scale *= temp;
                }
                getGraphScale(graph);
                getPosGraph(graph);
                getRotGraph(graph);
                it = graph->find(ValueType_t::COLOR);
                if (it != graph->end()) {
                    auto colorVector = std::get<Math::Vector3D>(it->second);
                    _color = Color();
                    _color = Math::Vector3D(colorVector.getX(),
                                            colorVector.getY(),
                                            colorVector.getZ());
                }
            }
        }
    }
}

Math::Ray APrimitives::computeScaledRay(const Math::Ray &ray) const {
    Math::Vector3D scaledOrigin = Math::Vector3D(ray.getOrigin() * _invScales);
    Math::Vector3D scaledDirection = Math::Vector3D(ray.getDirection() *
        _invScales).normalize();
    return Math::Ray(scaledOrigin, scaledDirection);
}

APrimitives::APrimitives(std::shared_ptr<std::map<ValueType_t,
    ValueType>> map, const std::vector<std::shared_ptr<std::map<ValueType_t,
    ValueType>>> &graphSceneList) {
    getPos(map);
    getRot(map);
    getCol(map);
    getScales(map);
    getGraph(map, graphSceneList);
    material = nullptr;
}
