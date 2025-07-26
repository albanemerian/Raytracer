/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** materialLoaderException
*/

#ifndef MATERIALLOADEREXCEPTION_HPP_
#define MATERIALLOADEREXCEPTION_HPP_

#include "AException.hpp"

class MaterialLoaderException : public AException {
    public:
        MaterialLoaderException(const std::string& message)
            : AException("MaterialLoaderError", message) {};
    protected:
    private:
};

#endif /* !MATERIALLOADEREXCEPTION_HPP_ */
