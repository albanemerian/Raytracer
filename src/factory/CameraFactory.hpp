/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** PrimitiveFactory
*/

#ifndef CAMERAFACTORY_HPP_
#define CAMERAFACTORY_HPP_

#include <vector>
#include <functional>
#include "IFactory.hpp"
#include "../../lib/DLLoader.hpp"
#include "../../common/Camera.hpp"
#include "../../common/Exception/FactoryException.hpp"

class CameraFactory : public IFactory<Camera> {
public:
    CameraFactory();
    ~CameraFactory();

    std::shared_ptr<Camera> create(const std::string& type,
        std::shared_ptr<std::map<ValueType_t, ValueType>> config,
        const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>& graphSceneList,
        std::vector<std::shared_ptr<IPrimitives>> primitivesList) override;

    std::shared_ptr<Camera> createSimple(const std::string& type,
        std::shared_ptr<std::map<ValueType_t, ValueType>> config,
        const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>& graphSceneList) override;

    void registerCreator(const std::string& type,
        std::function<std::shared_ptr<Camera>(
            std::shared_ptr<std::map<ValueType_t, ValueType>>,
            const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>&)> creator) override;

    void registerCreatorLight(const std::string& type,
        std::function<std::shared_ptr<Camera>(
            std::shared_ptr<std::map<ValueType_t, ValueType>>,
            const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>&,
        std::vector<std::shared_ptr<IPrimitives>> primitivesList)> creator) override;

    bool loadPlugin(const std::string& path) override;
    void loadAllPlugins(const std::string& directory = "plugins/");
    ObjectType getTypeFromPlugin(const std::string& path, DLLoader<void*> loader);
    std::string getNameFromPlugin(const std::string& path, DLLoader<void*> loader);

private:
    std::map<std::string, std::function<std::shared_ptr<Camera>(
        std::shared_ptr<std::map<ValueType_t, ValueType>>,
        const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>&)>> _creators;
    std::vector<DLLoader<void*>> _dlLoaders;
};

#endif /* !CAMERAFACTORY_HPP_ */
