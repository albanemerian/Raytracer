/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** LightFactory
*/

#include "LightFactory.hpp"
#include <filesystem>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <memory>


LightFactory::LightFactory() {
    loadAllPlugins();
}

LightFactory::~LightFactory() {
}

std::shared_ptr<ILight> LightFactory::createSimple(const std::string& type,
        std::shared_ptr<std::map<ValueType_t, ValueType>> config,
        const std::vector<std::shared_ptr<std::map<ValueType_t,
        ValueType>>>& graphSceneList) {
    auto it = _creators.find(type);
    if (it != _creators.end()) {
        return it->second(config, graphSceneList, {});
    } else {
        std::cerr << "Light type not found: " << type << std::endl;
        return nullptr;
    }
}

std::shared_ptr<ILight> LightFactory::create(const std::string& type,
    std::shared_ptr<std::map<ValueType_t, ValueType>> config,
    const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>&
    graphSceneList, std::vector<std::shared_ptr<IPrimitives>> primitivesList) {
    auto it = _creators.find(type);
    if (it != _creators.end()) {
        return it->second(config, graphSceneList, primitivesList);
    } else {
        std::cerr << "Light type not found: " << type << std::endl;
        return nullptr;
    }
}

void LightFactory::registerCreator(
    const std::string& type,
    std::function<std::shared_ptr<ILight>(
        std::shared_ptr<std::map<ValueType_t, ValueType>>,
        const std::vector<std::shared_ptr<std::map<ValueType_t,
        ValueType>>>&)> creator) {
    (void)creator;
    (void)type;
    std::cerr << "LightFactory: registerCreator." << std::endl;
}

void LightFactory::registerCreatorLight(const std::string& type,
    std::function<std::shared_ptr<ILight>(
        std::shared_ptr<std::map<ValueType_t, ValueType>>,
        const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>&,
        std::vector<std::shared_ptr<IPrimitives>> primitivesList)> creator) {
    _creators[type] = [creator](auto config, auto graphSceneList,
        auto primitivesList) {
        return creator(config, graphSceneList, primitivesList);
    };
}

bool LightFactory::loadPlugin(const std::string& path) {
    try {
        DLLoader<void*> loader;
        if (loader.Open(path.c_str(), RTLD_LAZY) == nullptr) {
            return false;
        }
        ObjectType type = getTypeFromPlugin(path, loader);
        if (type == TYPE_LIGHT) {
            std::string name = getNameFromPlugin(path, loader);
            _dlLoaders.push_back(loader);
            using CreateFunc = std::shared_ptr<ILight>(*)(
                std::shared_ptr<std::map<ValueType_t, ValueType>>,
                std::vector<std::shared_ptr<IPrimitives>> primitivesList);
            void* createSymbol = loader.Symbol("createLight");
            if (!createSymbol) {
                throw FactoryException
                    ("Failed to load create symbol from plugin: " + path);
            }
            std::cout << "loaded function createLight" << std::endl;
            CreateFunc createFunc = reinterpret_cast<CreateFunc>(createSymbol);
            registerCreatorLight(name, [createFunc]
                (std::shared_ptr<std::map<ValueType_t, ValueType>> config,
                 const std::vector<std::shared_ptr<std::map<ValueType_t,
                 ValueType>>>& graphSceneList,
                 std::vector<std::shared_ptr<IPrimitives>> primitivesList) {
                (void)graphSceneList;
                return createFunc(config, primitivesList);
            });
            return true;
        } else {
            loader.Close();
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "Failed to load plugin in Light Factory: "
        << path << ": " << e.what() << std::endl;
        return false;
    }
}

ObjectType LightFactory::getTypeFromPlugin(const std::string& path,
    DLLoader<void*> loader) {
    using GetTypeFunc = ObjectType(*)();
    void* symbolPtr = loader.Symbol("getType");
    if (!symbolPtr) {
        throw FactoryException
            ("Failed to load getType symbol from plugin: " + path);
    }
    GetTypeFunc getTypeFunc = reinterpret_cast<GetTypeFunc>(symbolPtr);
    return getTypeFunc();
}

std::string LightFactory::getNameFromPlugin(const std::string& path,
    DLLoader<void*> loader) {
    using GetNameFunc = std::string(*)();
    void* symbolPtr = loader.Symbol("getName");
    if (!symbolPtr) {
        throw FactoryException
            ("Failed to load getName symbol from plugin: " + path);
    }
    GetNameFunc getNameFunc = reinterpret_cast<GetNameFunc>(symbolPtr);
    std::string name = getNameFunc();
    return name;
}

void LightFactory::loadAllPlugins(const std::string &directory) {
    for (const auto &entry : std::filesystem::directory_iterator(directory)) {
        std::string path = entry.path().string();
        if (entry.is_regular_file() && path.size() > 3 &&
            path.substr(path.size() - 3) == ".so") {
            loadPlugin(path);
        }
    }
}
