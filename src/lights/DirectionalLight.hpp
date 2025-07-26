/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** DirectionalLight
*/

#ifndef DIRECTIONALLIGHT_HPP_
#define DIRECTIONALLIGHT_HPP_

#include "../../common/ALight.hpp"
#include "../../common/Vector3D.hpp"
#include "../../common/ValueType.hpp"
#include <map>
#include <optional>

class DirectionalLight : public ALight {
    public:
        DirectionalLight();
        DirectionalLight(const Color &color, float intensity,
                        const Math::Vector3D &direction, float radius,
                        std::vector<std::shared_ptr<IPrimitives>> primitivesList);
        DirectionalLight(std::shared_ptr<std::map<ValueType_t, ValueType>> map,
                        std::vector<std::shared_ptr<IPrimitives>> primitivesList);
        ~DirectionalLight();

        void addLight(std::shared_ptr<PixelInfo> pixelInfo, const Math::Ray &ray) const override;
        TypeLight getTypeLight() const override;
        Math::Vector3D getDirection() const override;
        float getRadius() const override;

        // Setters
        void setDirection(const Math::Vector3D &direction);

    private:
        Math::Vector3D _direction;
        Color _color;
        float _intensity;
        float _radius;
};


#endif /* !DIRECTIONALLIGHT_HPP_ */
