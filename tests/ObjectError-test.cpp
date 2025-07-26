/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** ObjectError-test
*/


#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../src/parser/ObjectErrorHandling.hpp"
#include "../src/parser/ConfigNode.hpp"
#include "../common/Exception/FileException.hpp"


void redirect_all_stdout_error(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(ObjectErrorHandling, checkArrayValidity, .init = redirect_all_stdout_error) {
    ObjectErrorHandling errorHandler;
    ConfigNode node;
}

Test(ObjectErrorHandling, checkArrayValidity_validArray, .init = redirect_all_stdout_error) {
    ObjectErrorHandling errorHandler;
    ConfigNode node;
    node.type = TypeArray;

    ConfigNode child1;
    child1.type = TypeValue;
    child1.isValue = true;
    child1.value = ValueType(42);

    ConfigNode child2;
    child2.type = TypeValue;
    child2.isValue = true;
    child2.value = ValueType(3.14f);

    node.children["child1"] = child1;
    node.children["child2"] = child2;

    cr_assert(errorHandler.checkArrayValidity(node, "TestObject"));
}

Test(ObjectErrorHandling, checkArrayValidity_invalidArray, .init = redirect_all_stdout_error) {
    ObjectErrorHandling errorHandler;
    ConfigNode node;
    node.type = TypeGroup;

    cr_assert_not(errorHandler.checkArrayValidity(node, "TestObject"));
}

Test(ObjectErrorHandling, checkGroupValidity_validGroup, .init = redirect_all_stdout_error) {
    ObjectErrorHandling errorHandler;
    ConfigNode node;
    node.type = TypeGroup;

    ConfigNode mandatoryParam;
    mandatoryParam.type = TypeValue;
    mandatoryParam.isValue = true;
    mandatoryParam.value = ValueType(42);

    node.children["mandatoryParam"] = mandatoryParam;

    std::vector<ShapeDefinition> shapes = {
        {"TestObject", {"mandatoryParam"}, {"optionalParam"}}
    };
    errorHandler.setShapeDefinitions(shapes);

    cr_assert_any_throw(errorHandler.checkGroupValidity(node, "TestObject"));
}

Test(ObjectErrorHandling, checkGroupValidity_missingMandatory, .init = redirect_all_stdout_error) {
    ObjectErrorHandling errorHandler;
    ConfigNode node;
    node.type = TypeGroup;

    std::vector<ShapeDefinition> shapes = {
        {"TestObject", {"mandatoryParam"}, {"optionalParam"}}
    };
    errorHandler.setShapeDefinitions(shapes);

    cr_assert_any_throw(errorHandler.checkGroupValidity(node, "TestObject"));
}

Test(ObjectErrorHandling, checkValueValidity_validValue, .init = redirect_all_stdout_error) {
    ObjectErrorHandling errorHandler;
    ConfigNode node;
    node.type = TypeValue;
    node.isValue = true;
    node.value = ValueType(42);

    cr_assert(errorHandler.checkValueValidity(node, "TestObject"));
}

Test(ObjectErrorHandling, checkValueValidity_invalidValue, .init = redirect_all_stdout_error) {
    ObjectErrorHandling errorHandler;
    ConfigNode node;
    node.type = TypeGroup;

    cr_assert_throw(errorHandler.checkValueValidity(node, "TestObject"), FileException);
}

Test(ObjectErrorHandling, verifyObjectValidity_array, .init = redirect_all_stdout_error) {
    ObjectErrorHandling errorHandler;
    ConfigNode node;
    node.type = TypeArray;

    ConfigNode child1;
    child1.type = TypeValue;
    child1.isValue = true;
    child1.value = ValueType(42);

    node.children["child1"] = child1;

    cr_assert(errorHandler.verifyObjectValidity(node, "TestObject"));
}

Test(ObjectErrorHandling, verifyObjectValidity_invalidType, .init = redirect_all_stdout_error) {
    ObjectErrorHandling errorHandler;
    ConfigNode node;
    node.type = static_cast<NodeType>(999);

    cr_assert_not(errorHandler.verifyObjectValidity(node, "TestObject"));
}
