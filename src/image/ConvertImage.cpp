/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** ConvertImage
*/


#include <iostream>
#include <string>

#include "../Raytracer.hpp"

#include <SFML/Graphics.hpp>



void Raytracer::loopThruType() {
    if (getOutputFormat() == "ppm")
        return;
    sf::Image newImage;
    std::string fileName = this->_outputfile;
    if (!newImage.loadFromFile(this->_outputfile)) {
        std::cerr << "Error loading newImage: " <<
        this->_outputfile << std::endl;
        return;
    }
    fileName = fileName.substr(0, fileName.find_last_of('.'))
        + "." + getOutputFormat();
    if (!newImage.saveToFile(fileName)) {
        std::cerr << "Error saving image: " << fileName << std::endl;
        return;
    }
}
