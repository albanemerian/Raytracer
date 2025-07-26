/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** RayMediator
*/

#include "RayMediator.hpp"
#include <iostream>
#include <functional>
#include <vector>
#include <thread>
#include <mutex>

RayMediator::RayMediator() {}

RayMediator::~RayMediator() {
    waitForCompletion();
}

void RayMediator::addTask(std::function<void()> task) {
    std::lock_guard<std::mutex> lock(_mutex);
    _tasks.push_back(task);
}

void RayMediator::executeTasks() {
    std::lock_guard<std::mutex> lock(_mutex);
    for (auto& task : _tasks) {
        _threads.emplace_back(task);
    }
    _tasks.clear();
}

void RayMediator::waitForCompletion() {
    for (auto& thread : _threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    _threads.clear();
}

void RayMediator::killTask() {
    std::lock_guard<std::mutex> lock(_mutex);
    _stop = true;
    for (auto& thread : _threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    _threads.clear();
}
