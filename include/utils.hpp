#pragma once
#include <string>
#include <filesystem>

struct Task;

namespace Utils {
    std::filesystem::path getDbPath();

    void createTask(int id, const std::string& title, const std::string& desc);
    void getTask(int id, const std::string& title, const std::string& desc);
    void updateTask(int id, const std::string& title, const std::string& desc);
    void deleteTask(int id, const std::string& title, const std::string& desc);

    void createSubTask(Task& parentTask, const std::string& title, const std::string& desc);
    void getSubTask(Task& parentTask, const std::string& title, const std::string& desc);
    void updataSubTask(Task& parentTask, const std::string& title, const std::string& desc);
    void deleteSubTask(Task& parentTask, const std::string& title, const std::string& desc);

    int counter(int id);
}