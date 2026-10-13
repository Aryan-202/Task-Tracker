#pragma once
#include <string>

struct SubTask
{
    int id;
    std::string title;
    std::string description;
    bool isCompleted;

    SubTask(int subTaskId, const std::string& title, const std::string& desc);
};