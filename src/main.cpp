#include "TaskManager.hpp"
#include "Utils.hpp"
#include <iostream>
#include <string>
#include <limits>
#include <cctype>

namespace {

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int readInt(const std::string& prompt, int minVal = std::numeric_limits<int>::min(), int maxVal = std::numeric_limits<int>::max()) {
    int value = 0;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            clearInputBuffer();
            if (value >= minVal && value <= maxVal) {
                return value;
            }
            std::cout << "Input out of range. Please enter a number between " << minVal << " and " << maxVal << ".\n";
        } else {
            if (std::cin.eof()) {
                std::cout << "\nInput terminated.\n";
                return minVal;
            }
            std::cout << "Invalid input. Please enter a valid number.\n";
            clearInputBuffer();
        }
    }
}

std::string readLine(const std::string& prompt, bool allowEmpty = false) {
    std::string text;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, text)) {
            return "";
        }
        if (allowEmpty || !text.empty()) {
            return text;
        }
        std::cout << "This field cannot be empty. Please enter a value.\n";
    }
}

bool readConfirmation(const std::string& prompt) {
    while (true) {
        std::string resp = readLine(prompt + " (y/n): ");
        if (!resp.empty()) {
            char c = static_cast<char>(std::tolower(static_cast<unsigned char>(resp[0])));
            if (c == 'y') return true;
            if (c == 'n') return false;
        }
        std::cout << "Please enter 'y' for yes or 'n' for no.\n";
    }
}

std::string selectPriority() {
    std::cout << "Select Priority:\n";
    std::cout << "  1. Low\n";
    std::cout << "  2. Medium (Default)\n";
    std::cout << "  3. High\n";
    int pChoice = readInt("Enter priority (1-3): ", 1, 3);
    if (pChoice == 1) return "Low";
    if (pChoice == 3) return "High";
    return "Medium";
}

void printBanner() {
    std::cout << "\n======================================================\n";
    std::cout << "              TASK TRACKER CONSOLE APP                \n";
    std::cout << "======================================================\n";
}

void printMenu() {
    std::cout << "\n--- TASK OPERATIONS ---\n";
    std::cout << " 1. List All Tasks\n";
    std::cout << " 2. View Task Details\n";
    std::cout << " 3. Create New Task\n";
    std::cout << " 4. Update Task\n";
    std::cout << " 5. Delete Task\n";
    std::cout << " 6. Toggle Task Status (Done / Pending)\n";
    std::cout << "\n--- SUBTASK OPERATIONS ---\n";
    std::cout << " 7. Add Subtask to Task\n";
    std::cout << " 8. Update Subtask\n";
    std::cout << " 9. Delete Subtask\n";
    std::cout << "10. Toggle Subtask Status (Done / Pending)\n";
    std::cout << "\n--- VIEWS & SEARCH ---\n";
    std::cout << "11. Filter Tasks\n";
    std::cout << "12. Search Tasks\n";
    std::cout << "13. View Statistics & Metrics\n";
    std::cout << "\n 0. Exit Application\n";
    std::cout << "------------------------------------------------------\n";
}

} // namespace

