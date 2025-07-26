/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Raytracer-test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../src/Raytracer.hpp"

void redirect_raytracer_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(Raytracer, constructor, .init = redirect_raytracer_stdout) {
    Raytracer raytracer;
    cr_assert_eq(raytracer.getSceneFile(), "", "Default scene file should be empty.");
    cr_assert_eq(raytracer.getOutputFile(), "", "Default output file should be empty.");
    cr_assert_eq(raytracer.getOutputFormat(), "", "Default output format should be empty.");
    cr_assert_eq(raytracer.getImage(), nullptr, "Default image should be null.");
    cr_assert_eq(raytracer.getGraphicMode(), false, "Default graphic mode should be false.");
}

Test(Raytracer, setters_and_getters, .init = redirect_raytracer_stdout) {
    Raytracer raytracer;

    raytracer.setSceneFile("test.cfg");
    raytracer.setOutputFile("output.ppm");
    raytracer.setOutputFormat("ppm");

    cr_assert_eq(raytracer.getSceneFile(), "test.cfg", "Scene file should be 'test.cfg'.");
    cr_assert_eq(raytracer.getOutputFile(), "output.ppm", "Output file should be 'output.ppm'.");
    cr_assert_eq(raytracer.getOutputFormat(), "ppm", "Output format should be 'ppm'.");
}

