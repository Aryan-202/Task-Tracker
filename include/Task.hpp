#pragma once
#include "SubTask.hpp"
#include <string>
#include <vector>

struct Task
{
    int id;
    std::string title;
    std::string description;
    bool isCompleted;
    std::vector<SubTask> subtasks;
    int nextSubTaskId = 1;

    Task(int taskId, const std::string& title, const std::string& desc);
};