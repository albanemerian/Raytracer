#ifndef COLOREXCEPTION_HPP_
#define COLOREXCEPTION_HPP_

#include "AException.hpp"

class ColorException : public AException {
    public:
        ColorException(const std::string &message)
            : AException("ColorError", message) {}
};

#endif /* !COLOREXCEPTION_HPP_ */
