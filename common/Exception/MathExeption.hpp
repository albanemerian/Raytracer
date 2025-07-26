/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** MathExeption
*/

#ifndef MATHEXEPTION_HPP_
#define MATHEXEPTION_HPP_

#include "AException.hpp"

class MathExeption  : public AException {
    public:
        MathExeption(const std::string& message)
            : AException("MathError", message) {};

    protected:
    private:
};

#endif /* !MATHEXEPTION_HPP_ */
