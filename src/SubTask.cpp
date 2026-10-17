#include "SubTask.hpp"

SubTask::SubTask(int subTaskId, const std::string& title, const std::string& desc, bool completed, const std::string& createdAt)
    : id(subTaskId), title(title), description(desc), isCompleted(completed), createdAt(createdAt) {}