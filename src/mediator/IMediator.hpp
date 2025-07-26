/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** IMediator
*/

#ifndef IMEDIATOR_HPP_
#define IMEDIATOR_HPP_

#include <functional>

class IMediator {
    public:
        virtual void addTask(std::function<void()> task) = 0;
        virtual void executeTasks() = 0;
        virtual void waitForCompletion() = 0;
        virtual void killTask() = 0;
    protected:
    private:
};

#endif /* !IMEDIATOR_HPP_ */
