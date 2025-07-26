/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** ConfigParser
*/

#include "ConfigParser.hpp"

#include <iostream>
#include <string>
#include <memory>

ConfigParser::ConfigParser() {}

ConfigParser::~ConfigParser() {}

bool ConfigParser::loadConfig(const std::string &filename, ConfigNode &rootN) {
    try {
        file.readFile(filename.c_str());
        const Setting &root = file.getRoot();
        auto nodePtr = std::make_shared<ConfigNode>(rootN);
        buildConfigTree(root, nodePtr);
        rootN = *nodePtr;
        return true;
    } catch (const FileIOException &fioex) {
        std::cout << "I/O error while reading file: " << filename << std::endl;
        exit(84);
    } catch (const ConfigException &cfgex) {
        std::cout << "Error configuration file: " << cfgex.what() << std::endl;
        exit(84);
    }
}

void ConfigParser::buildConfigTree(const Setting &setting,
                                   std::shared_ptr<ConfigNode> node) {
    int count = setting.getLength();

    if (setting.isGroup())
        node->type = TypeGroup;
    else if (setting.isArray())
        node->type = TypeArray;
    for (int i = 0; i < count; ++i) {
        const Setting &child = setting[i];
        std::string childName =
            child.getName() ? child.getName() : "[" + std::to_string(i) + "]";
        Setting::Type type = child.getType();
        if (type == Setting::TypeGroup) {
            handleGroupType(child, childName, node);
        } else if (type == Setting::TypeArray) {
            handleArrayType(child, childName, node);
        } else if (type == Setting::TypeList) {
            handleListType(child, childName, node);
        } else {
            handleValueType(child, childName, node);
        }
    }
}

void ConfigParser::handleGroupType(const Setting &child,
                                   const std::string &childName,
                                   std::shared_ptr<ConfigNode> node) {
    auto groupNode = std::make_shared<ConfigNode>();
    groupNode->type = TypeGroup;
    groupNode->_name = childName;
    buildConfigTree(child, groupNode);
    node->children[childName] = *groupNode;
}

void ConfigParser::handleArrayType(const Setting &child,
                                   const std::string &childName,
                                   std::shared_ptr<ConfigNode> node) {
    auto arrayNode = std::make_shared<ConfigNode>();
    arrayNode->type = TypeArray;
    arrayNode->_name = childName;
    buildConfigTree(child, arrayNode);
    node->children[childName] = *arrayNode;
}

void ConfigParser::handleListType(const Setting &child,
                                  const std::string &childName,
                                  std::shared_ptr<ConfigNode> node) {
    auto arrayNode = std::make_shared<ConfigNode>();
    arrayNode->type = TypeArray;
    arrayNode->_name = childName;
    for (int j = 0; j < child.getLength(); ++j) {
        const Setting &listItem = child[j];
        std::string itemName = "[" + std::to_string(j) + "]";
        if (listItem.isGroup()) {
            auto itemNode = std::make_shared<ConfigNode>();
            itemNode->type = TypeGroup;
            itemNode->_name = itemName;
            buildConfigTree(listItem, itemNode);
            arrayNode->children[itemName] = *itemNode;
        } else if (listItem.isArray()) {
            auto itemNode = std::make_shared<ConfigNode>();
            itemNode->type = TypeArray;
            itemNode->_name = itemName;
            buildConfigTree(listItem, itemNode);
            arrayNode->children[itemName] = *itemNode;
        }
    }
    node->children[childName] = *arrayNode;
}

void ConfigParser::handleValueType(const Setting &child,
                                   const std::string &childName,
                                   std::shared_ptr<ConfigNode> node) {
    auto valueNode = std::make_shared<ConfigNode>();
    valueNode->isValue = true;
    valueNode->type = TypeValue;
    valueNode->_name = childName;

    Setting::Type valueType = child.getType();
    switch (valueType) {
        case Setting::TypeInt:
            valueNode->value = static_cast<int>(child);
            break;
        case Setting::TypeFloat:
            valueNode->value = static_cast<float>(child);
            break;
        case Setting::TypeString:
            valueNode->value = std::string(static_cast<const char *>(child));
            break;
        case Setting::TypeBoolean:
            valueNode->value = static_cast<bool>(child);
            break;
        default:
            valueNode->value = 0;
            break;
    }
    node->children[childName] = *valueNode;
}
