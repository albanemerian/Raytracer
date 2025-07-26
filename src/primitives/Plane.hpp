/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Plane
*/

#include <memory>
#include <map>
#include "../../common/ValueType.hpp"
#include "../../common/material/IMaterial.hpp"
#include "../../common/APrimitives.hpp"
#include "../../common/Point3D.hpp"
#include "../../common/Rot3D.hpp"
#include "../../common/Vector3D.hpp"

class Plane : public APrimitives {
 public:
    Plane();
    Plane(std::shared_ptr<std::map<ValueType_t, ValueType>> map,
          const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>> &graphSceneList);
    ~Plane() override;

    std::optional<double> distance(const Math::Ray &ray) const override;
    PixelInfo distanceInfo(const Math::Ray &ray) override;
    std::optional<Math::Point3D> getIntersection(const Math::Ray &ray) const override;
    std::optional<Math::Vector3D> getNormal(const Math::Point3D &point) const override;
    /* Getter */
    Type getType() const override;

    /* Setter */
    void setRotation(const Math::Rot3D &newRotation) override;
    void updateNormal();

 private:
    double _distance;
    Math::Vector3D _normal;
    std::string _axe;
};
