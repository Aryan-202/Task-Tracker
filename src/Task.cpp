#include "Task.hpp"

Task::Task(int taskId, const std::string& desc)
    : id(taskId), description(desc), isCompleted(false) {}