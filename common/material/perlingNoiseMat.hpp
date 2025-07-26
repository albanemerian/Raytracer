/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** perlingNoiseMat
*/

#ifndef PERLINGNOISEMAT_HPP_
#define PERLINGNOISEMAT_HPP_

#include "AMaterial.hpp"
#include <cmath>
#include <random>
#include <vector>
#include "../IPrimitives.hpp"

class PerlingNoiseMat : public AMaterial {
    public:
        PerlingNoiseMat();
        ~PerlingNoiseMat() override = default;

        Color applyMaterial(const PixelInfo& pixelInfo, float radius, float height, const IPrimitives& primitive) const override;

    private:
        float frequency;
        float amplitude;
        int octaves;
        float persistence;

        float dotGridGradient(int ix, int iy, float x, float y) const;
        float interpolate(float a0, float a1, float w) const;
        float perlinNoise(float x, float y) const;
        float fractalBrownianMotion(float x, float y) const;
        int hash(int x, int y) const;

};

#endif /* !PERLINGNOISEMAT_HPP_ */
