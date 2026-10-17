#pragma once
#include "SubTask.hpp"
#include <string>
#include <vector>

struct Task
{
    int id = 0;
    std::string title;
    std::string description;
    bool isCompleted = false;
    std::string priority = "Medium";
    std::string createdAt;
    std::vector<SubTask> subtasks;
    int nextSubTaskId = 1;

    Task() = default;
    Task(int taskId, const std::string& title, const std::string& desc,
         bool completed = false, const std::string& priority = "Medium",
         const std::string& createdAt = "");

    int getCompletedSubtasksCount() const;
    int getTotalSubtasksCount() const;
};