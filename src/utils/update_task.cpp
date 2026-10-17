#include "Utils.hpp"
#include "Task.hpp"
#include "SubTask.hpp"
#include <vector>
#include <string>

namespace Utils {

    bool updateTask(int id, const std::string& title, const std::string& desc, const std::string& priority) {
        std::vector<Task> tasks = loadTasks();
        for (auto& task : tasks) {
            if (task.id == id) {
                if (!title.empty()) task.title = title;
                if (!desc.empty()) task.description = desc;
                if (!priority.empty()) task.priority = priority;
                return saveTasks(tasks);
            }
        }
        return false;
    }

    bool setTaskStatus(int id, bool isCompleted) {
        std::vector<Task> tasks = loadTasks();
        for (auto& task : tasks) {
            if (task.id == id) {
                task.isCompleted = isCompleted;
                return saveTasks(tasks);
            }
        }
        return false;
    }

    bool updateSubTask(int taskId, int subTaskId, const std::string& title, const std::string& desc) {
        std::vector<Task> tasks = loadTasks();
        for (auto& task : tasks) {
            if (task.id == taskId) {
                for (auto& sub : task.subtasks) {
                    if (sub.id == subTaskId) {
                        if (!title.empty()) sub.title = title;
                        if (!desc.empty()) sub.description = desc;
                        return saveTasks(tasks);
                    }
                }
                return false;
            }
        }
        return false;
    }

    bool setSubTaskStatus(int taskId, int subTaskId, bool isCompleted) {
        std::vector<Task> tasks = loadTasks();
        for (auto& task : tasks) {
            if (task.id == taskId) {
                for (auto& sub : task.subtasks) {
                    if (sub.id == subTaskId) {
                        sub.isCompleted = isCompleted;
                        return saveTasks(tasks);
                    }
                }
                return false;
            }
        }
        return false;
    }

    void updateSubTask(Task& parentTask, int subTaskId, const std::string& title, const std::string& desc) {
        for (auto& sub : parentTask.subtasks) {
            if (sub.id == subTaskId) {
                if (!title.empty()) sub.title = title;
                if (!desc.empty()) sub.description = desc;
                break;
            }
        }
    }
}
