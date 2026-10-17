#include "Task.hpp"

Task::Task(int taskId, const std::string& title, const std::string& desc,
           bool completed, const std::string& priority, const std::string& createdAt)
    : id(taskId), title(title), description(desc), isCompleted(completed),
      priority(priority), createdAt(createdAt), nextSubTaskId(1) {}

int Task::getCompletedSubtasksCount() const {
    int count = 0;
    for (const auto& sub : subtasks) {
        if (sub.isCompleted) {
            count++;
        }
    }
    return count;
}

int Task::getTotalSubtasksCount() const {
    return static_cast<int>(subtasks.size());
}