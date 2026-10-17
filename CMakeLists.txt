cmake_minimum_required(VERSION 3.16)

project(TaskTracker VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.3 
)
FetchContent_MakeAvailable(json)

set(SOURCES
    src/main.cpp
    src/Task.cpp
    src/SubTask.cpp
    src/TaskManager.cpp

    src/utils/create_task.cpp
    src/utils/get_task.cpp
    src/utils/update_task.cpp
    src/utils/delete_task.cpp 

    src/conf/db.cpp
)

add_executable(task_tracker ${SOURCES})
target_include_directories(task_tracker PRIVATE include)

target_link_libraries(task_tracker PRIVATE nlohmann_json::nlohmann_json)
