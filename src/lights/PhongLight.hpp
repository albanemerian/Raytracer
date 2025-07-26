/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** PhongLight
*/

#ifndef PHONGLIGHT_HPP_
#define PHONGLIGHT_HPP_

#include "../../common/ALight.hpp"
#include "../../common/Point3D.hpp"

#include <map>

class PhongLight : public ALight {
    public:
        PhongLight();
        PhongLight(std::shared_ptr<std::map<ValueType_t, ValueType>> map,
                    std::shared_ptr<std::vector<std::shared_ptr<IPrimitives>>> primitivesList);
        PhongLight(const Color &color, float intensity,
                    const Math::Vector3D &direction, float radius, float shininess,
                    std::shared_ptr<std::vector<std::shared_ptr<IPrimitives>>> primitivesList);
        ~PhongLight();

        void addLight(std::shared_ptr<PixelInfo> pixelInfo, const Math::Ray &ray) const override;
        TypeLight getTypeLight() const override;
        Math::Vector3D getDirection() const override;
        float getRadius() const override;
        // Getters
        float getShininess() const;

        // Setters
        void setDirection(const Math::Vector3D &position);
        void setShininess(float shininess);

    private:
        Math::Vector3D _direction;
        Color _color;
        float _intensity;
        float _radius;
        float _shininess;
};

#endif /* !PHONGLIGHT_HPP_ */
