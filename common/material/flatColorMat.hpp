/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** flatColorMat
*/

#ifndef FLATCOLORMAT_HPP_
#define FLATCOLORMAT_HPP_
#include "AMaterial.hpp"
#include "../IPrimitives.hpp"
#include "../PixelInfo.hpp"

class FlatColorMat : public AMaterial {
    public:
        FlatColorMat();
        ~FlatColorMat() override = default;

        Color applyMaterial(const PixelInfo& pixelInfo, float radius, float height, const IPrimitives &primitive) const override;
};

#endif /* !FLATCOLORMAT_HPP_ */