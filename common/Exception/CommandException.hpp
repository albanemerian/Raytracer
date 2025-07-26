/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** CommandException
*/

#ifndef COMMANDEXCEPTION_HPP_
#define COMMANDEXCEPTION_HPP_

#include "AException.hpp"

class CommandException : public AException {
    public:
        CommandException(const std::string& message)
            : AException("CommandError", message) {};
    protected:
    private:
};

#endif /* !COMMANDEXCEPTION_HPP_ */
