#pragma once 
#include "Task.hpp"
#include <vector>

class TaskManager
{
private:
    std::vector<Task> tasks;
    int nextId = 1;
public:
    void addTask(const std::string& description);
    void listTasks() const;
};
