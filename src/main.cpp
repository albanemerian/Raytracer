/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** main
*/

#include <iostream>

#include "../common/Error.hpp"
#include "Raytracer.hpp"
#include "../common/Exception/IException.hpp"
#include "parser/Parser.hpp"



int main(int ac, char **av) {
    Raytracer r;

    try {
        r.parseCmd(ac, av);
        Parser parser(r.getSceneFile());
        parser.getObjects();

        r.LoadAllformlibs(parser.getObjects());

        if (r.isDebug() == true)
            parser.printMap();
        r.StartImage();
    } catch (IException &e) {
        std::cerr << e.getFormattedMessage() << std::endl;
        return 84;
    } catch (std::exception &e) {
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
        return 84;
    }
    return 0;
}
