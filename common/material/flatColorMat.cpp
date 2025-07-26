/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** flatColorMat
*/

#include "flatColorMat.hpp"

FlatColorMat::FlatColorMat() {
    setMaterialType(MaterialType::FLAT_COLOR);
}

Color FlatColorMat::applyMaterial(const PixelInfo& pixelInfo,
    float radius, float height, const IPrimitives &primitive) const {
    (void)primitive;
    (void)radius;
    (void)height;
    Color result = pixelInfo._color;
    return result;
}
