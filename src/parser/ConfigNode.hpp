/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** ConfigNode
*/

#ifndef CONFIGNODE_HPP_
#define CONFIGNODE_HPP_

#include <iostream>
#include <map>
#include <variant>

#include "../../common/ValueType.hpp"

enum NodeType { TypeUnknown, TypeGroup, TypeArray, TypeValue, TypeList };

class ConfigNode {
 public:
    ConfigNode() : isValue(false), type(TypeUnknown), _name("") {}
    ~ConfigNode() = default;

        std::map<std::string, ConfigNode> children;
        ValueType value;
        bool isValue;
        NodeType type;
        std::string _name;

    bool hasChild(const std::string &name) const;
   // template <typename T>
    //T getValue(const T &defaultValue = T()) const;
};

#endif /* !CONFIGNODE_HPP_ */
