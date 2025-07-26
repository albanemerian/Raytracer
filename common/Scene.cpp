/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Scene
*/

#include <vector>
#include <memory>
#include <iostream>
#include <stdexcept>
#include "Scene.hpp"

Scene::Scene() {
    _camera = std::make_shared<Camera>();
}

Scene::Scene(std::shared_ptr<Camera> camera,
    std::vector<std::shared_ptr<IPrimitives>> primitives)
    : _camera(camera), _primTemp(primitives) {
}

Scene::~Scene() {
}


// Getters
std::shared_ptr<Camera> Scene::getCamera() const {
    return _camera;
}

std::shared_ptr<GraphsNodePrimitive> Scene::getPrimitives() const {
    return _primitives;
}

std::shared_ptr<GraphsNodeLight> Scene::getLights() const {
    return _lights;
}

int Scene::camereaWidth() const {
    return _camera->getWidth();
}

int Scene::camereaHeight() const {
    return _camera->getHeight();
}

int Scene::cameraAntiAliasing() const {
    return _camera->getAntiAliasing();
}

float Scene::getAmbientLight() const {
    return _ambientLight;
}

// Setters
void Scene::setCamera(std::shared_ptr<Camera>camera) {
    _camera->setResolution(camera->getWidth(), camera->getHeight());
    _camera->setPosition(camera->getPosition());
    _camera->setFieldOfView(camera->getFieldOfView());
    _camera->setRotation(camera->getRotation());
    try {
        _camera->setAntiAliasing(camera->getAntiAliasing());
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw;
    }
    _camera = camera;
}

void Scene::setPrimitives(
    const std::vector<std::shared_ptr<IPrimitives>> &primitives) {
    auto root = std::make_shared<GraphsNodePrimitive>();
    root->_primitives = nullptr;

    for (const auto& prim : primitives) {
        auto node = std::make_shared<GraphsNodePrimitive>();
        node->_primitives = prim;
        root->_children.push_back(node);
    }

    this->_primitives = root;
}

void Scene::setLights(
    const std::vector<std::shared_ptr<ILight>> &lights) {
    auto root = std::make_shared<GraphsNodeLight>();
    root->_primitives = nullptr;

    for (const auto& prim : lights) {
        auto node = std::make_shared<GraphsNodeLight>();
        node->_primitives = prim;
        root->_children.push_back(node);
    }

    this->_lights = root;
}

void Scene::setAntiAliasing(int antiAliasing) {
    _camera->setAntiAliasing(antiAliasing);
}
