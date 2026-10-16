#include <iostream>
#include <filesystem>
#include <string>
#include <fstream> 

namespace fs = std::filesystem;

void createFile() {
    const char* userProfileEnv = std::getenv("USERPROFILE");

    if (userProfileEnv != nullptr)
    {
        fs::path file_path = fs::path(userProfileEnv) / "task_tracker.json";
        
        std::ofstream file(file_path);
        
        if (file.is_open()) {
            file << "{}";
            std::cout << "File successfully created at: " << file_path << std::endl;
            file.close();
        } else {
            std::cout << "Failed to open or create the file." << std::endl;
        }
    } 
    else 
    {
        std::cout << "Error: USERPROFILE environment variable not found!" << std::endl;
    }
}
