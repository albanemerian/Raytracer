/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Cone
*/

#ifndef CONE_HPP_
#define CONE_HPP_

#include <map>
#include <optional>
#include "../../common/APrimitives.hpp"
#include "../../common/ValueType.hpp"

class Cone : public APrimitives {
    public:
        Cone();
        Cone(std::shared_ptr<std::map<ValueType_t, ValueType>> map,
          const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>> &graphSceneList);
        ~Cone();
        /* Setter */
        void setBaseRadius(float radius);
        void setHeight(float height);

        /* Method */
        std::optional<double> distance(const Math::Ray &ray) const override;
        PixelInfo distanceInfo(const Math::Ray &ray) override;
        std::optional<Math::Point3D> getIntersection(const Math::Ray &ray) const override;
        std::optional<Math::Vector3D> getNormal(const Math::Point3D &point) const override;

        /* Getter */
        float getBaseRadius() const;
        Type getType() const override;
        float getHeight() const;


        Math::Vector3D transformToLocal(const Math::Ray &ray) const;
        Math::Vector3D localDirectionVector(const Math::Ray &ray) const;
        std::optional<double> intersectConeBody(const Math::Vector3D &localOrigin, const Math::Vector3D &localDirection) const;
        std::optional<double> intersectConeBase(const Math::Vector3D &localOrigin, const Math::Vector3D &localDirection) const;
        bool isPointOnConeBody(const Math::Point3D &hitPoint) const;
    protected:
    private:
        float _baseRadius;
        float _height;
        double _distance;

 };

#endif /* !CONE_HPP_ */
