/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Raytracer
*/

#include <dirent.h>
#include <sys/types.h>

#include <map>
#include <cstring>
#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <cstdio>
#include "../common/Image.hpp"
#include "Raytracer.hpp"
#include "../common/Exception/CommandException.hpp"
#include "../common/Exception/FileException.hpp"
#include "utils/Utils.hpp"

Raytracer::Raytracer() {
    this->_outputfile = "";
    this->_outputformat = "";
    this->_scenefile = "";
    this->graphicMode = false;
    this->debugMode = false;
    this->image = nullptr;
    this->_scene = Scene();
    this->_display = nullptr;
    this->numRenders = 1;
}

Raytracer::~Raytracer() {
}

/* Getter */

std::string Raytracer::getSceneFile() const {
    return this->_scenefile;
}

std::string Raytracer::getOutputFile() const {
    return this->_outputfile;
}

std::string Raytracer::getOutputFormat() const {
    return this->_outputformat;
}

std::shared_ptr<Image> Raytracer::getImage() const {
    return image;
}

bool Raytracer::getGraphicMode() const {
    return this->graphicMode;
}

bool Raytracer::isDebug() const {
    return this->debugMode;
}

Scene Raytracer::getScene() const {
    return _scene;
}

/* Setter */

void Raytracer::setSceneFile(std::string sceneFile) {
    this->_scenefile = sceneFile;
}

void Raytracer::setOutputFile(std::string outputFile) {
    this->_outputfile = outputFile;
}

void Raytracer::setOutputFormat(std::string outputFormat) {
    this->_outputformat = outputFormat;
}

void Raytracer::setScene(Scene scene) {
    this->_scene = scene;
}


bool Raytracer::setGraphicMode() {
    try {
        DLLoader<void*> loader;
        if (loader.Open("src/raytracer_sfml.so", RTLD_LAZY) != nullptr) {
            std::cout << "SFML library loaded successfully." << std::endl;
            auto createGraphicMode = loader.Symbol("createInstance");
            if (createGraphicMode != nullptr) {
                this->_display = reinterpret_cast<std::shared_ptr
                    <GraphicMode> (*)()>(createGraphicMode)();
            } else {
                throw FileException(loader.Error());
            }
        } else {
            throw FileException(loader.Error());
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        this->graphicMode = false;
        this->_display = nullptr;
        return false;
    }
    return true;
}

/* Methods */

void Raytracer::setImage(std::shared_ptr<Image> new_Image) {
    this->image = new_Image;
}

/* Methods */

void Raytracer::writeToFilePPM(std::string fileName) {
    image->writeToFilePPM(fileName);
}

void Raytracer::InitParams() {
    if (this->_outputfile.empty()) {
        this->_outputfile = "output.ppm";
    }
    if (this->_outputformat.empty()) {
        this->_outputformat = "ppm";
    }
    if (this->debugMode == true) {
        std::cout << " Scene file = " << this->_scenefile << std::endl;
        std::cout << " Output file = " << this->_outputfile << std::endl;
        std::cout << " Output Format = " << this->_outputformat << std::endl;
        std::cout << " Debug Mode  = " << std::boolalpha << std::endl;
    }
}

void Raytracer::parseCmd(int ac, char **av) {
    Utils u;
    std::string file = av[1];

    if (ac < 2) {
        throw CommandException("Missing scene file argument");
    }
    for (int i = 1; i < ac; i++) {
        if (strcmp(av[i], "-h") == 0 || strcmp(av[i], "--help") == 0) {
            u.helper();
        }
    }
    if (file.size() < 4 || file.substr(file.size() - 4) != ".cfg") {
        throw CommandException("Invalid scene file extension");
    }
    this->setSceneFile(file);
    for (int i = 2; i < ac; i++) {
        if (strcmp(av[i], "-n") == 0) {
            if (av[i + 1] != nullptr) {
                this->setOutputFile(av[i + 1]);
                i++;
            } else {
                throw CommandException("Missing output file name");
            }
        } else if (strcmp(av[i], "-f") == 0) {
            if (av[i + 1] != nullptr && (strcmp(av[i + 1], "jpg") == 0 ||
                strcmp(av[i + 1], "jpeg") == 0 ||
                strcmp(av[i + 1], "png") == 0 ||
                strcmp(av[i + 1], "bmp") == 0)) {
                this->setOutputFormat(av[i + 1]);
                i++;
            } else {
                throw CommandException("Missing output format");
            }
        } else if (strcmp(av[i], "-g") == 0) {
            this->graphicMode = true;
        } else if (strcmp(av[i], "-d") == 0) {
            this->debugMode = true;
        } else if (strcmp(av[i], "-l") == 0) {
            if (av[i + 1] != nullptr) {
                this->numRenders = std::stoi(av[i + 1]);
                i++;
            } else {
                throw CommandException("Missing number of renders");
            }
        } else {
            throw CommandException("Invalid argument");
        }
    }
    InitParams();
}

void Raytracer::LoadAllformlibs
(const std::vector<std::shared_ptr
<std::map<ValueType_t, ValueType>>>& objectsConfig) {
    std::cout << "Loading all objects from libraries..." << std::endl;
    _factoryManager.createObjectsFromConfig(objectsConfig);
}
