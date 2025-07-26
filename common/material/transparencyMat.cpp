/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** transparencyMat
*/

#include "transparencyMat.hpp"
#include <iostream>

TransparencyMat::TransparencyMat() {
    setMaterialType(MaterialType::TRANSPARENCY_MAT);
    setTransparency(0.6f);
    setRefractiveIndex(1.5f);
}

Color TransparencyMat::applyMaterial(const PixelInfo& pixelInfo, float radius,
    float height, const IPrimitives &primitive) const {
    (void)radius;
    (void)height;
    (void)primitive;
    Color result = pixelInfo._color;
    result.setTransparency(getTransparency());
    return result;
}
