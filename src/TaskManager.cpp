#include "TaskManager.hpp"
#include "Utils.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>

TaskManager::TaskManager() {
    loadFromDisk();
}

void TaskManager::updateNextIds() {
    int maxId = 0;
    for (auto& task : tasks) {
        if (task.id > maxId) {
            maxId = task.id;
        }
        int maxSubId = 0;
        for (const auto& sub : task.subtasks) {
            if (sub.id > maxSubId) {
                maxSubId = sub.id;
            }
        }
        task.nextSubTaskId = maxSubId + 1;
    }
    nextId = maxId + 1;
}

void TaskManager::loadFromDisk() {
    tasks = Utils::loadTasks();
    updateNextIds();
}

void TaskManager::saveToDisk() const {
    Utils::saveTasks(tasks);
}

int TaskManager::createTask(const std::string& title, const std::string& description, const std::string& priority) {
    int id = nextId++;
    std::string timestamp = Utils::getCurrentTimestamp();
    std::string actualPriority = priority.empty() ? "Medium" : priority;

    tasks.emplace_back(id, title, description, false, actualPriority, timestamp);
    saveToDisk();
    return id;
}

bool TaskManager::updateTask(int taskId, const std::string& title, const std::string& description, const std::string& priority) {
    Task* task = getTaskById(taskId);
    if (task != nullptr) {
        if (!title.empty()) task->title = title;
        if (!description.empty()) task->description = description;
        if (!priority.empty()) task->priority = priority;
        saveToDisk();
        return true;
    }
    return false;
}

bool TaskManager::deleteTask(int taskId) {
    auto it = std::remove_if(tasks.begin(), tasks.end(), [taskId](const Task& t) {
        return t.id == taskId;
    });

    if (it != tasks.end()) {
        tasks.erase(it, tasks.end());
        saveToDisk();
        return true;
    }
    return false;
}

bool TaskManager::toggleTaskStatus(int taskId) {
    Task* task = getTaskById(taskId);
    if (task != nullptr) {
        task->isCompleted = !task->isCompleted;
        saveToDisk();
        return true;
    }
    return false;
}

bool TaskManager::setTaskStatus(int taskId, bool isCompleted) {
    Task* task = getTaskById(taskId);
    if (task != nullptr) {
        task->isCompleted = isCompleted;
        saveToDisk();
        return true;
    }
    return false;
}

bool TaskManager::addSubTaskToTask(int taskId, const std::string& title, const std::string& description) {
    Task* task = getTaskById(taskId);
    if (task != nullptr) {
        int subId = task->nextSubTaskId++;
        task->subtasks.emplace_back(subId, title, description, false, Utils::getCurrentTimestamp());
        saveToDisk();
        return true;
    }
    return false;
}

bool TaskManager::updateSubTask(int taskId, int subTaskId, const std::string& title, const std::string& description) {
    Task* task = getTaskById(taskId);
    if (task != nullptr) {
        for (auto& sub : task->subtasks) {
            if (sub.id == subTaskId) {
                if (!title.empty()) sub.title = title;
                if (!description.empty()) sub.description = description;
                saveToDisk();
                return true;
            }
        }
    }
    return false;
}

bool TaskManager::deleteSubTask(int taskId, int subTaskId) {
    Task* task = getTaskById(taskId);
    if (task != nullptr) {
        auto it = std::remove_if(task->subtasks.begin(), task->subtasks.end(), [subTaskId](const SubTask& s) {
            return s.id == subTaskId;
        });
        if (it != task->subtasks.end()) {
            task->subtasks.erase(it, task->subtasks.end());
            saveToDisk();
            return true;
        }
    }
    return false;
}

bool TaskManager::toggleSubTaskStatus(int taskId, int subTaskId) {
    Task* task = getTaskById(taskId);
    if (task != nullptr) {
        for (auto& sub : task->subtasks) {
            if (sub.id == subTaskId) {
                sub.isCompleted = !sub.isCompleted;
                saveToDisk();
                return true;
            }
        }
    }
    return false;
}

bool TaskManager::setSubTaskStatus(int taskId, int subTaskId, bool isCompleted) {
    Task* task = getTaskById(taskId);
    if (task != nullptr) {
        for (auto& sub : task->subtasks) {
            if (sub.id == subTaskId) {
                sub.isCompleted = isCompleted;
                saveToDisk();
                return true;
            }
        }
    }
    return false;
}

