/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** ILight
*/

#include <memory>
#include <vector>
#include "Color.hpp"
#include "PixelInfo.hpp"
#include "Ray.hpp"
#include "Vector3D.hpp"

#ifndef ILIGHT_HPP_
#define ILIGHT_HPP_


enum class TypeLight { POINT, DIRECTIONAL, PHONG, AMBIENT };

// Forward declaration to avoid circular dependencies
class IPrimitives;

class ILight {
    public:
        virtual ~ILight() = default;

        virtual void addLight(std::shared_ptr<PixelInfo> pixelInfo, const Math::Ray &ray) const = 0;

        // Geters
        virtual Color getColor() const = 0;
        virtual Math::Vector3D getDirection() const = 0;
        virtual float getIntensity() const = 0;
        virtual float getRadius() const = 0;
        virtual TypeLight getTypeLight() const = 0;
        virtual std::shared_ptr<std::vector<std::shared_ptr<IPrimitives>>> getPrimitives() const = 0;

        // Setters
        virtual void setColor(const Color &color) = 0;
        virtual void setIntensity(float intensity) = 0;
        
};

#endif /* !ILIGHT_HPP_ */
