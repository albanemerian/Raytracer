/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** AMaterial
*/

#ifndef AMATERIAL_HPP_
#define AMATERIAL_HPP_
#include "IMaterial.hpp"
#include "../Vector3D.hpp"
#include "../Color.hpp"
#include <memory>

class AMaterial : public IMaterial {
    public:
        AMaterial();
        virtual ~AMaterial() = default;

        void setAmbient(const Math::Vector3D& a) override { ambient = a; }
        void setDiffuse(const Math::Vector3D& d) override { diffuse = d; }
        void setSpecular(const Math::Vector3D& s) override { specular = s; }
        void setShininess(float s) override { shininess = s; }
        void setReflectivity(float r) override { reflectivity = r; }
        void setTransparency(float t) override { transparency = t; }
        void setRefractiveIndex(float i) override { refractiveIndex = i; }
        void setOpacity(float o) override { opacity = o; }
        void setColorTexture(const std::shared_ptr<std::string>& texture) override { colorTexture = texture; }
        void setNormalMap(const std::shared_ptr<std::string>& map) override { normalMap = map; }
        void setOptionalColor1(const Color& color) override { OptionalColor1 = color; }
        void setOptionalColor2(const Color& color) override { OptionalColor2 = color; }
        void setScale(float s) override { scale = s; }
        void setMaterialType(MaterialType type) override { materialType = type; }

        Math::Vector3D getAmbient() const override { return ambient; }
        Math::Vector3D getDiffuse() const override { return diffuse; }
        Math::Vector3D getSpecular() const override { return specular; }
        float getShininess() const override { return shininess; }
        float getReflectivity() const override { return reflectivity; }
        float getTransparency() const override { return transparency; }
        float getRefractiveIndex() const override { return refractiveIndex; }
        float getOpacity() const override { return opacity; }
        std::shared_ptr<std::string> getColorTexture() const override { return colorTexture; }
        std::shared_ptr<std::string> getNormalMap() const override { return normalMap; }
        Color getOptionalColor1() const override { return OptionalColor1; }
        Color getOptionalColor2() const override { return OptionalColor2; }
        float getScale() const override { return scale; }
        MaterialType getMaterialType() const override { return materialType; }

        virtual Color applyMaterial(const PixelInfo& pixelInfo, float radius, float height, const IPrimitives &primitive) const = 0;
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
        float refractiveIndex;   // Snell's law index (1.0 = vacuum/air)
        float opacity;           // [0,1] Fraction of light that is absorbed by the material

        // Optional textures (nullptr if unused)
        std::shared_ptr<std::string> colorTexture;     // Overrides diffuse when present
        std::shared_ptr<std::string> normalMap;        // Perturbs surface normals for bump mapping
        MaterialType materialType = MaterialType::FLAT_COLOR;
};

#endif /* !AMATERIAL_HPP_ */