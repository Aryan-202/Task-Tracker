#include "SubTask.hpp"

SubTask::SubTask(int subTaskId, const std::string& title, const std::string& desc)
    :id(subTaskId), title(title), description(desc), isCompleted(false) {}