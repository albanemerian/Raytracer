/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Random-test
*/

#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <vector>
#include "../common/Random.hpp"

Test(Random, pcg_returns_value_between_0_and_1) {
    uint32_t state = 42;
    for (int i = 0; i < 100; i++) {
        float val = Math::Random::pcg(state);
        cr_assert(val >= 0.0f && val <= 1.0f, "PCG value %f outside [0,1] range", val);
    }
}

Test(Random, pcg_changes_state) {
    uint32_t state1 = 42;
    uint32_t state2 = 42;
    float val1 = Math::Random::pcg(state1);
    float val2 = Math::Random::pcg(state2);
    cr_assert_float_eq(val1, val2, 0.0001);
    float val3 = Math::Random::pcg(state1);
    float val4 = Math::Random::pcg(state2);
    cr_assert_float_eq(val3, val4, 0.0001);
    uint32_t state3 = 43;
    float val5 = Math::Random::pcg(state3);
    cr_assert(val1 != val5, "Different seeds should produce different values");
}

Test(Random, normalDistribution_distribution_properties) {
    uint32_t state = 42;
    std::vector<double> samples;
    const int sampleSize = 1000;
    for (int i = 0; i < sampleSize; i++) {
        samples.push_back(Math::Random::normalDistribution(state));
    }
    double sum = 0;
    for (double sample : samples) {
        sum += sample;
    }
    double mean = sum / sampleSize;
    cr_assert(std::abs(mean) < 0.1, "Mean should be approximately 0, got %f", mean);
    double sumSquaredDiff = 0;
    for (double sample : samples) {
        sumSquaredDiff += (sample - mean) * (sample - mean);
    }
    double variance = sumSquaredDiff / sampleSize;
    cr_assert(std::abs(variance - 1.0) < 0.2, "Variance should be approximately 1, got %f", variance);
}
