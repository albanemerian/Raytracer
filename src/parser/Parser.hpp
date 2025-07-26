/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <memory>
#include <string>
#include <vector>
#include <filesystem>
#include "ConfigParser.hpp"
#include "ObjectConstructor.hpp"

class Parser {
 public:
    Parser();
    Parser(const std::string &filename);
    ~Parser();
    void loadConfig(const std::string &filename);
    void parse();
    const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>
        &getObjects() const;
    std::shared_ptr<ConfigNode> getRootNode() { return std::make_shared<ConfigNode>(rootNode); }

    void printMap() const;
 private:
    void importScene();
    bool isValidFilePath(const std::string &path) const;
    bool loadImportedScene(const std::string &scenePath, std::shared_ptr<ConfigNode> importedRootNode) const;
    void importObjectsFromScene(const std::shared_ptr<ConfigNode> importedRootNode);

    ConfigNode rootNode;
    ConfigParser configParser;
    ObjectConstructor _objectConstructor;
};

#endif /* !PARSER_HPP_ */
