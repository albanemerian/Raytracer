/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Helper-test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../src/utils/Utils.hpp"

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(Utils, helper_output, .init = redirect_all_stdout)
{
    Utils utils;
    utils.helper();
    cr_assert_stdout_eq_str(
        "USAGE :\n"
        "\t./raytracer <SCENE_FILE>\n"
        "OPTIONS :\n"
        "\t-h, --help\t\tDisplay this help message\n"
        "\t-g, Display the imahe in a sfml window\n"
        "\t-n + \"file_name\"\t\tSpecify the name output file\n"
        "\t-f Specify format of the output : jpg, jpeg, png, bmp\n"
        "\t-d display debugs of the element\n"
        "SCENE_FILE :\n"
        " The scene files needs to be properlly formatted."
        " The exentsion of the file needs to be .cfg\n"
        "If no output file name is specified,"
        " the default name is \"output\" and format : .ppm\n"
    );
    utils.~Utils();
}

