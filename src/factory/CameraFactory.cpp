/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** CameraFactory
*/

#include "CameraFactory.hpp"
#include <filesystem>
#include <memory>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <stdexcept>

CameraFactory::CameraFactory() {
    loadAllPlugins();
}

CameraFactory::~CameraFactory() {
}

std::shared_ptr<Camera> CameraFactory::createSimple(const std::string& type,
    std::shared_ptr<std::map<ValueType_t, ValueType>> config,
    const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>&
    graphSceneList) {
    if (config == nullptr) {
        std::cerr << "Config is null" << std::endl;
    }
    auto it = _creators.find(type);
    if (it != _creators.end()) {
        return it->second(config, graphSceneList);
    } else {
        auto defaultCamera = std::make_shared<Camera>();
        if (config) {
            if (config->count(RESOLUTION)) {
                auto resolution = std::get<Math::Vector2D>
                ((*config)[RESOLUTION]);
                defaultCamera->setResolution(resolution.getX(),
                resolution.getY());
            }
            if (config->count(POSITION)) {
                auto position = std::get<Math::Vector3D>
                ((*config)[POSITION]);
                defaultCamera->setPosition(position);
            }
            if (config->count(ROTATION)) {
                // handle rotation
            }
            if (config->count(FIELD_OF_VIEW)) {
                auto fov = std::get<float>((*config)[FIELD_OF_VIEW]);
                defaultCamera->setFieldOfView(fov);
            }
            if (config->count(ANTI_ALIASING)) {
                auto aa = static_cast<int>(std::get<float>((*config)
                [ANTI_ALIASING]));
                try {
                    defaultCamera->setAntiAliasing(aa);
                } catch (const std::runtime_error& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                    throw;
                }
            }
            defaultCamera->updateScreen();
        }
        return defaultCamera;
    }
}

std::shared_ptr<Camera> CameraFactory::create(const std::string& type,
    std::shared_ptr<std::map<ValueType_t, ValueType>> config,
    const std::vector<std::shared_ptr<std::map<ValueType_t,
    ValueType>>>& graphSceneList,
    std::vector<std::shared_ptr<IPrimitives>> primitivesList) {
    (void)primitivesList;
    return createSimple(type, config, graphSceneList);
}

void CameraFactory::registerCreator(const std::string& type,
    std::function<std::shared_ptr<Camera>(
        std::shared_ptr<std::map<ValueType_t, ValueType>>,
        const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>&)>
        creator) {
    _creators[type] = creator;
}

void CameraFactory::registerCreatorLight(const std::string& type,
    std::function<std::shared_ptr<Camera>(
        std::shared_ptr<std::map<ValueType_t, ValueType>>,
        const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>&,
        std::vector<std::shared_ptr<IPrimitives>> primitivesList)> creator) {
    _creators[type] = [creator](auto config, auto graphSceneList) {
        return creator(config, graphSceneList, {});
    };
}

bool CameraFactory::loadPlugin(const std::string& path) {
    try {
        DLLoader<void*> loader;
        if (path == "plugins/.gitkeep")
            return false;
        loader.Open(path.c_str(), RTLD_LAZY);
        ObjectType type = getTypeFromPlugin(path, loader);
        if (type == TYPE_CAMERA) {
            std::string name = getNameFromPlugin(path, loader);
            _dlLoaders.push_back(loader);
            using CreateFunc = std::shared_ptr<Camera>(*)
                (std::shared_ptr<std::map<ValueType_t, ValueType>>);
            void* createSymbol = loader.Symbol("createCamera");
            if (!createSymbol) {
                throw FactoryException
                    ("Failed to load create symbol from plugin: " + path);
            }
            CreateFunc createFunc = reinterpret_cast<CreateFunc>(createSymbol);
            registerCreator(name, [createFunc]
                (std::shared_ptr<std::map<ValueType_t, ValueType>> config,
                 const std::vector<std::shared_ptr<std::map<ValueType_t,
                 ValueType>>>& graphSceneList) {
                (void)graphSceneList;
                return createFunc(config);
            });
            return true;
        } else {
            loader.Close();
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "Failed to load plugin in cameraFactory: "
        << path << ": " << e.what() << std::endl;
        return false;
    }
}

ObjectType CameraFactory::getTypeFromPlugin
(const std::string& path, DLLoader<void*> loader) {
    using GetTypeFunc = ObjectType(*)();
    void* symbolPtr = loader.Symbol("getType");
    if (!symbolPtr) {
        throw FactoryException
            ("Failed to load getType symbol from plugin: " + path);
    }
    GetTypeFunc getTypeFunc = reinterpret_cast<GetTypeFunc>(symbolPtr);
    return getTypeFunc();
}

std::string CameraFactory::getNameFromPlugin
(const std::string& path, DLLoader<void*> loader) {
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

void CameraFactory::loadAllPlugins(const std::string& directory) {
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        std::string path = entry.path().string();
        if (entry.is_regular_file() && path.size() > 3 &&
            path.substr(path.size() - 3) == ".so") {
            loadPlugin(path);
        }
    }
}
