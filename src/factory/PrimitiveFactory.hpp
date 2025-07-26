/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** PrimitiveFactory
*/

#ifndef PRIMITIVEFACTORY_HPP_
#define PRIMITIVEFACTORY_HPP_

#include <vector>
#include <memory>
#include <functional>
#include "IFactory.hpp"
#include "../../common/APrimitives.hpp"
#include "../../lib/DLLoader.hpp"
#include "../../common/Exception/FactoryException.hpp"

class PrimitiveFactory : public IFactory<IPrimitives> {
public:
    PrimitiveFactory();
    ~PrimitiveFactory();

    std::shared_ptr<IPrimitives> create(const std::string& type,
        std::shared_ptr<std::map<ValueType_t, ValueType>> config,
        const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>& graphSceneList,
        std::vector<std::shared_ptr<IPrimitives>> primitivesList) override;

    std::shared_ptr<IPrimitives> createSimple(const std::string& type,
        std::shared_ptr<std::map<ValueType_t, ValueType>> config,
        const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>& graphSceneList) override;

    void registerCreatorLight(const std::string& type,
        std::function<std::shared_ptr<IPrimitives>(
            std::shared_ptr<std::map<ValueType_t, ValueType>>,
            const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>&,
            std::vector<std::shared_ptr<IPrimitives>> primitivesList)> creator) override;

    void registerCreator(const std::string& type,
        std::function<std::shared_ptr<IPrimitives>(
            std::shared_ptr<std::map<ValueType_t, ValueType>>,
            const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>&) > creator) override;

    bool loadPlugin(const std::string& path) override;

    void loadAllPlugins(const std::string& directory = "plugins/");
    ObjectType getTypeFromPlugin(const std::string& path, DLLoader<void*> loader);
    std::string getNameFromPlugin(const std::string& path, DLLoader<void*> loader);

    void setTexturePathIfNeeded(
        std::shared_ptr<IPrimitives> primitive,
        std::shared_ptr<std::map<ValueType_t, ValueType>> config);
    
    std::shared_ptr<IMaterial> createMaterial(const std::string& materialName);
    std::shared_ptr<IMaterial> createMaterialByType(MaterialType matType);

private:
    std::map<std::string, std::function<std::shared_ptr<IPrimitives>(
        std::shared_ptr<std::map<ValueType_t, ValueType>>,
        const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>&)
        >> _creators;
    std::vector<DLLoader<void*>> _dlLoaders;
    std::map<std::string, std::shared_ptr<IMaterial>> _materialList;
};

#endif /* !PRIMITIVEFACTORY_HPP_ */
