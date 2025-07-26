/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** AMaterial
*/

#include "AMaterial.hpp"

AMaterial::AMaterial()
    : ambient(0.0f, 0.0f, 0.0f)
    , diffuse(0.0f, 0.0f, 0.0f)
    , specular(0.0f, 0.0f, 0.0f)
    , shininess(32.0f)
    , reflectivity(0.0f)
    , transparency(0.0f)
    , refractiveIndex(1.0f)
    , opacity(1.0f)
    , colorTexture(nullptr)
    , normalMap(nullptr)
    , materialType(FLAT_COLOR) {
}
