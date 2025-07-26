/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Parser
*/

#include "Parser.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <filesystem>

#include "../../common/Exception/FileException.hpp"

Parser::Parser() {
}

Parser::Parser(const std::string &filename) {
    loadConfig(filename);
    parse();
}

Parser::~Parser() {}

const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>
    &Parser::getObjects() const {
    return _objectConstructor.getObjects();
}

void Parser::loadConfig(const std::string &filename) {
    if (!configParser.loadConfig(filename, rootNode)) {
        std::cerr << "Failed to load file: " << filename << std::endl;
    }
}

void Parser::parse() {
    if (!rootNode.hasChild("camera")) {
        throw FileException
            ("Error: Missing camera configuration.");
    }
    if (!rootNode.hasChild("lights")) {
        throw(FileException
            ("Error: Missing lights configuration."));
    }
    if (!rootNode.hasChild("primitives")) {
        throw FileException
            ("Error: Missing primitives configuration.");
    }
    _objectConstructor.createObject(rootNode.children["camera"]);
    _objectConstructor.createObjects(rootNode.children["lights"]);
    _objectConstructor.createObjects(rootNode.children["primitives"]);
    if (rootNode.hasChild("importScenes")) {
        _objectConstructor.createObjects(rootNode.children["importScenes"]);
        importScene();
    }
    if (rootNode.hasChild("graphList")) {
        _objectConstructor.createObjects(rootNode.children["graphList"]);
    }
}

void Parser::importScene() {
    auto objetCpy = _objectConstructor.getObjects();
    for (const auto &object : objetCpy) {
        std::cout << "Importing scene..." << std::endl;
        if (object->find(TYPE) != object->end() &&
            std::get<ObjectType>((*object)[TYPE]) == TYPE_IMPORTED_SCENE) {
            std::string scenePath = std::get<std::string>((*object)[PATH]);
            if (!isValidFilePath(scenePath)) {
                std::cerr << "Error: Invalid or inaccessible file path: "
                << scenePath << std::endl;
                continue;
            }
            auto importedRootNode = std::make_shared<ConfigNode>();
            if (loadImportedScene(scenePath, importedRootNode)) {
                importObjectsFromScene(importedRootNode);
            } else {
                throw FileException
                    ("Failed to load imported scene: " + scenePath);
            }
        }
    }
}

bool Parser::isValidFilePath(const std::string &path) const {
    std::filesystem::path filePath(path);
    if (!std::filesystem::exists(filePath))
        return false;
    if (!std::filesystem::is_regular_file(filePath))
        return false;
    return true;
}

bool Parser::loadImportedScene
    (const std::string &scenePath,
    std::shared_ptr<ConfigNode> importedRootNode) const {
    ConfigParser tempParser;
    if (!tempParser.loadConfig(scenePath, *importedRootNode)) {
        return false;
    }
    return true;
}

void Parser::importObjectsFromScene
    (const std::shared_ptr<ConfigNode> importedRootNode) {
    if (importedRootNode->hasChild("primitives")) {
        _objectConstructor.createObjects
            (importedRootNode->children.at("primitives"));
    } else {
        std::cout << "No primitives found in imported scene." << std::endl;
    }

    if (importedRootNode->hasChild("lights")) {
        _objectConstructor.createObjects
            (importedRootNode->children.at("lights"));
    } else {
        std::cout << "No lights found in imported scene." << std::endl;
    }
}

void Parser::printMap() const {
    _objectConstructor.printObjectMap();
}
