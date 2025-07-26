/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** FactoryManager
*/

#ifndef FACTORYMANAGER_HPP_
#define FACTORYMANAGER_HPP_

#include <memory>
#include "PrimitiveFactory.hpp"
#include "CameraFactory.hpp"
#include "LightFactory.hpp"
#include "../../common/Graphs.hpp"
#include "../../common/Exception/FactoryException.hpp"

class FactoryManager {
public:
    FactoryManager();
    ~FactoryManager() = default;

    std::shared_ptr<PrimitiveFactory> getPrimitiveFactory() { return _primitiveFactory; }
    std::shared_ptr<CameraFactory> getCameraFactory() { return _cameraFactory; }

    void initializeFactories();

    void createObjectsFromConfig(const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>& objectsConfig);

    std::shared_ptr<GraphsNodePrimitive> getPrimitives() const { return _primitives; }
    std::vector<std::shared_ptr<ILight>> getLights() const { return _lights; }
    std::shared_ptr<Camera> getCamera() const { return _camera; }
    float getAmbientLight() const { return _ambientLight; }

private:
    std::shared_ptr<PrimitiveFactory> _primitiveFactory;
    std::shared_ptr<CameraFactory> _cameraFactory;
    std::shared_ptr<LightFactory> _lightsFactory;
    std::shared_ptr<GraphsNodePrimitive> _primitives;
    std::vector<std::shared_ptr<ILight>> _lights;
    std::shared_ptr<Camera> _camera;
    float _ambientLight;
};

#endif /* !FACTORYMANAGER_HPP_ */
