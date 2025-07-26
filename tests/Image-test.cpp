/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Image-test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../common/Image.hpp"
#include "../common/Color.hpp"
#include "../common/Exception/FileException.hpp"

Test(Image, constructor) {
    Image image(1920, 1080, 255);

    cr_assert_eq(image.getWidth(), 1920, "Width is incorrect.");
    cr_assert_eq(image.getHeight(), 1080, "Height is incorrect.");
    cr_assert_eq(image.getMaxColorValue(), 255, "Max color value is incorrect.");
}

Test(Image, set_and_get_pixel) {
    Image image(10, 10, 255);
    Color red(255, 0, 0);

    image.setPixel(5, 5, red);
    Color retrievedColor = image.getPixel(5, 5);

    cr_assert_eq(retrievedColor.getRed(), 255, "Red value is incorrect.");
    cr_assert_eq(retrievedColor.getGreen(), 0, "Green value is incorrect.");
    cr_assert_eq(retrievedColor.getBlue(), 0, "Blue value is incorrect.");
}

Test(Image, set_pixel_out_of_bounds) {
    Image image(10, 10, 255);
    Color red(255, 0, 0);

    cr_assert_throw(image.setPixel(15, 15, red), FileException, "Out-of-bounds setPixel did not throw an exception.");
}

Test(Image, get_pixel_out_of_bounds) {
    Image image(10, 10, 255);

    cr_assert_throw(image.getPixel(15, 15), FileException, "Out-of-bounds getPixel did not throw an exception.");
    cr_assert(image.getWidth() == 10, "Width is incorrect.");
    cr_assert(image.getHeight() == 10, "Height is incorrect.");
    cr_assert(image.getMaxColorValue() == 255, "Max color value is incorrect.");
}

Test(Image, write_to_file_ppm) {
    Image image(10, 10, 255);
    Color red(255, 0, 0);

    image.setPixel(5, 5, red);

    image.writeToFilePPM("output.ppm");
}

Test(Image, write_to_file_invalid) {
    Image image(10, 10, 255);
    Color red(255, 0, 0);

    image.setPixel(5, 5, red);

    cr_assert_throw(image.writeToFilePPM("invalid_path/output.ppm"), FileException,
                    "Write to file did not throw an exception.");
}
