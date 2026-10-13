cmake_minimum_required(VERSION 3.16)

project(TaskTracker VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(task_tracker ${SOURCES})


target_include_directories(task_tracker PRIVATE include)
