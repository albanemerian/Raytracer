/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Raytracer
*/

#include <arpa/inet.h>
#include <zlib.h>

#include <string>

#include "Image.hpp"
#include "Exception/FileException.hpp"


Image::Image(int new_width, int new_height, int new_maxColorValue)
    : width(new_width),
      height(new_height),
      maxColorValue(new_maxColorValue),
      data(width * height) {
      }

void Image::writeToFilePPM(const std::string &fileName) const {
    std::ofstream file(fileName, std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        throw FileException("Failed to open file: " + fileName);
    }
    file << "P6\n" << width << " " << height << "\n255\n";
    for (const auto &color : data) {
        file.put((color.getRed()));
        file.put((color.getGreen()));
        file.put((color.getBlue()));
    }

    file.close();
}

void Image::setPixel(int x, int y, const Color &color) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw FileException("Pixel coordinates are out of bounds");
    }
    data[y * width + x] = color;
}

Color Image::getPixel(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw FileException("Pixel coordinates are out of bounds");
    }
    return data[y * width + x];
}
