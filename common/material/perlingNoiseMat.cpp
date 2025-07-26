/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** perlingNoiseMat
*/

#include "perlingNoiseMat.hpp"
#include <algorithm>
#include <iostream>
#include <cmath>

PerlingNoiseMat::PerlingNoiseMat() {
    setMaterialType(MaterialType::PERLING_NOISE_MAT);
    frequency = 0.5f;
    amplitude = 1.0f;
    octaves = 9;
    persistence = 0.2f;
}

int PerlingNoiseMat::hash(int x, int y) const {
    uint32_t state =
        static_cast<uint32_t>(x * 374761393 + y * 668265263);
    return static_cast<int>
        (Math::Random::normalDistribution(state) * 2147483647);
}

float PerlingNoiseMat::dotGridGradient
    (int ix, int iy, float x, float y) const {
    uint32_t h = static_cast<uint32_t>(hash(ix, iy));
    int idx = h & 7;
    static const float gradX[] = { 1.0f, -1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, 0.0f, 0.0f };
    static const float gradY[] = { 1.0f, 1.0f, -1.0f, -1.0f,
        0.0f, 0.0f, 1.0f, -1.0f };
    float gx = gradX[idx];
    float gy = gradY[idx];
    float dx = x - static_cast<float>(ix);
    float dy = y - static_cast<float>(iy);
    return (dx * gx + dy * gy);
}

float PerlingNoiseMat::interpolate(float a0, float a1, float w) const {
    w = w * w * (3.0f - 2.0f * w);
    return a0 + w * (a1 - a0);
}

float PerlingNoiseMat::perlinNoise(float x, float y) const {
    int x0 = static_cast<int>(floor(x));
    int x1 = x0 + 1;
    int y0 = static_cast<int>(floor(y));
    int y1 = y0 + 1;
    float sx = x - static_cast<float>(x0);
    float sy = y - static_cast<float>(y0);
    float n00 = dotGridGradient(x0, y0, x, y);
    float n10 = dotGridGradient(x1, y0, x, y);
    float n01 = dotGridGradient(x0, y1, x, y);
    float n11 = dotGridGradient(x1, y1, x, y);
    float ix0 = interpolate(n00, n10, sx);
    float ix1 = interpolate(n01, n11, sx);
    return interpolate(ix0, ix1, sy);
}

float PerlingNoiseMat::fractalBrownianMotion(float x, float y) const {
    float total = 0.0f;
    float maxValue = 0.0f;
    float freq = this->frequency;
    float ampl = this->amplitude;

    for (int i = 0; i < octaves; i++) {
        total += perlinNoise(x * freq, y * freq) * ampl;
        maxValue += ampl;
        freq *= 2.0f;
        ampl *= persistence;
    }
    return total / maxValue;
}

Color PerlingNoiseMat::applyMaterial(const PixelInfo& pixelInfo, float radius,
    float height, const IPrimitives& primitive) const {
    (void)radius;
    (void)height;
    Math::Vector3D localPos = primitive.getRotation().inverseRotate
        (pixelInfo._pos - primitive.getPosition());
    float noiseValue = fractalBrownianMotion(localPos.getX(), localPos.getZ());
    noiseValue = (noiseValue + 1.0f) * 0.5f;
    Color result(noiseValue * 255, noiseValue * 255, noiseValue * 255);
    return result;
}
