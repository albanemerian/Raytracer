/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** ConfigParser-test
*/

#include <criterion/criterion.h>
#include "../src/parser/ConfigParser.hpp"
#include "../src/parser/ConfigNode.hpp"
#include "../src/parser/ValueConverter.hpp"

Test(ConfigParser, loadConfig) {
    ConfigParser parser;
    ConfigNode rootNode;

    cr_assert(parser.loadConfig("ressouces/cone.cfg", rootNode), "Failed to load config file.");
    rootNode.children.size();
    rootNode.children["camera"].type;
    rootNode.children["lights"].type;
    rootNode.children["objects"].type;
}
