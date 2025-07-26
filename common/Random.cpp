/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Random
** For gaussian distribution, see : https://stackoverflow.com/a/6178290
*/

#include "Random.hpp"

namespace Math {

double Random::normalDistribution(uint32_t& state) {
    float theta = 2 * M_PI * pcg(state);
    float rho = std::sqrt(-2 * std::log(pcg(state)));
    return rho  * std::cos(theta);
}

float Random::pcg(uint32_t& state) {
    state = state * 747796405u + 2891336453u;
    state = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
    state = (state >> 22u) ^ state;
    return static_cast<float>(state) / 4294967295.0f;
}

}  // namespace Math
