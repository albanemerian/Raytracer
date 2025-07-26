/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Cylinder
*/

#ifndef CYLINDER_HPP_
#define CYLINDER_HPP_

#include <map>
#include "../../common/APrimitives.hpp"
#include "../../common/ValueType.hpp"
// #include "../../common/Color.hpp"

class Cylinder : public APrimitives {
    public:
        Cylinder();
        Cylinder(std::shared_ptr<std::map<ValueType_t, ValueType>> map,
          const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>> &graphSceneList);

        ~Cylinder();

        /* Setter */
        void setBaseRadius(float radius);
        void setHeight(float height);

        /* Getter */
        float getBaseRadius() const;
        float getHeight() const;
        Type getType() const override;
        std::optional<double> distance(const Math::Ray &ray) const override;
        PixelInfo distanceInfo(const Math::Ray &ray) override;
        std::optional<Math::Point3D> getIntersection(const Math::Ray &ray) const override;
        std::optional<Math::Vector3D> getNormal(const Math::Point3D &point) const override;

    private:
        float _baseRadius;
        float _height;
        double _distance;

        std::optional<double> getSideIntersection(const Math::Vector3D &localOrigin, const Math::Vector3D &localDir) const;
        std::optional<double> getBaseIntersection(const Math::Vector3D &localOrigin, const Math::Vector3D &localDir) const;
        std::optional<double> getCapIntersection(const Math::Vector3D &localOrigin, const Math::Vector3D &localDir) const;
        Math::Vector3D calculateLocalNormal(const Math::Vector3D &localPoint) const;
};

#endif /* !CYLINDER_HPP_ */

