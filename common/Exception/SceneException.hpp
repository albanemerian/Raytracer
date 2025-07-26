/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** SceneException
*/

#ifndef SCENEEXCEPTION_HPP_
#define SCENEEXCEPTION_HPP_

#include "AException.hpp"

class SceneException : public AException {
    public:
        SceneException(const std::string &message)
            : AException("SceneError", message) {}

    protected:
    private:
};

#endif /* !SCENEEXCEPTION_HPP_ */
