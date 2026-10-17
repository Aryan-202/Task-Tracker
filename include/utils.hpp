#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include "Task.hpp"

namespace Utils {
    std::filesystem::path getDbPath();
    void createFile();
    std::vector<Task> loadTasks();
    bool saveTasks(const std::vector<Task>& tasks);
    std::string getCurrentTimestamp();

    void createTask(int id, const std::string& title, const std::string& desc,
                    const std::string& priority = "Medium", const std::string& createdAt = "");
    bool getTask(int id, Task& outTask);
    bool updateTask(int id, const std::string& title, const std::string& desc,
                    const std::string& priority = "");
    bool deleteTask(int id);
    bool setTaskStatus(int id, bool isCompleted);

    bool createSubTask(int taskId, const std::string& title, const std::string& desc);
    bool updateSubTask(int taskId, int subTaskId, const std::string& title, const std::string& desc);
    bool deleteSubTask(int taskId, int subTaskId);
    bool setSubTaskStatus(int taskId, int subTaskId, bool isCompleted);

    void createSubTask(Task& parentTask, const std::string& title, const std::string& desc);
    void updateSubTask(Task& parentTask, int subTaskId, const std::string& title, const std::string& desc);
    void deleteSubTask(Task& parentTask, int subTaskId);

    int counter(int& id);
    int counter(int id);
}