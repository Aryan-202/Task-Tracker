#include "utils.hpp"
#include "Task.hpp"

namespace Utils {
    void addSubTask(Task& parentTask, const std::string& title, const std::string& desc) {
        parentTask.subtasks.emplace_back(parentTask.nextSubTaskId++, title, desc);
    }
}