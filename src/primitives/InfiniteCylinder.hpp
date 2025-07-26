/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** InfiniteCylinder
*/

#ifndef INFINITECYLINDER_HPP_
#define INFINITECYLINDER_HPP_

#include <map>
#include <optional>
#include "../../common/APrimitives.hpp"
#include "../../common/ValueType.hpp"

class InfiniteCylinder : public APrimitives {
    public:
        InfiniteCylinder();
        InfiniteCylinder(std::shared_ptr<std::map<ValueType_t, ValueType>> map,
          const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>> &graphSceneList);

        ~InfiniteCylinder();

        /* Setter */
        void setBaseRadius(float radius);

        /* Getter */
        float getBaseRadius() const;
        Type getType() const override;
        std::optional<double> distance(const Math::Ray &ray) const override;
        PixelInfo distanceInfo(const Math::Ray &ray) override;
        std::optional<Math::Point3D> getIntersection(const Math::Ray &ray) const override;
        std::optional<Math::Vector3D> getNormal(const Math::Point3D &point) const override;


    private:
        float _baseRadius;
        double _distance;
};

#endif /* !INFINITECYLINDER_HPP_ */
