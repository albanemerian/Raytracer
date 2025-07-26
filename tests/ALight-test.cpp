/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** ALight-test
*/

#include <criterion/criterion.h>
#include "../common/ALight.hpp"

// Minimal concrete subclass for testing ALight
class TestLight : public ALight {
public:
    TestLight() : ALight() {}
    TestLight(const Color &color, float intensity) : ALight(color, intensity) {}
    void addLight(std::shared_ptr<PixelInfo> pixelInfo, const Math::Ray &ray) const override {}
    TypeLight getTypeLight() const override { return TypeLight::POINT; }
    Math::Vector3D getDirection() const override { return Math::Vector3D(0, 0, 0); }
    float getRadius() const override { return 0.0f; }
};

Test(ALight, default_constructor) {
    TestLight light(Color(0, 0, 0), 0.0f);
    cr_assert_eq(light.getColor().getRed(), 0);
    cr_assert_eq(light.getColor().getGreen(), 0);
    cr_assert_eq(light.getColor().getBlue(), 0);
    cr_assert_float_eq(light.getIntensity(), 0.0f, 0.0001);
}

Test(ALight, parameterized_constructor) {
    Color c(10, 20, 30);
    TestLight light(c, 1.5f);
    cr_assert_eq(light.getColor().getRed(), 10);
    cr_assert_eq(light.getColor().getGreen(), 20);
    cr_assert_eq(light.getColor().getBlue(), 30);
    cr_assert_float_eq(light.getIntensity(), 1.5f, 0.0001);
}

Test(ALight, setColor_and_getColor) {
    TestLight light;
    Color c(100, 150, 200);
    light.setColor(c);
    Color result = light.getColor();
    cr_assert_eq(result.getRed(), 100);
    cr_assert_eq(result.getGreen(), 150);
    cr_assert_eq(result.getBlue(), 200);
}

Test(ALight, setIntensity_and_getIntensity) {
    TestLight light;
    light.setIntensity(2.5f);
    cr_assert_float_eq(light.getIntensity(), 2.5f, 0.0001);
}

