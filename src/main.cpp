#include "TaskManager.hpp"
#include <iostream>
#include <string>

int main() {
    TaskManager manager;
    int choice = 0;

    while (choice != 4) {
        std::cout << "\n=== Task Tracker ===\n";
        std::cout << "1. Create Task\n";
        std::cout << "2. Add Subtask\n";
        std::cout << "3. List Tasks\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            std::string title, description;
            std::cout << "Enter task title: ";
            std::getline(std::cin, title);
            std::cout << "Enter task description: ";
            std::getline(std::cin, description);
            std::cout << "TODO: implementation of the task";
        } 
        else if (choice == 2) {
            int taskId;
            std::string title, description;
            std::cout << "Enter parent Task ID: ";
            std::cin >> taskId;
            std::cin.ignore();
            std::cout << "Enter subtask title: ";
            std::getline(std::cin, title);
            std::cout << "Enter subtask description: ";
            std::getline(std::cin, description);
            manager.addSubTaskToTask(taskId, title, description);
        }
        else if (choice == 3) {
            manager.listTasks();
        }
    }

    return 0;
}
