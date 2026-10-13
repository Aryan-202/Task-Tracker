#pragma once
#include <string>

struct Task
{
    int id;
    std::string description;
    bool isCompleted;

    Task(int taskId, const std::string& desc);
};