const Task* TaskManager::getTaskById(int taskId) const {
    for (const auto& task : tasks) {
        if (task.id == taskId) {
            return &task;
        }
    }
    return nullptr;
}

Task* TaskManager::getTaskById(int taskId) {
    for (auto& task : tasks) {
        if (task.id == taskId) {
            return &task;
        }
    }
    return nullptr;
}

const std::vector<Task>& TaskManager::getAllTasks() const {
    return tasks;
}

size_t TaskManager::getTaskCount() const {
    return tasks.size();
}

void TaskManager::listTasks(int filter) const {
    std::vector<const Task*> filtered;
    for (const auto& task : tasks) {
        if (filter == 1 && task.isCompleted) continue; // Pending only
        if (filter == 2 && !task.isCompleted) continue; // Completed only
        if (filter == 3 && task.priority != "High") continue; // High priority only
        filtered.push_back(&task);
    }

    if (filtered.empty()) {
        std::cout << "\n--- No tasks found matching the selected filter. ---\n";
        return;
    }

    std::cout << "\n=========================================================================================================\n";
    std::cout << std::left << std::setw(6)  << "ID"
              << std::left << std::setw(12) << "STATUS"
              << std::left << std::setw(10) << "PRIORITY"
              << std::left << std::setw(18) << "CREATED"
              << "TITLE & SUBTASK PROGRESS\n";
    std::cout << "=========================================================================================================\n";

    for (const auto* task : filtered) {
        std::string statusStr = task->isCompleted ? "[Done]" : "[Pending]";
        std::string priorityStr = "[" + task->priority + "]";
        std::string progressStr = "";
        if (!task->subtasks.empty()) {
            progressStr = " (" + std::to_string(task->getCompletedSubtasksCount()) + "/"
                          + std::to_string(task->getTotalSubtasksCount()) + " subtasks done)";
        }

        std::cout << std::left << std::setw(6)  << ("#" + std::to_string(task->id))
                  << std::left << std::setw(12) << statusStr
                  << std::left << std::setw(10) << priorityStr
                  << std::left << std::setw(18) << (task->createdAt.empty() ? "-" : task->createdAt)
                  << task->title << progressStr << "\n";

        for (const auto& sub : task->subtasks) {
            std::string subStatus = sub.isCompleted ? "[X]" : "[ ]";
            std::cout << "      |-- " << subStatus << " #" << task->id << "." << sub.id << " "
                      << sub.title << (sub.isCompleted ? " (Done)" : " (Pending)") << "\n";
        }
    }
    std::cout << "=========================================================================================================\n";
    std::cout << "Total displayed: " << filtered.size() << " task(s)\n";
}

void TaskManager::viewTaskDetails(int taskId) const {
    const Task* task = getTaskById(taskId);
    if (task == nullptr) {
        std::cout << "\nTask with ID #" << taskId << " was not found.\n";
        return;
    }

    std::cout << "\n================================================================================\n";
    std::cout << " TASK DETAILS: #" << task->id << " - " << task->title << "\n";
    std::cout << "================================================================================\n";
    std::cout << "  Status:      " << (task->isCompleted ? "[Done]" : "[Pending]") << "\n";
    std::cout << "  Priority:    " << task->priority << "\n";
    std::cout << "  Created:     " << (task->createdAt.empty() ? "N/A" : task->createdAt) << "\n";
    std::cout << "  Description: " << (task->description.empty() ? "(No description provided)" : task->description) << "\n";
    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << "  Subtasks (" << task->getCompletedSubtasksCount() << "/"
              << task->getTotalSubtasksCount() << " completed):\n";

    if (task->subtasks.empty()) {
        std::cout << "    (No subtasks created for this task yet)\n";
    } else {
        for (const auto& sub : task->subtasks) {
            std::cout << "    [" << (sub.isCompleted ? "X" : " ") << "] Subtask #" << sub.id
                      << ": " << sub.title << " (" << (sub.isCompleted ? "Done" : "Pending") << ")\n";
            if (!sub.description.empty()) {
                std::cout << "        Description: " << sub.description << "\n";
            }
            if (!sub.createdAt.empty()) {
                std::cout << "        Created:     " << sub.createdAt << "\n";
            }
        }
    }
    std::cout << "================================================================================\n";
}

