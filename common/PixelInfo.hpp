/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** PixelInfo
*/

#ifndef PIXELINFO_HPP_
#define PIXELINFO_HPP_

#include "Color.hpp"
#include "Vector3D.hpp"

struct PixelInfo {
    Color _color;
    Math::Vector3D _normalizedVector;
    double _distance;
    bool _isHit;
    Math::Vector3D _pos;
    float _light_intensity;
    Color _light_color;

    PixelInfo() : 
        _color(),
        _normalizedVector(),
        _distance(0.0),
        _isHit(false),
        _pos(),
        _light_intensity(0.0f),
        _light_color()
    {}

    PixelInfo(const Color& color, const Math::Vector3D& normalVector, double distance, 
              bool isHit, const Math::Vector3D& position, float lightIntensity, const Color& colorLight) :
        _color(color),
        _normalizedVector(normalVector),
        _distance(distance),
        _isHit(isHit),
        _pos(position),
        _light_intensity(lightIntensity),
        _light_color(colorLight)
    {}
};

#endif /* !PIXELINFO_HPP_ */
