/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Raytracer
*/

#include <fstream>
#include <iostream>
#include <vector>

#include "../common/Error.hpp"
#include "Color.hpp"

#ifndef IMAGE_HPP_
#define IMAGE_HPP_

class Image {
 public:
    Image(int width, int height, int maxColorValue = 255);
    ~Image() = default;

    int getWidth() const { return width; }

    int getHeight() const { return height; }

    int getMaxColorValue() const { return maxColorValue; }

    const std::vector<Color> &getData() const { return data; }

    void writeToFilePPM(const std::string &fileName) const;
    void setPixel(int x, int y, const Color &color);
    Color getPixel(int x, int y) const;

 private:
    int width;
    int height;
    int maxColorValue;
    std::vector<Color> data;
};

#endif /* !IMAGE_HPP_ */
