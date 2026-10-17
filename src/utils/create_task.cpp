#include "Utils.hpp"
#include "Task.hpp"
#include "SubTask.hpp"
#include <string>
#include <vector>

namespace Utils {

    void createTask(int id, const std::string& title, const std::string& desc,
                    const std::string& priority, const std::string& createdAt) {
        std::vector<Task> tasks = loadTasks();

        std::string actualCreated = createdAt.empty() ? getCurrentTimestamp() : createdAt;
        std::string actualPriority = priority.empty() ? "Medium" : priority;

        tasks.emplace_back(id, title, desc, false, actualPriority, actualCreated);
        saveTasks(tasks);
    }

    bool createSubTask(int taskId, const std::string& title, const std::string& desc) {
        std::vector<Task> tasks = loadTasks();
        for (auto& task : tasks) {
            if (task.id == taskId) {
                int subId = task.nextSubTaskId++;
                task.subtasks.emplace_back(subId, title, desc, false, getCurrentTimestamp());
                return saveTasks(tasks);
            }
        }
        return false;
    }

    void createSubTask(Task& parentTask, const std::string& title, const std::string& desc) {
        int subId = parentTask.nextSubTaskId++;
        parentTask.subtasks.emplace_back(subId, title, desc, false, getCurrentTimestamp());
    }
}