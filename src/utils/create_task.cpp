#include "Utils.hpp"
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

void createTask(int id, const std::string& title, const std::string& desc) {
    const std::string userProfile = std::getenv("USERPROFILE");

    if (userProfile != "")
    {
        fs::path FILE_PATH = fs::path(userProfile) / "task_tracker.json";
    } else
    {
        printf("Error creating file");
    }
    
}
