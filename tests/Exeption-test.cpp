/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Exeption-test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../common/Exception/SceneException.hpp"
#include "../common/Exception/MathExeption.hpp"
#include "../common/Exception/materialLoaderException.hpp"
#include "../common/Exception/FileException.hpp"
#include "../common/Exception/FactoryException.hpp"
#include "../common/Exception/CommandException.hpp"
#include "../common/Exception/ColorException.hpp"

Test(SceneException, test_message_and_type) {
    SceneException ex("Scene error occurred");
    cr_assert_eq(ex.getType(), "SceneError");
    cr_assert_eq(ex.getMessage(), "Scene error occurred");
    cr_assert_eq(ex.getFormattedMessage(), "[SceneError] Scene error occurred");
}

Test(MathExeption, test_message_and_type) {
    MathExeption ex("Math error occurred");
    cr_assert_eq(ex.getType(), "MathError");
    cr_assert_eq(ex.getMessage(), "Math error occurred");
    cr_assert_eq(ex.getFormattedMessage(), "[MathError] Math error occurred");
}

Test(MaterialLoaderException, test_message_and_type) {
    MaterialLoaderException ex("Material loader error occurred");
    cr_assert_eq(ex.getType(), "MaterialLoaderError");
    cr_assert_eq(ex.getMessage(), "Material loader error occurred");
    cr_assert_eq(ex.getFormattedMessage(), "[MaterialLoaderError] Material loader error occurred");
}

Test(FileException, test_message_and_type) {
    FileException ex("File error occurred");
    cr_assert_eq(ex.getType(), "FileError");
    cr_assert_eq(ex.getMessage(), "File error occurred");
    cr_assert_eq(ex.getFormattedMessage(), "[FileError] File error occurred");
}

Test(FactoryException, test_message_and_type) {
    FactoryException ex("Factory error occurred");
    cr_assert_eq(ex.getType(), "FactoryError");
    cr_assert_eq(ex.getMessage(), "Factory error occurred");
    cr_assert_eq(ex.getFormattedMessage(), "[FactoryError] Factory error occurred");
}

Test(CommandException, test_message_and_type) {
    CommandException ex("Command error occurred");
    cr_assert_eq(ex.getType(), "CommandError");
    cr_assert_eq(ex.getMessage(), "Command error occurred");
    cr_assert_eq(ex.getFormattedMessage(), "[CommandError] Command error occurred");
}

Test(ColorException, test_message_and_type) {
    ColorException ex("Color error occurred");
    cr_assert_eq(ex.getType(), "ColorError");
    cr_assert_eq(ex.getMessage(), "Color error occurred");
    cr_assert_eq(ex.getFormattedMessage(), "[ColorError] Color error occurred");
}

Test(AException, test_what_method) {
    AException ex("TestError", "This is a test error");
    std::string formattedMessage(ex.what());
}
