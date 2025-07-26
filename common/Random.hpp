/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Random
*/

#ifndef RANDOM_HPP_
#define RANDOM_HPP_

#include <cmath>
#include <random>
#include <functional>

namespace Math {

class Random {
 public:
    static double normalDistribution(uint32_t& state);
    static float pcg(uint32_t& state);
};

}  // namespace Math

#endif /* !RANDOM_HPP_ */