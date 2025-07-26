/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** ALight
*/

#ifndef ALIGHT_HPP_
#define ALIGHT_HPP_

#include "ILight.hpp"
#include "ValueType.hpp"
#include "Point3D.hpp"

class ALight : public ILight {
    public:
        ALight();
        ALight(const Color &color, float intensity);
        ALight(const Color &color, float intensity,std::shared_ptr<std::vector<std::shared_ptr<IPrimitives>>> primitivesList);
        ~ALight() override;

        /* Virtual methods */
        virtual void addLight(std::shared_ptr<PixelInfo> pixelInfo, const Math::Ray &ray) const = 0;
        virtual TypeLight getTypeLight() const override = 0;

        /* Getter */
        Color getColor() const override;
        float getIntensity() const override;
        std::shared_ptr<std::vector<std::shared_ptr<IPrimitives>>> getPrimitives() const override { return _primitives; }

        /* Setter */
        void setColor(const Color &color) override;
        void setIntensity(float intensity) override;

    protected:
        Color _color;
        float _intensity;
        std::shared_ptr<std::vector<std::shared_ptr<IPrimitives>>> _primitives;
};

#endif /* !ALIGHT_HPP_ */
