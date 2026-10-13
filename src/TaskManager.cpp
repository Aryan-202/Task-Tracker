#include "TaskManager.hpp"
#include <iostream>

void TaskManager::addTask(const std::string& description) {
    tasks.push_back(Task(nextId++, description));
    std::cout << "Task added successfully!\n";
}

void TaskManager::listTasks() const {
    if (tasks.empty()) {
        std::cout << "No tasks found.\n";
        return;
    }
    
    std::cout << "\n--- Current Tasks ---\n";
    for (const auto& task : tasks) {
        std::cout << task.id << ". [" << (task.isCompleted ? "X" : " ") << "] " 
                  << task.description << "\n";
    }
}
