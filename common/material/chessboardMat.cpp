/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** chessboardMat
*/

#include "chessboardMat.hpp"
#include <cmath>
#include "../IPrimitives.hpp"
#include "../PixelInfo.hpp"

ChessboardMat::ChessboardMat() {
    setMaterialType(MaterialType::CHESSBOARD);
    setOptionalColor1(Color(255, 255, 255));
    setOptionalColor2(Color(0, 0, 0));
    setScale(2.0f);
}

Color ChessboardMat::applyMaterial
    (const PixelInfo& pixelInfo, float radius,
    float height, const IPrimitives &primitive) const {
    switch (primitive.getType()) {
        case Type::SPHERE:
            return applySphereChessboard
                (pixelInfo, radius, height, primitive);
        case Type::PLANE:
            return applyPlaneChessboard
                (pixelInfo, radius, height, primitive);
        case Type::CYLINDER:
            return applyCylinderChessboard
                (pixelInfo, radius, height, primitive);
        case Type::CONE:
            return applyConeChessboard
                (pixelInfo, radius, height, primitive);
        default:
            return Color(0, 0, 0);
    }
}

Color ChessboardMat::applySphereChessboard
    (const PixelInfo& pixelInfo, float radius,
    float height, const IPrimitives &primitive) const {
    (void)height;
    Math::Vector3D localPos = primitive.getRotation().inverseRotate
        (pixelInfo._pos - primitive.getPosition());
    float u = 0.0f;
    float v = 0.0f;

    float longitude = std::atan2(localPos.getZ(), localPos.getX());
    float normalizedLongitude = longitude / (M_PI * 2) + 0.5f;
    float latitude = std::acos(localPos.getY() / radius);
    float normalizedLatitude = latitude / M_PI;
    u = normalizedLongitude * 16.0f;
    v = normalizedLatitude * 8.0f;
    float materialScale = getScale();
    if (materialScale <= 0.0f)
        materialScale = 1.0f;
    float adjustedScale = materialScale * 0.5f;
    int ix = static_cast<int>(std::floor(u / adjustedScale));
    int iy = static_cast<int>(std::floor(v / adjustedScale));
    bool isFirstColor = ((ix + iy) % 2 == 0);
    return isFirstColor ? getOptionalColor1() : getOptionalColor2();
}

Color ChessboardMat::applyPlaneChessboard
    (const PixelInfo& pixelInfo, float radius,
    float height, const IPrimitives &primitive) const {
    (void)radius;
    (void)height;
    Math::Vector3D localPos = primitive.getRotation().inverseRotate
        (pixelInfo._pos - primitive.getPosition());
    float u = 0.0f;
    float v = 0.0f;
    Math::Vector3D normal = pixelInfo._normalizedVector;
    Math::Vector3D absNormal(std::abs(normal.getX()),
                            std::abs(normal.getY()),
                            std::abs(normal.getZ()));
    if (absNormal.getX() >= absNormal.getY() &&
        absNormal.getX() >= absNormal.getZ()) {
        u = localPos.getZ();
        v = localPos.getY();
    } else if (absNormal.getY() >= absNormal.getX() &&
                absNormal.getY() >= absNormal.getZ()) {
        u = localPos.getX();
        v = localPos.getZ();
    } else {
        u = localPos.getX();
        v = localPos.getY();
    }
    float materialScale = getScale();
    if (materialScale <= 0.0f)
        materialScale = 1.0f;
    float adjustedScale = materialScale * 0.5f;
    int ix = static_cast<int>(std::floor(u / adjustedScale));
    int iy = static_cast<int>(std::floor(v / adjustedScale));
    bool isFirstColor = ((ix + iy) % 2 == 0);
    return isFirstColor ? getOptionalColor1() : getOptionalColor2();
}

Color ChessboardMat::applyCylinderChessboard
    (const PixelInfo& pixelInfo, float radius,
    float height, const IPrimitives &primitive) const {
    (void)radius;
    Math::Vector3D localPos = primitive.getRotation().inverseRotate
        (pixelInfo._pos - primitive.getPosition());
    float u = 0.0f;
    float v = 0.0f;
    float angle = std::atan2(localPos.getX(), localPos.getZ());
    float normalizedAngle = angle / (M_PI * 2) + 0.5f;
    u = normalizedAngle * 16.0f;
    float normalizedHeight = localPos.getY() / height;
    v = normalizedHeight * 16.0f;
    float materialScale = getScale();
    if (materialScale <= 0.0f)
        materialScale = 1.0f;
    float adjustedScale = materialScale * 0.5f;
    int ix = static_cast<int>(std::floor(u / adjustedScale));
    int iy = static_cast<int>(std::floor(v / adjustedScale));
    bool isFirstColor = ((ix + iy) % 2 == 0);
    return isFirstColor ? getOptionalColor1() : getOptionalColor2();
}

Color ChessboardMat::applyConeChessboard
    (const PixelInfo& pixelInfo, float radius,
    float height, const IPrimitives &primitive) const {
    Math::Vector3D localPos = primitive.getRotation().inverseRotate
        (pixelInfo._pos - primitive.getPosition());
    float angle = std::atan2(localPos.getX(), localPos.getZ());
    float normalizedAngle = angle / (M_PI * 2) + 0.5f;
    float normalizedHeight = localPos.getY() / height;
    float radiusAtHeight = radius * (1.0f - normalizedHeight);
    float circumference = 2.0f * M_PI * radiusAtHeight;
    float u = normalizedAngle * circumference;
    float v = normalizedHeight * height;
    float materialScale = getScale();
    if (materialScale <= 0.0f)
        materialScale = 1.0f;
    float adjustedScale = materialScale * 0.5f;
    int ix = static_cast<int>(std::floor(u / adjustedScale));
    int iy = static_cast<int>(std::floor(v / adjustedScale));
    bool isFirstColor = ((ix + iy) % 2 == 0);
    return isFirstColor ? getOptionalColor1() : getOptionalColor2();
}
