#include <iostream>
#include <filesystem>
#include <fstream> 
#include <cstdlib>

namespace fs = std::filesystem;

namespace Utils {
    fs::path getDbPath() {
        const char* userProfileEnv = std::getenv("USERPROFILE");
        if (userProfileEnv != nullptr) {
            return fs::path(userProfileEnv) / ".task_tracker/db/task_tracker.json";
        }
        return fs::current_path() / ".task_tracker/db/task_tracker.json";
    }

    void createFile() {
        fs::path file_path = getDbPath();
        
        std::ofstream file(file_path);
        
        if (file.is_open()) {
            file << "{}";
            std::cout << "File successfully created at: " << file_path << std::endl;
            file.close();
        } else {
            std::cout << "Failed to open or create the file." << std::endl;
        }
    }
}
