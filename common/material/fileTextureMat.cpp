/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** fileTextureMat
*/

#include "fileTextureMat.hpp"
#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "../IPrimitives.hpp"

FileTextureMat::FileTextureMat() {
    setMaterialType(FILE_TEXTURE_MAT);
}

Color FileTextureMat::applyMaterial(const PixelInfo& pixelInfo, float radius,
    float height, const IPrimitives &primitive) const {
    if (colorTexture == nullptr) {
        return pixelInfo._color;
    }

    std::shared_ptr<float> u = std::make_shared<float>(0.0f);
    std::shared_ptr<float> v = std::make_shared<float>(0.0f);
    calculUVCoordinates(primitive, pixelInfo, radius, height, u, v);
    return getTextureFromFile(pixelInfo, u, v);
}

void FileTextureMat::loadTextureFromFile(const std::string& filePath) {
    if (colorTexture == nullptr) {
        colorTexture = std::make_shared<std::string>(filePath);
    } else {
        *colorTexture = filePath;
    }
}

void FileTextureMat::calculUVCoordinatesSphere
    (const IPrimitives &primitive, const PixelInfo& pixelInfo,
    float radius, std::shared_ptr<float> u, std::shared_ptr<float> v) const {
    Math::Vector3D localPos = primitive.getRotation().inverseRotate
    (pixelInfo._pos - primitive.getPosition());
    float phi = std::atan2(localPos.getZ(), localPos.getX());
    float theta = std::acos(localPos.getY() / radius);
    *u = (phi + M_PI) / (2.0f * M_PI);
    *v = theta / M_PI;
}

void FileTextureMat::calculUVCoordinatesCylinder
    (const IPrimitives &primitive, const PixelInfo& pixelInfo,
    float radius, float height, std::shared_ptr<float> u,
    std::shared_ptr<float> v) const {
    (void)radius;
    Math::Vector3D localPos = primitive.getRotation().inverseRotate
        (pixelInfo._pos - primitive.getPosition());
    float phi = std::atan2(localPos.getZ(), localPos.getX());
    *u = (phi + M_PI) / (2.0f * M_PI);
    *v = (localPos.getY() + height / 2.0f) / height;
}

void FileTextureMat::calculUVCoordinatesCone
    (const IPrimitives &primitive, const PixelInfo& pixelInfo,
    float radius, float height, std::shared_ptr<float> u,
    std::shared_ptr<float> v) const {
    (void)radius;
    Math::Vector3D localPos = primitive.getRotation().inverseRotate
        (pixelInfo._pos - primitive.getPosition());
    float phi = std::atan2(localPos.getZ(), localPos.getX());
    *u = (phi + M_PI) / (2.0f * M_PI);
    *v = (localPos.getY() + height) / height;
}

void FileTextureMat::calculUVCoordinatesPlane(const IPrimitives &primitive,
    const PixelInfo& pixelInfo,
    float radius, float height, std::shared_ptr<float> u,
    std::shared_ptr<float> v) const {
    (void)radius;
    (void)height;
    Math::Vector3D localPos = primitive.getRotation().inverseRotate
        (pixelInfo._pos - primitive.getPosition());
    Math::Vector3D normal = pixelInfo._normalizedVector;
    Math::Vector3D absNormal(std::abs(normal.getX()),
                           std::abs(normal.getY()),
                           std::abs(normal.getZ()));
    if (absNormal.getX() >= absNormal.getY() &&
        absNormal.getX() >= absNormal.getZ()) {
        *u = localPos.getZ();
        *v = localPos.getY();
    } else if (absNormal.getY() >= absNormal.getX() &&
            absNormal.getY() >= absNormal.getZ()) {
        *u = localPos.getX();
        *v = localPos.getZ();
    } else {
        *u = localPos.getX();
        *v = localPos.getY();
    }
    float materialScale = scale;
    if (materialScale <= 0.0f) {
        materialScale = 1.0f;
    }
    *u /= materialScale;
    *v /= materialScale;
    *u = *u - std::floor(*u);
    *v = *v - std::floor(*v);
}

void FileTextureMat::calculUVCoordinates(const IPrimitives &primitive,
    const PixelInfo& pixelInfo,
    float radius, float height, std::shared_ptr<float> u,
    std::shared_ptr<float> v) const {
    Math::Vector3D localPos = primitive.getRotation().inverseRotate
        (pixelInfo._pos - primitive.getPosition());
    auto type = primitive.getType();
    if (type == Type::SPHERE) {
        calculUVCoordinatesSphere
            (primitive, pixelInfo, radius, u, v);
    } else if (type == Type::CYLINDER) {
        calculUVCoordinatesCylinder
            (primitive, pixelInfo, radius, height, u, v);
    } else if (type == Type::CONE) {
        calculUVCoordinatesCone
            (primitive, pixelInfo, radius, height, u, v);
    } else if (type == Type::PLANE) {
        calculUVCoordinatesPlane
            (primitive, pixelInfo, radius, height, u, v);
    }
}

Color FileTextureMat::getTextureFromFile
    (const PixelInfo& pixelInfo, std::shared_ptr<float> u,
    std::shared_ptr<float> v) const {
    if (colorTexture == nullptr)
        return pixelInfo._color;
    try {
        std::string texturePath = *colorTexture;
        std::ifstream file(texturePath);
        if (!file.good()) {
            std::cerr << "Erreur lors du chargement de la texture: "
                << texturePath << std::endl;
            return pixelInfo._color;
        }
        file.close();
        static std::map<std::string, sf::Image> textureCache;
        if (textureCache.find(texturePath) == textureCache.end()) {
            sf::Image image;
            if (!image.loadFromFile(texturePath)) {
                std::cerr << "Erreur lors du chargement de la texture SFML: "
                    << texturePath << std::endl;
                return pixelInfo._color;
            }
            textureCache[texturePath] = image;
        }
        const sf::Image& texture = textureCache[texturePath];
        *u = *u - std::floor(*u);
        *v = *v - std::floor(*v);
        unsigned int x = static_cast<unsigned int>
            (*u * texture.getSize().x) % texture.getSize().x;
        unsigned int y = static_cast<unsigned int>
            (*v * texture.getSize().y) % texture.getSize().y;
        sf::Color pixelColor = texture.getPixel(x, y);
        Color result(pixelColor.r, pixelColor.g, pixelColor.b);
        return result;
    } catch (const std::exception& e) {
        std::cerr << "Exception lors du traitement de la texture: "
        << e.what() << std::endl;
        return pixelInfo._color;
    }
}
