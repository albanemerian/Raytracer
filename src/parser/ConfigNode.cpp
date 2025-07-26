/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** ConfigNode
*/

#include "ConfigNode.hpp"

#include <string>

bool ConfigNode::hasChild(const std::string &name) const {
    return children.find(name) != children.end();
}

