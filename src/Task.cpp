#include "Task.hpp"

Task::Task(int taskId, const std::string &title, const std::string &desc)
    : id(taskId), title(title), description(desc), isCompleted(false) {}