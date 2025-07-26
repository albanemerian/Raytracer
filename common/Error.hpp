/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <exception>
#include <iostream>
#include <string>

class Error : public std::exception {
 public:
    Error(const std::string &msg, const std::string &file, int line)
        : _message(msg), _file(file), _line(line) {
        ErrorFaillureException();
    }

    ~Error() noexcept override = default;

    const char *what() const noexcept override { return _message.c_str(); }

    const char *where() const noexcept { return _file.c_str(); }

    int line() const noexcept { return _line; }

    void ErrorFaillureException() const {
        std::cerr << "Error: " << what() << " in file: " << where()
                  << " at line: " << line() << std::endl;
        exit(84);
    }
    void exitCode(int code) { exit(code); }

 private:
    std::string _message;
    std::string _file;
    int _line;
};

#endif /* !ERROR_HPP_ */
