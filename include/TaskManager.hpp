#pragma once
#include "Task.hpp"
#include <vector>
#include <string>

class TaskManager
{
private:
    std::vector<Task> tasks;
    int nextId = 1;
public:
    void addTask(const std::string& title, const std::string& description);
    bool addSubTaskToTask(int taskId, const std::string& title, const std::string& description);
    void listTasks() const;
};
