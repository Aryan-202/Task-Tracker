#include "Utils.hpp"
#include "Task.hpp"
#include "SubTask.hpp"
#include <vector>
#include <algorithm>

namespace Utils {

    bool deleteTask(int id) {
        std::vector<Task> tasks = loadTasks();
        auto it = std::remove_if(tasks.begin(), tasks.end(), [id](const Task& t) {
            return t.id == id;
        });

        if (it != tasks.end()) {
            tasks.erase(it, tasks.end());
            return saveTasks(tasks);
        }
        return false;
    }

    bool deleteSubTask(int taskId, int subTaskId) {
        std::vector<Task> tasks = loadTasks();
        for (auto& task : tasks) {
            if (task.id == taskId) {
                auto it = std::remove_if(task.subtasks.begin(), task.subtasks.end(), [subTaskId](const SubTask& s) {
                    return s.id == subTaskId;
                });
                if (it != task.subtasks.end()) {
                    task.subtasks.erase(it, task.subtasks.end());
                    return saveTasks(tasks);
                }
                return false;
            }
        }
        return false;
    }

    void deleteSubTask(Task& parentTask, int subTaskId) {
        auto it = std::remove_if(parentTask.subtasks.begin(), parentTask.subtasks.end(), [subTaskId](const SubTask& s) {
            return s.id == subTaskId;
        });
        if (it != parentTask.subtasks.end()) {
            parentTask.subtasks.erase(it, parentTask.subtasks.end());
        }
    }
}
