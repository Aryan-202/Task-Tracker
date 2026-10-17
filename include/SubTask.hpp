#pragma once
#include <string>

struct SubTask
{
    int id = 0;
    std::string title;
    std::string description;
    bool isCompleted = false;
    std::string createdAt;

    SubTask() = default;
    SubTask(int subTaskId, const std::string& title, const std::string& desc, bool completed = false, const std::string& createdAt = "");
};