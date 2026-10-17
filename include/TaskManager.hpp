#pragma once
#include "Task.hpp"
#include <vector>
#include <string>

class TaskManager
{
private:
    std::vector<Task> tasks;
    int nextId = 1;

    void updateNextIds();

public:
    TaskManager();

    // Disk persistence
    void loadFromDisk();
    void saveToDisk() const;

    // Task CRUD operations
    int createTask(const std::string& title, const std::string& description, const std::string& priority = "Medium");
    bool updateTask(int taskId, const std::string& title, const std::string& description, const std::string& priority = "");
    bool deleteTask(int taskId);
    bool toggleTaskStatus(int taskId);
    bool setTaskStatus(int taskId, bool isCompleted);

    // SubTask CRUD operations
    bool addSubTaskToTask(int taskId, const std::string& title, const std::string& description);
    bool updateSubTask(int taskId, int subTaskId, const std::string& title, const std::string& description);
    bool deleteSubTask(int taskId, int subTaskId);
    bool toggleSubTaskStatus(int taskId, int subTaskId);
    bool setSubTaskStatus(int taskId, int subTaskId, bool isCompleted);

    // Lookups & Getters
    const Task* getTaskById(int taskId) const;
    Task* getTaskById(int taskId);
    const std::vector<Task>& getAllTasks() const;
    size_t getTaskCount() const;

    // Display & Analysis
    void listTasks(int filter = 0) const; // 0: All, 1: Pending, 2: Completed, 3: High Priority
    void viewTaskDetails(int taskId) const;
    void searchTasks(const std::string& keyword) const;
    void displayStatistics() const;
};
