#include "TaskManager.hpp"
#include <iostream>
#include <string>

int main() {
    TaskManager manager;
    int choice = 0;

    while (choice != 3) {
        std::cout << "\n=== Task Tracker ===\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. List Tasks\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        // Clear input buffer to prepare for text descriptions
        std::cin.ignore();

        if (choice == 1) {
            std::string description;
            std::cout << "Enter task description: ";
            std::getline(std::cin, description);
            manager.addTask(description);
        } 
        else if (choice == 2) {
            manager.listTasks();
        }
    }

    return 0;
}
