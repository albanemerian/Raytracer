/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** transparencyMat
*/

#ifndef TRANSPARENCYMAT_HPP_
#define TRANSPARENCYMAT_HPP_

#include "AMaterial.hpp"

class TransparencyMat : public AMaterial {
    public:
        TransparencyMat();
        ~TransparencyMat() override = default;

        Color applyMaterial(const PixelInfo& pixelInfo, float radius, float height, const IPrimitives &primitive) const override;
};
#endif /* !TRANSPARENCYMAT_HPP_ */
