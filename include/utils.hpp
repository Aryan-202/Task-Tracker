#pragma once
#include <string>

struct Task;

namespace Utils {
    void addSubTask(Task& parentTask, const std::string& title, const std::string& desc);
}