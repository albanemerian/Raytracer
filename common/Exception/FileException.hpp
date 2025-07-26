/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** FileConstructionExeption
*/

#ifndef FILECONSTRUCTIONEXEPTION_HPP_
#define FILECONSTRUCTIONEXEPTION_HPP_

#include "AException.hpp"

class FileException : public AException {
    public:
        FileException(const std::string& message)
            : AException("FileError", message) {};
    protected:
    private:
};

#endif /* !FILECONSTRUCTIONEXEPTION_HPP_ */
