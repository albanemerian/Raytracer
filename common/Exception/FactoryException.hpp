/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** FactoryException
*/

#ifndef FACTORYEXCEPTION_HPP_
#define FACTORYEXCEPTION_HPP_

#include "AException.hpp"

class FactoryException : public AException {
    public:
        FactoryException(const std::string& message)
                : AException("FactoryError", message) {};
    protected:
    private:
};

#endif /* !FACTORYEXCEPTION_HPP_ */