int main() {
    TaskManager manager;
    printBanner();
    std::cout << "Database loaded successfully (" << manager.getTaskCount() << " tasks in storage).\n";

    bool running = true;
    while (running) {
        printMenu();
        int choice = readInt("Enter your choice (0-13): ", 0, 13);

        switch (choice) {
            case 1: {
                manager.listTasks(0);
                break;
            }
            case 2: {
                int taskId = readInt("Enter Task ID to view: ", 1);
                manager.viewTaskDetails(taskId);
                break;
            }
            case 3: {
                std::cout << "\n--- Create New Task ---\n";
                std::string title = readLine("Enter task title: ", false);
                std::string description = readLine("Enter task description: ", true);
                std::string priority = selectPriority();

                int newId = manager.createTask(title, description, priority);
                std::cout << "\n[Success] Task #" << newId << " created successfully!\n";
                break;
            }
            case 4: {
                std::cout << "\n--- Update Task ---\n";
                int taskId = readInt("Enter Task ID to update: ", 1);
                const Task* existing = manager.getTaskById(taskId);
                if (existing == nullptr) {
                    std::cout << "\n[Error] Task #" << taskId << " does not exist.\n";
                    break;
                }

                std::cout << "Current title: " << existing->title << "\n";
                std::string newTitle = readLine("Enter new title (leave blank to keep unchanged): ", true);

                std::cout << "Current description: " << existing->description << "\n";
                std::string newDesc = readLine("Enter new description (leave blank to keep unchanged): ", true);

                std::cout << "Current priority: " << existing->priority << "\n";
                std::string updatePrio = readLine("Update priority? (y/n): ", true);
                std::string newPriority = "";
                if (!updatePrio.empty() && std::tolower(static_cast<unsigned char>(updatePrio[0])) == 'y') {
                    newPriority = selectPriority();
                }

                if (manager.updateTask(taskId, newTitle, newDesc, newPriority)) {
                    std::cout << "\n[Success] Task #" << taskId << " updated successfully!\n";
                } else {
                    std::cout << "\n[Error] Failed to update task #" << taskId << ".\n";
                }
                break;
            }
            case 5: {
                std::cout << "\n--- Delete Task ---\n";
                int taskId = readInt("Enter Task ID to delete: ", 1);
                const Task* existing = manager.getTaskById(taskId);
                if (existing == nullptr) {
                    std::cout << "\n[Error] Task #" << taskId << " does not exist.\n";
                    break;
                }

                if (readConfirmation("Are you sure you want to permanently delete Task #" + std::to_string(taskId) + " (" + existing->title + ")?")) {
                    if (manager.deleteTask(taskId)) {
                        std::cout << "\n[Success] Task #" << taskId << " and all its subtasks were deleted.\n";
                    } else {
                        std::cout << "\n[Error] Could not delete Task #" << taskId << ".\n";
                    }
                } else {
                    std::cout << "Deletion cancelled.\n";
                }
                break;
            }
            case 6: {
                std::cout << "\n--- Toggle Task Status ---\n";
                int taskId = readInt("Enter Task ID to toggle status: ", 1);
                const Task* existing = manager.getTaskById(taskId);
                if (existing == nullptr) {
                    std::cout << "\n[Error] Task #" << taskId << " does not exist.\n";
                    break;
                }

                bool newStatus = !existing->isCompleted;
                manager.toggleTaskStatus(taskId);
                std::cout << "\n[Success] Task #" << taskId << " marked as "
                          << (newStatus ? "[Done]" : "[Pending]") << "!\n";
                break;
            }
            case 7: {
                std::cout << "\n--- Add Subtask ---\n";
                int taskId = readInt("Enter parent Task ID: ", 1);
                const Task* parent = manager.getTaskById(taskId);
                if (parent == nullptr) {
                    std::cout << "\n[Error] Parent Task #" << taskId << " does not exist.\n";
                    break;
                }

                std::string title = readLine("Enter subtask title: ", false);
                std::string description = readLine("Enter subtask description: ", true);

                if (manager.addSubTaskToTask(taskId, title, description)) {
                    std::cout << "\n[Success] Subtask added to Task #" << taskId << "!\n";
                } else {
                    std::cout << "\n[Error] Failed to add subtask.\n";
                }
                break;
            }
            case 8: {
                std::cout << "\n--- Update Subtask ---\n";
                int taskId = readInt("Enter parent Task ID: ", 1);
                const Task* parent = manager.getTaskById(taskId);
                if (parent == nullptr) {
                    std::cout << "\n[Error] Parent Task #" << taskId << " does not exist.\n";
                    break;
                }

                int subTaskId = readInt("Enter Subtask ID to update: ", 1);
                std::string newTitle = readLine("Enter new subtask title (leave blank to keep unchanged): ", true);
                std::string newDesc = readLine("Enter new subtask description (leave blank to keep unchanged): ", true);

                if (manager.updateSubTask(taskId, subTaskId, newTitle, newDesc)) {
                    std::cout << "\n[Success] Subtask #" << subTaskId << " of Task #" << taskId << " updated successfully!\n";
                } else {
                    std::cout << "\n[Error] Subtask #" << subTaskId << " not found under Task #" << taskId << ".\n";
                }
                break;
            }
            case 9: {
                std::cout << "\n--- Delete Subtask ---\n";
                int taskId = readInt("Enter parent Task ID: ", 1);
                int subTaskId = readInt("Enter Subtask ID to delete: ", 1);

                if (readConfirmation("Are you sure you want to delete Subtask #" + std::to_string(subTaskId) + "?")) {
                    if (manager.deleteSubTask(taskId, subTaskId)) {
                        std::cout << "\n[Success] Subtask #" << subTaskId << " removed from Task #" << taskId << ".\n";
                    } else {
                        std::cout << "\n[Error] Could not find or delete Subtask #" << subTaskId << ".\n";
                    }
                } else {
                    std::cout << "Deletion cancelled.\n";
                }
                break;
            }
            case 10: {
                std::cout << "\n--- Toggle Subtask Status ---\n";
                int taskId = readInt("Enter parent Task ID: ", 1);
                int subTaskId = readInt("Enter Subtask ID: ", 1);

                if (manager.toggleSubTaskStatus(taskId, subTaskId)) {
                    const Task* parent = manager.getTaskById(taskId);
                    bool isDone = false;
                    if (parent != nullptr) {
                        for (const auto& s : parent->subtasks) {
                            if (s.id == subTaskId) {
                                isDone = s.isCompleted;
                                break;
                            }
                        }
                    }
                    std::cout << "\n[Success] Subtask #" << subTaskId << " of Task #" << taskId
                              << " is now " << (isDone ? "[Done]" : "[Pending]") << "!\n";
                } else {
                    std::cout << "\n[Error] Subtask #" << subTaskId << " not found under Task #" << taskId << ".\n";
                }
                break;
            }
            case 11: {
                std::cout << "\n--- Filter Tasks ---\n";
                std::cout << "  1. All Tasks\n";
                std::cout << "  2. Pending Tasks Only\n";
                std::cout << "  3. Completed Tasks Only\n";
                std::cout << "  4. High Priority Tasks Only\n";
                int filterChoice = readInt("Choose filter (1-4): ", 1, 4);
                manager.listTasks(filterChoice - 1);
                break;
            }
            case 12: {
                std::cout << "\n--- Search Tasks ---\n";
                std::string keyword = readLine("Enter search keyword: ", false);
                manager.searchTasks(keyword);
                break;
            }
            case 13: {
                manager.displayStatistics();
                break;
            }
            case 0: {
                std::cout << "\nSaving and exiting Task Tracker. Goodbye!\n";
                running = false;
                break;
            }
            default:
                break;
        }
    }

    return 0;
}
