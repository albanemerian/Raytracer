/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** PrimitiveFactory
*/

#include "PrimitiveFactory.hpp"
#include <filesystem>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include "../../common/material/flatColorMat.hpp"
#include "../../common/material/transparencyMat.hpp"
#include "../../common/material/chessboardMat.hpp"
#include "../../common/material/fileTextureMat.hpp"
#include "../../common/material/perlingNoiseMat.hpp"

PrimitiveFactory::PrimitiveFactory() {
    loadAllPlugins();
    _materialList = [] {
        std::map<std::string, std::shared_ptr<IMaterial>> materials;
        materials["flatColorMat"] = std::make_shared<FlatColorMat>();
        materials["transparencyMat"] = std::make_shared<TransparencyMat>();
        materials["chessboardMat"] = std::make_shared<ChessboardMat>();
        materials["fileTextureMat"] = std::make_shared<FileTextureMat>();
        materials["perlingNoiseMat"] = std::make_shared<PerlingNoiseMat>();
        return materials;
    }();
}

PrimitiveFactory::~PrimitiveFactory() {
}

void PrimitiveFactory::setTexturePathIfNeeded(
    std::shared_ptr<IPrimitives> primitive,
    std::shared_ptr<std::map<ValueType_t, ValueType>> config) {

    if (!primitive->getMaterial())
        return;
    if (primitive->getMaterial()->getMaterialType() ==
        MaterialType::FILE_TEXTURE_MAT) {
        if (config->find(ValueType_t::PATH) != config->end()) {
            std::string path = std::get<std::string>
                ((*config)[ValueType_t::PATH]);
            primitive->getMaterial()->setColorTexture(
                std::make_shared<std::string>(path));
        }
    }
}

std::shared_ptr<IPrimitives> PrimitiveFactory::create(
    const std::string& type,
    std::shared_ptr<std::map<ValueType_t, ValueType>> config,
    const std::vector<std::shared_ptr<std::map<ValueType_t,
    ValueType>>>& graphSceneList, std::vector<std::shared_ptr<IPrimitives>>
    primitivesList) {
    (void)primitivesList;
    return createSimple(type, config, graphSceneList);
}

std::shared_ptr<IPrimitives> PrimitiveFactory::createSimple(
    const std::string& type,
    std::shared_ptr<std::map<ValueType_t, ValueType>> config,
    const std::vector<std::shared_ptr<std::map<ValueType_t,
    ValueType>>>& graphSceneList) {
    auto it = _creators.find(type);
    if (it != _creators.end()) {
        auto primitive = it->second(config, graphSceneList);
        setTexturePathIfNeeded(primitive, config);
        return primitive;
    } else {
        std::cerr << "Primitive type not found: " << type << std::endl;
        return nullptr;
    }
}

void PrimitiveFactory::registerCreatorLight(const std::string& type,
        std::function<std::shared_ptr<IPrimitives>(
        std::shared_ptr<std::map<ValueType_t, ValueType>>,
        const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>&,
        std::vector<std::shared_ptr<IPrimitives>> primitivesList)> creator) {
        _creators[type] = [creator, this]
        (std::shared_ptr<std::map<ValueType_t, ValueType>> config,
         const std::vector<std::shared_ptr<std::map<ValueType_t,
         ValueType>>>& graphSceneList) {
        auto primitive = creator(config, graphSceneList, {});

        if (config->find(ValueType_t::MATERIAL) != config->end()) {
            std::string materialName = std::get<std::string>
                ((*config)[ValueType_t::MATERIAL]);
            auto materialIt = _materialList.find(materialName);
            if (materialIt != _materialList.end()) {
                primitive->setMaterial(createMaterialByType
                    (materialIt->second->getMaterialType()));
            } else {
                std::cerr << "Material not found: " << materialName
                    << std::endl;
            }
        }
        return primitive;
    };
}

void PrimitiveFactory::registerCreator(const std::string& type,
        std::function<std::shared_ptr<IPrimitives>(
        std::shared_ptr<std::map<ValueType_t, ValueType>>,
        const std::vector<std::shared_ptr<std::map<ValueType_t,
        ValueType>>>&)> creator) {
    _creators[type] = [creator](auto config, auto graphSceneList) {
        return creator(config, graphSceneList);
    };
}

bool PrimitiveFactory::loadPlugin(const std::string& path) {
    try {
        DLLoader<void*> loader;
        loader.Open(path.c_str(), RTLD_LAZY);
        ObjectType type = getTypeFromPlugin(path, loader);

        if (type == TYPE_PRIMITIVE) {
            std::string name = getNameFromPlugin(path, loader);
            _dlLoaders.push_back(loader);

            using CreateFunc = std::shared_ptr<IPrimitives>(*)(
                std::shared_ptr<std::map<ValueType_t, ValueType>>,
                const std::vector<std::shared_ptr<std::map<ValueType_t,
                ValueType>>>&);

            void* createSymbol = loader.Symbol("createPrimitive");
            if (!createSymbol) {
                throw FactoryException("Failed to from plugin: " + path);
            }

            CreateFunc createFunc = reinterpret_cast<CreateFunc>(createSymbol);
            registerCreator(name, [createFunc](auto config,
                auto graphSceneList) {
                return createFunc(config, graphSceneList);
            });
            return true;
        } else {
            loader.Close();
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "Failed to load plugin in Primitives Factory: "
            << path << ": " << e.what() << std::endl;
        return false;
    }
}
ObjectType PrimitiveFactory::getTypeFromPlugin
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

std::string PrimitiveFactory::getNameFromPlugin
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

void PrimitiveFactory::loadAllPlugins(const std::string& directory) {
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        std::string path = entry.path().string();
        if (entry.is_regular_file() && path.size() > 3 &&
            path.substr(path.size() - 3) == ".so") {
            loadPlugin(path);
        }
    }
}

std::shared_ptr<IMaterial>
PrimitiveFactory::createMaterialByType(MaterialType matType) {
    switch (matType) {
        case MaterialType::FLAT_COLOR:
            return std::make_shared<FlatColorMat>();
        case MaterialType::TRANSPARENCY_MAT:
            return std::make_shared<TransparencyMat>();
        case MaterialType::CHESSBOARD:
            return std::make_shared<ChessboardMat>();
        case MaterialType::FILE_TEXTURE_MAT:
            return std::make_shared<FileTextureMat>();
        case MaterialType::PERLING_NOISE_MAT:
            return std::make_shared<PerlingNoiseMat>();
        default:
            std::cerr << "Unknown material type, defaulting to flat color"
                << std::endl;
            return std::make_shared<FlatColorMat>();
    }
}

std::shared_ptr<IMaterial> PrimitiveFactory::createMaterial
    (const std::string& materialName) {
    auto materialIt = _materialList.find(materialName);
    if (materialIt != _materialList.end()) {
        return createMaterialByType(materialIt->second->getMaterialType());
    }
    std::cerr << "Material not found: " << materialName << std::endl;
    return nullptr;
}
