#include "TaskManager.hpp"
#include "utils.hpp"
#include <iostream>

void TaskManager::addTask(const std::string& title, const std::string& description) {
    tasks.emplace_back(nextId++, title, description);
    std::cout << "Task added successfully!\n";
}

bool TaskManager::addSubTaskToTask(int taskId, const std::string& title, const std::string& description) {
    for (auto& task : tasks) {
        if (task.id == taskId) {
            // Using your helper function here:
            Utils::addSubTask(task, title, description);
            std::cout << "Subtask added successfully!\n";
            return true;
        }
    }
    std::cout << "Task with ID " << taskId << " not found.\n";
    return false;
}

void TaskManager::listTasks() const {
    if (tasks.empty()) {
        std::cout << "No tasks found.\n";
        return;
    }
    
    std::cout << "\n--- Current Tasks ---\n";
    for (const auto& task : tasks) {
        std::cout << task.id << ". [" << (task.isCompleted ? "X" : " ") << "] " 
                  << task.title << " - " << task.description << "\n";
        
        for (const auto& sub : task.subtasks) {
            std::cout << "    └── " << sub.id << ". [" << (sub.isCompleted ? "X" : " ") << "] " 
                      << sub.title << " - " << sub.description << "\n";
        }
    }
}