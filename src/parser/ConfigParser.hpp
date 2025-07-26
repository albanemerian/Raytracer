/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** ConfigParser
*/

#ifndef CONFIGPARSER_HPP_
#define CONFIGPARSER_HPP_

#include <libconfig.h++>
#include <string>
#include <memory>

#include "ConfigNode.hpp"

using namespace libconfig;

class ConfigParser {
 public:
    ConfigParser();
    ~ConfigParser();
    bool loadConfig(const std::string &filename, ConfigNode &rootNode);

 protected:
    void buildConfigTree(const Setting &setting, std::shared_ptr<ConfigNode> node);

 private:
    void handleGroupType(const Setting &child, const std::string &childName,
                         std::shared_ptr<ConfigNode> node);
    void handleArrayType(const Setting &child, const std::string &childName,
                         std::shared_ptr<ConfigNode> node);
    void handleListType(const Setting &child, const std::string &childName,
                        std::shared_ptr<ConfigNode> node);
    void handleValueType(const Setting &child, const std::string &childName,
                         std::shared_ptr<ConfigNode> node);

    Config file;
};

#endif /* !CONFIGPARSER_HPP_ */