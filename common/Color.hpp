/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Color
*/

#ifndef COLOR_HPP_
#define COLOR_HPP_

#include <cstdint>
#include "Vector3D.hpp"
#include "Exception/ColorException.hpp"

class Color  {
 public:
    Color() {
        this->_red = 0;
        this->_green = 0;
        this->_blue = 0;
        this->_transparency = 255;
    }
    ~Color() = default;

    Color(uint8_t red, uint8_t green, uint8_t blue) {
        this->_red = red;
        this->_green = green;
        this->_blue = blue;
        this->_transparency = 255;
    }

    Color(Math::Vector3D vec) {
        vec.setX(std::min(255.0, std::max(0.0, vec.getX())));
        vec.setY(std::min(255.0, std::max(0.0, vec.getY())));
        vec.setZ(std::min(255.0, std::max(0.0, vec.getZ())));
        this->_red = static_cast<uint8_t>(vec.getX());
        this->_green = static_cast<uint8_t>(vec.getY());
        this->_blue = static_cast<uint8_t>(vec.getZ());
        this->_transparency = 255;
    }

    Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t transparency) {
        this->_red = red;
        this->_green = green;
        this->_blue = blue;
        this->_transparency = transparency;
    }

    Color& operator=(const Math::Vector3D &vec) {
        if (vec.getX() < 0.0 || vec.getX() > 255.0 ||
            vec.getY() < 0.0 || vec.getY() > 255.0 ||
            vec.getZ() < 0.0 || vec.getZ() > 255.0) {
            throw ColorException("Color values must be between 0 and 255");
        }

        this->_red = static_cast<uint8_t>(vec.getX());
        this->_green = static_cast<uint8_t>(vec.getY());
        this->_blue = static_cast<uint8_t>(vec.getZ());
        return *this;
    }

    Color operator*(float scalar) const {
        uint8_t red = static_cast<uint8_t>(std::min(255.0f, std::max(0.0f, static_cast<float>(_red) * scalar)));
        uint8_t green = static_cast<uint8_t>(std::min(255.0f, std::max(0.0f, static_cast<float>(_green) * scalar)));
        uint8_t blue = static_cast<uint8_t>(std::min(255.0f, std::max(0.0f, static_cast<float>(_blue) * scalar)));
        return Color(red, green, blue, _transparency);
    }

    Color operator*(const Color& other) const {
        uint8_t red = static_cast<uint8_t>(std::min(255.0f, (static_cast<float>(_red) * other._red) / 255.0f));
        uint8_t green = static_cast<uint8_t>(std::min(255.0f, (static_cast<float>(_green) * other._green) / 255.0f));
        uint8_t blue = static_cast<uint8_t>(std::min(255.0f, (static_cast<float>(_blue) * other._blue) / 255.0f));
        uint8_t transparency = static_cast<uint8_t>(std::min(255.0f, (static_cast<float>(_transparency) * other._transparency) / 255.0f));
        return Color(red, green, blue, transparency);
    }

    Color operator*=(float scalar) {
        this->_red = static_cast<uint8_t>(std::min(255.0f, std::max(0.0f, static_cast<float>(_red) * scalar)));
        this->_green = static_cast<uint8_t>(std::min(255.0f, std::max(0.0f, static_cast<float>(_green) * scalar)));
        this->_blue = static_cast<uint8_t>(std::min(255.0f, std::max(0.0f, static_cast<float>(_blue) * scalar)));
        return *this;
    }

    Color operator*=(const Color& other) {
        this->_red = static_cast<uint8_t>(std::min(255.0f, (static_cast<float>(_red) * other._red) / 255.0f));
        this->_green = static_cast<uint8_t>(std::min(255.0f, (static_cast<float>(_green) * other._green) / 255.0f));
        this->_blue = static_cast<uint8_t>(std::min(255.0f, (static_cast<float>(_blue) * other._blue) / 255.0f));
        this->_transparency = static_cast<uint8_t>(std::min(255.0f, (static_cast<float>(_transparency) * other._transparency) / 255.0f));
        return *this;
    }

    Color operator+(const Color& other) const {
        uint8_t red = static_cast<uint8_t>(std::min(255, static_cast<int>(_red) + static_cast<int>(other._red)));
        uint8_t green = static_cast<uint8_t>(std::min(255, static_cast<int>(_green) + static_cast<int>(other._green)));
        uint8_t blue = static_cast<uint8_t>(std::min(255, static_cast<int>(_blue) + static_cast<int>(other._blue)));
        uint8_t transparency = static_cast<uint8_t>(std::min(255, static_cast<int>(_transparency) + static_cast<int>(other._transparency)));
        return Color(red, green, blue, transparency);
    }

    Color operator+=(const Color& other) {
        this->_red= static_cast<uint8_t>(std::min(255, static_cast<int>(_red) + static_cast<int>(other._red)));
        this->_green = static_cast<uint8_t>(std::min(255, static_cast<int>(_green) + static_cast<int>(other._green)));
        this->_blue = static_cast<uint8_t>(std::min(255, static_cast<int>(_blue) + static_cast<int>(other._blue)));
        this->_transparency = static_cast<uint8_t>(std::min(255, static_cast<int>(_transparency) + static_cast<int>(other._transparency)));
        return *this;
    }

    Color operator-(const Color& other) const {
        uint8_t red = static_cast<uint8_t>(std::max(0, static_cast<int>(_red) - static_cast<int>(other._red)));
        uint8_t green = static_cast<uint8_t>(std::max(0, static_cast<int>(_green) - static_cast<int>(other._green)));
        uint8_t blue = static_cast<uint8_t>(std::max(0, static_cast<int>(_blue) - static_cast<int>(other._blue)));
        uint8_t transparency = static_cast<uint8_t>(std::max(0, static_cast<int>(_transparency) - static_cast<int>(other._transparency)));
        return Color(red, green, blue, transparency);
    }

    Color operator-=(const Color& other) {
        this->_red = static_cast<uint8_t>(std::max(0, static_cast<int>(_red) - static_cast<int>(other._red)));
        this->_green = static_cast<uint8_t>(std::max(0, static_cast<int>(_green) - static_cast<int>(other._green)));
        this->_blue = static_cast<uint8_t>(std::max(0, static_cast<int>(_blue) - static_cast<int>(other._blue)));
        this->_transparency = static_cast<uint8_t>(std::max(0, static_cast<int>(_transparency) - static_cast<int>(other._transparency)));
        return *this;
    }



    void setTransparency(float transparencyValue) {
        this->_transparency = static_cast<uint8_t>(255 * (1.0f - transparencyValue));
    }
    /* Getter */
    uint8_t getRed() const { return this->_red; }
    uint8_t getGreen() const { return this->_green; }
    uint8_t getBlue() const { return this->_blue; }
    uint8_t getTransparency() const { return this->_transparency; }

    /* Setter */
    void setRed(uint8_t red) { this->_red = red; }
    void setGreen(uint8_t green) { this->_green = green; }
    void setBlue(uint8_t blue) { this->_blue = blue; }

 protected:
 private:
    uint8_t _red;
    uint8_t _green;
    uint8_t _blue;

    uint8_t _transparency;
};

#endif /* !COLOR_HPP_ */
