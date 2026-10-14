#include "TaskManager.hpp"
#include "utils.hpp"
#include <iostream>

using namespace std;

void TaskManager::addTask(const std::string &title, const std::string &description)
{
    tasks.emplace_back(nextId++, title, description);
    cout << "Task added successfully!" << endl;
}

bool TaskManager::addSubTaskToTask(int taskId, const std::string &title, const std::string &description)
{
    for (auto &task : tasks)
    {
        if (task.id == taskId)
        {
            Utils::addSubTask(task, title, description);
            cout << "Subtask added successfully!" << endl;
            return true;
        }
    }
    cout << "Task with ID " << taskId << " not found." << endl;
    return false;
}

void TaskManager::listTasks() const
{
    if (tasks.empty())
    {
        cout << "No tasks found." << endl;
        return;
    }

    cout << "\n--- Current Tasks ---" << endl;
    for (const auto &task : tasks)
    {
        std::cout << task.id << ". [" << (task.isCompleted ? "X" : " ") << "] "
                  << task.title << " - " << task.description << endl;

        for (const auto &sub : task.subtasks)
        {
            std::cout << "    └── " << sub.id << ". [" << (sub.isCompleted ? "X" : " ") << "] "
                      << sub.title << " - " << sub.description << endl;
        }
    }
}
