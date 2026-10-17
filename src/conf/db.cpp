#include "Utils.hpp"
#include "Task.hpp"
#include "SubTask.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>
#include "nlohmann/json.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

namespace Utils {

    fs::path getDbPath() {
        fs::path dbPath;
        const char* userProfileEnv = std::getenv("USERPROFILE");
        if (userProfileEnv != nullptr && std::string(userProfileEnv).length() > 0) {
            dbPath = fs::path(userProfileEnv) / ".task_tracker" / "db" / "task_tracker.json";
        } else {
            const char* homeEnv = std::getenv("HOME");
            if (homeEnv != nullptr && std::string(homeEnv).length() > 0) {
                dbPath = fs::path(homeEnv) / ".task_tracker" / "db" / "task_tracker.json";
            } else {
                dbPath = fs::current_path() / ".task_tracker" / "db" / "task_tracker.json";
            }
        }
        return dbPath;
    }

    void createFile() {
        fs::path file_path = getDbPath();
        try {
            if (file_path.has_parent_path()) {
                fs::create_directories(file_path.parent_path());
            }
            if (!fs::exists(file_path)) {
                std::ofstream file(file_path);
                if (file.is_open()) {
                    file << "[]\n";
                    file.close();
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error creating database directory/file: " << e.what() << std::endl;
        }
    }

    std::string getCurrentTimestamp() {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::tm tm_buf{};
#if defined(_WIN32) || defined(_WIN64)
        localtime_s(&tm_buf, &now);
#else
        localtime_r(&now, &tm_buf);
#endif
        std::ostringstream oss;
        oss << std::put_time(&tm_buf, "%Y-%m-%d %H:%M");
        return oss.str();
    }

    std::vector<Task> loadTasks() {
        std::vector<Task> loadedTasks;
        fs::path file_path = getDbPath();

        if (!fs::exists(file_path) || fs::is_empty(file_path)) {
            createFile();
            return loadedTasks;
        }

        std::ifstream infile(file_path);
        if (!infile.is_open()) {
            std::cerr << "Warning: Could not open database file for reading: " << file_path << std::endl;
            return loadedTasks;
        }

        try {
            json root;
            infile >> root;
            infile.close();

            if (!root.is_array()) {
                std::cerr << "Warning: Database root is not an array. Resetting in-memory tasks.\n";
                return loadedTasks;
            }

            for (const auto& item : root) {
                if (!item.is_object()) continue;

                Task t;
                t.id = item.value("id", 0);
                t.title = item.value("title", "");
                t.description = item.value("description", "");
                t.isCompleted = item.value("isCompleted", false);
                t.priority = item.value("priority", "Medium");
                t.createdAt = item.value("createdAt", "");
                t.nextSubTaskId = item.value("nextSubTaskId", 1);

                if (item.contains("subtasks") && item["subtasks"].is_array()) {
                    int maxSubId = 0;
                    for (const auto& subItem : item["subtasks"]) {
                        if (!subItem.is_object()) continue;
                        SubTask s;
                        s.id = subItem.value("id", 0);
                        s.title = subItem.value("title", "");
                        s.description = subItem.value("description", "");
                        s.isCompleted = subItem.value("isCompleted", false);
                        s.createdAt = subItem.value("createdAt", "");
                        if (s.id > maxSubId) maxSubId = s.id;
                        t.subtasks.push_back(s);
                    }
                    if (t.nextSubTaskId <= maxSubId) {
                        t.nextSubTaskId = maxSubId + 1;
                    }
                }

                loadedTasks.push_back(t);
            }
        } catch (const json::parse_error& e) {
            std::cerr << "JSON Parse error: " << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Error loading database: " << e.what() << "\n";
        }

        return loadedTasks;
    }

    bool saveTasks(const std::vector<Task>& tasks) {
        fs::path file_path = getDbPath();
        try {
            if (file_path.has_parent_path()) {
                fs::create_directories(file_path.parent_path());
            }

            json root = json::array();
            for (const auto& t : tasks) {
                json task_obj = {
                    {"id", t.id},
                    {"title", t.title},
                    {"description", t.description},
                    {"isCompleted", t.isCompleted},
                    {"priority", t.priority},
                    {"createdAt", t.createdAt},
                    {"nextSubTaskId", t.nextSubTaskId}
                };

                json subs = json::array();
                for (const auto& s : t.subtasks) {
                    subs.push_back({
                        {"id", s.id},
                        {"title", s.title},
                        {"description", s.description},
                        {"isCompleted", s.isCompleted},
                        {"createdAt", s.createdAt}
                    });
                }
                task_obj["subtasks"] = subs;
                root.push_back(task_obj);
            }

            std::ofstream outfile(file_path);
            if (!outfile.is_open()) {
                std::cerr << "Error: Could not open database file for writing: " << file_path << std::endl;
                return false;
            }

            outfile << root.dump(4) << "\n";
            outfile.close();
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Error saving database: " << e.what() << std::endl;
            return false;
        }
    }
}
