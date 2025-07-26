/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** IPrimitives
*/

#include <memory>
#include <optional>

#include "material/IMaterial.hpp"
#include "Point3D.hpp"
#include "Ray.hpp"
#include "Rot3D.hpp"
#include "PixelInfo.hpp"


#ifndef IPRIMITIVES_HPP_
#define IPRIMITIVES_HPP_

enum class Type { SPHERE, PLANE, CYLINDER, CONE, CUBE, TORUS };

class IPrimitives {
 public:
    virtual ~IPrimitives() = default;

    virtual std::optional<double> distance(const Math::Ray &ray) const = 0;
    virtual PixelInfo distanceInfo(const Math::Ray &ray) = 0;
    virtual std::optional<Math::Point3D> getIntersection(const Math::Ray &ray) const = 0;
    virtual std::optional<Math::Vector3D> getNormal(const Math::Point3D &point) const = 0;
    virtual Math::Ray computeScaledRay(const Math::Ray &ray) const = 0;

    /* Getter */
    virtual Type getType() const = 0;
    virtual Math::Point3D getPosition() const = 0;
    virtual Math::Rot3D getRotation() const = 0;
    virtual float getScale() const = 0;
    virtual std::shared_ptr<IMaterial> getMaterial() const = 0;

    /* Setter */
    virtual void setPosition(const Math::Point3D &position) = 0;
    virtual void setRotation(const Math::Rot3D &rotation) = 0;
    virtual void setScale(float scale) = 0;
    virtual void setMaterial(std::shared_ptr<IMaterial> material) = 0;
 protected:
 private:
};

#endif /* !IPRIMITIVES_HPP_ */
