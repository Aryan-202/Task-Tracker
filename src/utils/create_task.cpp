#include "Utils.hpp"
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "nlohmann/json.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

void Utils::createTask(int id, const std::string& title, const std::string& desc) {
    fs::path file_path = Utils::getDbPath();
    json task_list = json::array();

    if (fs::exists(file_path) && !fs::is_empty(file_path))
    {
        std::ifstream infile(file_path);
        if (infile.is_open())
        {
            try
            {
                infile >> task_list;
                if (!task_list.is_array())
                {
                    task_list = json::array();
                }
                
            }
            catch(const json::parse_error& e)
            {
                std::cerr << "Parse error" << e.what() << '\n' <<"\nResetting db file";
                task_list = json::array();  
            }
            infile.close();
        } 
    }

    json new_task = {
        {"id", id},
        {"title", title},
        {"description", desc},
        {"isCompleted", false}
    };

    task_list.push_back(new_task);

    std::ofstream outfile(file_path);
    if (outfile.is_open())
    {
        outfile << task_list.dump(4);
        outfile.close();
    } else
    {
        std::cerr << "Error: could not open database file for writing: " << file_path << std::endl;
    }
}