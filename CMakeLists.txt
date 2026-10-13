cmake_minimum_required(VERSION 3.16)

project(TaskTracker VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
    src/Task.cpp
    src/TaskManager.cpp
)

file(GLOB SOURCES "src/*.cpp")

add_executable(task_tracker ${SOURCES})


target_include_directories(task_tracker PRIVATE include)
