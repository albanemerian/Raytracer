/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** RayMediator-test
*/

#include <criterion/criterion.h>
#include <atomic>
#include <chrono>
#include "../src/mediator/RayMediator.hpp"

Test(RayMediator, constructor_destructor) {
    RayMediator* mediator = new RayMediator();
    delete mediator;
}

Test(RayMediator, add_task_and_execute) {
    RayMediator mediator;
    std::atomic<int> counter{0};
    mediator.addTask([&counter]() {
        counter++;
    });
    mediator.addTask([&counter]() {
        counter++;
    });
    mediator.executeTasks();
    mediator.waitForCompletion();
    cr_assert_eq(counter, 2);
}

Test(RayMediator, multiple_execute_calls) {
    RayMediator mediator;
    std::atomic<int> counter{0};
    mediator.addTask([&counter]() {
        counter++;
    });
    mediator.executeTasks();
    mediator.addTask([&counter]() {
        counter++;
    });
    mediator.executeTasks();
    mediator.waitForCompletion();
    cr_assert_eq(counter, 2);
}

Test(RayMediator, task_execution_parallelism) {
    RayMediator mediator;
    std::atomic<bool> task1Started{false};
    std::atomic<bool> task2Started{false};
    std::atomic<bool> task1Completed{false};
    std::atomic<bool> task2Completed{false};
    mediator.addTask([&task1Started, &task1Completed]() {
        task1Started = true;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        task1Completed = true;
    });
    mediator.addTask([&task2Started, &task2Completed]() {
        task2Started = true;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        task2Completed = true;
    });
    mediator.executeTasks();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    cr_assert(task1Started && task2Started, "Tasks should start in parallel");
    cr_assert(!task1Completed || !task2Completed, "At least one task should still be running");
    mediator.waitForCompletion();
    cr_assert(task1Completed && task2Completed, "All tasks should be completed after waiting");
}
