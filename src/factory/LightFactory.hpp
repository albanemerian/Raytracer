/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** LightFactory
*/

#ifndef LIGHTFACTORY_HPP_
#define LIGHTFACTORY_HPP_

#include <vector>
#include <memory>
#include <functional>
#include "IFactory.hpp"
#include "../../common/ALight.hpp"
#include "../../lib/DLLoader.hpp"
#include "../../common/Exception/FactoryException.hpp"


class LightFactory : public IFactory<ILight> {
    public:
        LightFactory();
        ~LightFactory();

        std::shared_ptr<ILight> create(const std::string& type,
            std::shared_ptr<std::map<ValueType_t, ValueType>> config,
            const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>& graphSceneList,
        std::vector<std::shared_ptr<IPrimitives>> primitivesList) override;

        std::shared_ptr<ILight> createSimple(const std::string& type,
            std::shared_ptr<std::map<ValueType_t, ValueType>> config,
            const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>& graphSceneList) override;

        void registerCreator(const std::string& type,
            std::function<std::shared_ptr<ILight>(
            std::shared_ptr<std::map<ValueType_t, ValueType>>,
            const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>&) > creator) override;

        void registerCreatorLight(const std::string& type,
            std::function<std::shared_ptr<ILight>(
            std::shared_ptr<std::map<ValueType_t, ValueType>>,
            const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>&,
        std::vector<std::shared_ptr<IPrimitives>>)> creator) override;

        bool loadPlugin(const std::string& path) override;
        void loadAllPlugins(const std::string& directory = "plugins/");
        ObjectType getTypeFromPlugin(const std::string& path, DLLoader<void*> loader);
        std::string getNameFromPlugin(const std::string& path, DLLoader<void*> loader);
    protected:
    private:
        std::map<std::string, std::function<std::shared_ptr<ILight>(
        std::shared_ptr<std::map<ValueType_t, ValueType>>,
        const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>&,
        std::vector<std::shared_ptr<IPrimitives>> primitivesList)>> _creators;
        std::vector<DLLoader<void*>> _dlLoaders;
};

#endif /* !LIGHTFACTORY_HPP_ */
