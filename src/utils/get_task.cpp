#include "Utils.hpp"
#include "Task.hpp"
#include <vector>

namespace Utils {

    bool getTask(int id, Task& outTask) {
        std::vector<Task> tasks = loadTasks();
        for (const auto& task : tasks) {
            if (task.id == id) {
                outTask = task;
                return true;
            }
        }
        return false;
    }
}
