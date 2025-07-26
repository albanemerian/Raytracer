/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** IMaterial
*/

#ifndef IMATERIAL_HPP_
#define IMATERIAL_HPP_

#include "../Vector3D.hpp"
#include "../Color.hpp"
#include "../PixelInfo.hpp"
#include <memory>

// Forward declaration pour éviter les dépendances circulaires
class IPrimitives;

enum MaterialType {
    FLAT_COLOR,
    TRANSPARENCY_MAT,
    CHESSBOARD,
    FILE_TEXTURE_MAT,
    PERLING_NOISE_MAT
};

class IMaterial {
    public:
        virtual ~IMaterial() = default;

        // Setters
        virtual void setAmbient(const Math::Vector3D& a) = 0;
        virtual void setDiffuse(const Math::Vector3D& d) = 0;
        virtual void setSpecular(const Math::Vector3D& s) = 0;
        virtual void setShininess(float s) = 0;
        virtual void setReflectivity(float r) = 0;
        virtual void setTransparency(float t) = 0;
        virtual void setRefractiveIndex(float i) = 0;
        virtual void setOpacity(float o) = 0;
        virtual void setColorTexture(const std::shared_ptr<std::string>& texture) = 0;
        virtual void setNormalMap(const std::shared_ptr<std::string>& map) = 0;
        virtual void setOptionalColor1(const Color& color) = 0;
        virtual void setOptionalColor2(const Color& color) = 0;
        virtual void setScale(float s) = 0;
        virtual void setMaterialType(MaterialType type) = 0;

        // Getters
        virtual Math::Vector3D getAmbient() const = 0;
        virtual Math::Vector3D getDiffuse() const = 0;
        virtual Math::Vector3D getSpecular() const = 0;
        virtual float getShininess() const = 0;
        virtual float getReflectivity() const = 0;
        virtual float getTransparency() const = 0;
        virtual float getRefractiveIndex() const = 0;
        virtual float getOpacity() const = 0;
        virtual std::shared_ptr<std::string> getColorTexture() const = 0;
        virtual std::shared_ptr<std::string> getNormalMap() const = 0;
        virtual Color getOptionalColor1() const = 0;
        virtual Color getOptionalColor2() const = 0;
        virtual float getScale() const = 0;
        virtual MaterialType getMaterialType() const = 0;

        // Material application methods
        virtual Color applyMaterial(const PixelInfo& pixelInfo, float radius, float height, const IPrimitives &primitive) const = 0;
};

#endif /* !IMATERIAL_HPP_ */
