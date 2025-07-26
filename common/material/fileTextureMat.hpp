/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** fileTextureMat
*/

#ifndef FILETEXTUREMAT_HPP_
#define FILETEXTUREMAT_HPP_

#include "AMaterial.hpp"

class FileTextureMat : public AMaterial {
    public:
        FileTextureMat();
        ~FileTextureMat() override = default;

        Color applyMaterial(const PixelInfo& pixelInfo, float radius, float height, const IPrimitives &primitive) const override;

        void loadTextureFromFile(const std::string& filePath);
        Color getTextureFromFile(const PixelInfo& pixelInfo, std::shared_ptr<float> u, std::shared_ptr<float> v) const;
        void calculUVCoordinates(const IPrimitives &primitive, const PixelInfo& pixelInfo,
            float radius, float height, std::shared_ptr<float> u, std::shared_ptr<float> v) const;
    private:
        void calculUVCoordinatesSphere(const IPrimitives &primitive, const PixelInfo& pixelInfo,
            float radius, std::shared_ptr<float> u, std::shared_ptr<float> v) const;
        void calculUVCoordinatesCylinder(const IPrimitives &primitive, const PixelInfo& pixelInfo,
            float radius, float height, std::shared_ptr<float> u, std::shared_ptr<float> v) const;
        void calculUVCoordinatesCone(const IPrimitives &primitive, const PixelInfo& pixelInfo,
            float radius, float height, std::shared_ptr<float> u, std::shared_ptr<float> v) const;
        void calculUVCoordinatesPlane(const IPrimitives &primitive, const PixelInfo& pixelInfo,
            float radius, float height, std::shared_ptr<float> u, std::shared_ptr<float> v) const;
};

#endif /* !FILETEXTUREMAT_HPP_ */
