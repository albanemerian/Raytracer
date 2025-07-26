/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Utils
*/

#include "Utils.hpp"

#include <iostream>

Utils::Utils() {}

Utils::~Utils() {}

void Utils::helper() {
    std::cout << "USAGE :\n";
    std::cout << "\t./raytracer <SCENE_FILE>\n";
    std::cout << "OPTIONS :\n";
    std::cout << "\t-h, --help\t\tDisplay this help message\n";
    std::cout << "\t-g, Display the imahe in a sfml window\n";
    std::cout << "\t-n + \"file_name\"\t\tSpecify the name output file\n";
    std::cout << "\t-f Specify format of the output : jpg, jpeg, png, bmp\n";
    std::cout << "\t-d display debugs of the element" << std::endl;
    std::cout << "\t-l number of layers to compute\n",
    std::cout << "SCENE_FILE :\n";
    std::cout << " The scene files needs to be properlly formatted.";
    std::cout << " The exentsion of the file needs to be .cfg\n";
    std::cout << "If no output file name is specified,";
    std::cout << " the default name is \"output\" and format : .ppm\n";
    exit(0);
}
