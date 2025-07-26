/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** ConfigNode-test
*/

#include <criterion/criterion.h>
#include "../src/parser/ConfigNode.hpp"

Test(ConfigNodeTest, DefaultConstructor) {
    ConfigNode node;

    cr_assert_eq(node.isValue, false);
    cr_assert_eq(node.type, TypeUnknown);
    cr_assert_eq(node._name, "");
}

Test(ConfigNodeTest, HasChild) {
    ConfigNode node;
    ConfigNode childNode;
    node.children["child"] = childNode;

    cr_assert_eq(node.hasChild("child"), true);
    cr_assert_eq(node.hasChild("nonexistent"), false);
}

Test(ConfigNodeTest, GetValue) {
    ConfigNode node;
    node.isValue = true;
    node.value = 42;
}
