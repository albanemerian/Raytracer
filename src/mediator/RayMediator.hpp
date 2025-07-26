/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** RayMediator
*/

#ifndef RAYMEDIATOR_HPP_
#define RAYMEDIATOR_HPP_


#include <thread>
#include <functional>
#include <vector>
#include <mutex>
#include <condition_variable>

#include "IMediator.hpp"

class RayMediator : public IMediator {
    public:
        RayMediator();
        ~RayMediator();

        void addTask(std::function<void()> task) override;
        void executeTasks() override;
        void waitForCompletion() override;
        void killTask() override;

    private:
        std::vector<std::thread> _threads;
        std::vector<std::function<void()>> _tasks;
        std::mutex _mutex;
        std::condition_variable _condition;
        bool _stop = false;
};

#endif /* !RAYMEDIATOR_HPP_ */
