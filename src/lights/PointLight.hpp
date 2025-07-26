/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** PointLight
*/

#ifndef POINTLIGHT_HPP_
#define POINTLIGHT_HPP_

#include "../../common/ALight.hpp"
#include "../../common/Point3D.hpp"
#include "../../common/ValueType.hpp"
#include <map>
#include <memory>

class PointLight : public ALight {
    public:
        PointLight();
        PointLight(const Color &color, float intensity,
                   const Math::Point3D &position, float radius,
                   std::shared_ptr<std::vector<std::shared_ptr<IPrimitives>>> primitivesList = {});
        PointLight(std::shared_ptr<std::map<ValueType_t, ValueType>> map,
                  std::shared_ptr<std::vector<std::shared_ptr<IPrimitives>>> primitivesList = {});
        ~PointLight();

        /* Override method */
        TypeLight getTypeLight() const override;
        void addLight(std::shared_ptr<PixelInfo> pixelInfo, const Math::Ray &ray) const override;

        // Getters
        Math::Point3D getPosition() const;
        float getRadius() const;

        // Setters
        void setPosition(const Math::Point3D &position);
        void setRadius(float radius);

    private:
        Math::Point3D _position;
        float _radius;
};

#endif /* !POINTLIGHT_HPP_ */
