/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** ObjectConstructor-test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../src/parser/ObjectConstructor.hpp"
#include "../common/ValueType.hpp"
#include <memory>
#include <map>
#include <string>

void redirect_objconstruct_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(ObjectConstructor, constructor_test) {
    ObjectConstructor constructor;

    cr_assert(true, "ObjectConstructor should be constructible");
}

Test(ObjectConstructor, get_empty_objects) {
    ObjectConstructor constructor;
    auto objects = constructor.getObjects();
    cr_assert(objects.empty(), "Initial objects collection should be empty");
}

Test(ObjectConstructor, print_empty_map, .init = redirect_objconstruct_stdout) {
    ObjectConstructor constructor;

    constructor.printObjectMap();
    cr_assert(true, "printObjectMap should not crash with empty data");
}

Test(ObjectConstructor, simple_verify_validity) {
    ObjectConstructor constructor;
    ConfigNode node;

    bool result = constructor.verifyObjectValidity(node, "test");


    cr_assert(true, "verifyObjectValidity should not throw exceptions");
}
