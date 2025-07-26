/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Material
*/

#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_
#include "Vector3D.hpp"
#include "Color.hpp"

enum MaterialType {
    FLAT_COLOR,
    TRANSPARENCY_MAT,
    CHESSBOARD,
    FILE_TEXTURE_MAT,
    PERLING_NOISE_MAT
};

struct Material {
    // Basic colors/components (Vec3: r,g,b in [0,1])
    Math::Vector3D ambient; // Ambient reflection coefficient
    Math::Vector3D diffuse; // Diffuse (Lambertian) reflection coefficient
    Math::Vector3D specular; // Specular reflection coefficient
    float shininess;         // Phong exponent (higher = smaller, sharper highlights)

    Color OptionalColor1 = Color(0.0f, 0.0f, 0.0f); // Color for the first chessboard square
    Color OptionalColor2 = Color(0.0f, 0.0f, 0.0f); // Color for the second chessboard square
    float scale = 5.0f; // Scale for the chessboard pattern

    // Reflection & Refraction
    float reflectivity;      // [0,1] Fraction of reflection ray contribution
    float transparency;      // [0,1] Fraction of refracted ray contribution
    float refractiveIndex;      // Snell's law index (1.0 = vacuum/air)
    float opacity;      // [0,1] Fraction of light that is absorbed by the material

    // Optional textures (nullptr if unused)
    std::shared_ptr<std::string> colorTexture;     // Overrides diffuse when present
    std::shared_ptr<std::string> normalMap;        // Perturbs surface normals for bump mapping

    MaterialType materialType = FLAT_COLOR;

    // Constructors
    Material()
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
    {}

    Material(const Math::Vector3D& a, const Math::Vector3D& d, const Math::Vector3D& s, float shin,
             float refl = 0.0f, float trans = 0.0f, float ior = 1.0f)
        : ambient(a)
        , diffuse(d)
        , specular(s)
        , shininess(shin)
        , reflectivity(refl)
        , transparency(trans)
        , refractiveIndex(ior)
        , opacity(1.0f)
        , colorTexture(nullptr)
        , normalMap(nullptr)
    {}
};


#endif /* !MATERIAL_HPP_ */
