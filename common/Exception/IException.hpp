/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** IExeption
*/

#ifndef IEXEPTION_HPP_
#define IEXEPTION_HPP_

#include <exception>
#include <string>


class IException : public std::exception {
    public:
        virtual ~IException() noexcept = default;
        const char* what() const noexcept override = 0;
        virtual std::string getType() const noexcept = 0;
        virtual std::string getMessage() const noexcept = 0;
        virtual std::string getFormattedMessage() const noexcept = 0;
};

#endif /* !IEXEPTION_HPP_ */