static std::string toLower(std::string_view s) {
    std::string result;
    result.reserve(s.size());
    for (char c : s) {
        result.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(c))));
    }
    return result;
}

void TaskManager::searchTasks(const std::string& keyword) const {
    if (keyword.empty()) {
        listTasks(0);
        return;
    }

    std::string lowerKeyword = toLower(keyword);
    std::vector<const Task*> matches;

    for (const auto& task : tasks) {
        bool matched = false;
        if (toLower(task.title).find(lowerKeyword) != std::string::npos ||
            toLower(task.description).find(lowerKeyword) != std::string::npos ||
            toLower(task.priority).find(lowerKeyword) != std::string::npos) {
            matched = true;
        }

        if (!matched) {
            for (const auto& sub : task.subtasks) {
                if (toLower(sub.title).find(lowerKeyword) != std::string::npos ||
                    toLower(sub.description).find(lowerKeyword) != std::string::npos) {
                    matched = true;
                    break;
                }
            }
        }

        if (matched) {
            matches.push_back(&task);
        }
    }

    if (matches.empty()) {
        std::cout << "\nNo tasks found matching keyword: \"" << keyword << "\"\n";
        return;
    }

    std::cout << "\nFound " << matches.size() << " task(s) matching \"" << keyword << "\":\n";
    std::cout << "=========================================================================================================\n";
    std::cout << std::left << std::setw(6)  << "ID"
              << std::left << std::setw(12) << "STATUS"
              << std::left << std::setw(10) << "PRIORITY"
              << std::left << std::setw(18) << "CREATED"
              << "TITLE\n";
    std::cout << "=========================================================================================================\n";

    for (const auto* task : matches) {
        std::string statusStr = task->isCompleted ? "[Done]" : "[Pending]";
        std::string priorityStr = "[" + task->priority + "]";
        std::cout << std::left << std::setw(6)  << ("#" + std::to_string(task->id))
                  << std::left << std::setw(12) << statusStr
                  << std::left << std::setw(10) << priorityStr
                  << std::left << std::setw(18) << (task->createdAt.empty() ? "-" : task->createdAt)
                  << task->title << "\n";
    }
    std::cout << "=========================================================================================================\n";
}

void TaskManager::displayStatistics() const {
    int totalTasks = static_cast<int>(tasks.size());
    int completedTasks = 0;
    int pendingTasks = 0;
    int highPriority = 0;
    int mediumPriority = 0;
    int lowPriority = 0;
    int totalSubtasks = 0;
    int completedSubtasks = 0;

    for (const auto& task : tasks) {
        if (task.isCompleted) completedTasks++;
        else pendingTasks++;

        if (task.priority == "High") highPriority++;
        else if (task.priority == "Low") lowPriority++;
        else mediumPriority++;

        for (const auto& sub : task.subtasks) {
            totalSubtasks++;
            if (sub.isCompleted) completedSubtasks++;
        }
    }

    double taskRate = totalTasks > 0 ? (100.0 * completedTasks / totalTasks) : 0.0;
    double subRate = totalSubtasks > 0 ? (100.0 * completedSubtasks / totalSubtasks) : 0.0;

    std::cout << "\n========================================================\n";
    std::cout << "                 TASK TRACKER METRICS                   \n";
    std::cout << "========================================================\n";
    std::cout << "  Total Tasks:           " << totalTasks << "\n";
    std::cout << "  - Completed:           " << completedTasks << " (" << std::fixed << std::setprecision(1) << taskRate << "%)\n";
    std::cout << "  - Pending:             " << pendingTasks << "\n";
    std::cout << "--------------------------------------------------------\n";
    std::cout << "  Priority Breakdown:\n";
    std::cout << "  - High Priority:       " << highPriority << "\n";
    std::cout << "  - Medium Priority:     " << mediumPriority << "\n";
    std::cout << "  - Low Priority:        " << lowPriority << "\n";
    std::cout << "--------------------------------------------------------\n";
    std::cout << "  Subtask Metrics:\n";
    std::cout << "  - Total Subtasks:      " << totalSubtasks << "\n";
    std::cout << "  - Subtasks Completed:  " << completedSubtasks << " (" << std::fixed << std::setprecision(1) << subRate << "%)\n";
    std::cout << "  - Subtasks Pending:    " << (totalSubtasks - completedSubtasks) << "\n";
    std::cout << "========================================================\n";
}