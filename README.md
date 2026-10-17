# Task Tracker Console Application

A modern, fast, and feature-packed console Task Tracker application written in **C++20** with persistent JSON storage powered by `nlohmann/json`.

---

## Features

- **Full Task Lifecycle Management (CRUD)**:
  - Create tasks with a title, description, and priority level (**High**, **Medium**, **Low**).
  - Automatically records creation timestamps (`YYYY-MM-DD HH:MM`).
  - Update task title, description, and priority anytime.
  - Delete tasks and automatically cascade-delete their associated subtasks.
  - Quick status toggling between `[Pending]` and `[Done]`.
- **Subtask / Checklist Support**:
  - Add nested subtasks to any parent task.
  - Each subtask has its own ID, title, description, status, and creation date.
  - Update, delete, and toggle completion of individual subtasks.
  - Real-time subtask completion progress indicators (e.g. `(2/3 subtasks done)`).
- **Persistent JSON Storage**:
  - Automatically loads existing tasks on application startup and saves on every change.
  - Storage file is kept in `%USERPROFILE%/.task_tracker/db/task_tracker.json` (or `$HOME` / working directory fallback).
  - Automatically provisions parent directories if they do not exist.
  - IDs are persistent across sessions and automatically increment without collision.
- **Views & Search**:
  - Filter tasks by status: All, Pending Only, Completed Only, or High Priority Only.
  - Case-insensitive search across task titles, descriptions, priorities, and subtask text.
  - View full details card for any task by its ID.
- **Statistics & Metrics Dashboard**:
  - Displays total tasks, completed vs. pending tasks, completion rate (%), priority breakdown, and subtask metrics.
- **Robust Console UI**:
  - Validates all user input and handles invalid entries or stream errors without crashing or infinite loops.
  - Safe confirmation prompts before deleting tasks or subtasks.

---

## Project Structure

```
d:/projects/task-tracker/
├── CMakeLists.txt          # CMake build configuration with nlohmann/json FetchContent
├── README.md               # Documentation and usage guide
├── .gitignore              # Git ignore configuration
├── include/
│   ├── Task.hpp            # Task data structure & subtask counters
│   ├── SubTask.hpp         # SubTask data structure
│   ├── TaskManager.hpp     # In-memory manager, filtering, search, and statistics
│   └── Utils.hpp           # Database persistence, timestamping, and CRUD utilities
└── src/
    ├── main.cpp            # Interactive console menu with input validation
    ├── Task.cpp            # Task model implementation
    ├── SubTask.cpp         # SubTask model implementation
    ├── TaskManager.cpp     # TaskManager operations and formatted display
    ├── conf/
    │   └── db.cpp          # JSON database initialization, load, and save
    └── utils/
        ├── create_task.cpp # Task & SubTask creation utilities
        ├── get_task.cpp    # Task query utilities
        ├── update_task.cpp # Task & SubTask update & status toggle utilities
        ├── delete_task.cpp # Task & SubTask deletion utilities
        └── id_counter.cpp  # ID counter helpers
```

---

## Building and Running

### Prerequisites
- C++20 compliant compiler (MSVC 2019+, GCC 10+, or Clang 11+)
- CMake 3.16 or later
- Internet access during initial CMake configure (to automatically fetch `nlohmann/json` v3.11.3)

### Build with CMake

```bash
# 1. Create and enter build directory
mkdir build
cd build

# 2. Configure the project
cmake ..

# 3. Build the executable
cmake --build . --config Release
```

### Run the Application

On Windows:
```cmd
.\Release\task_tracker.exe
# or if built in root build dir:
.\task_tracker.exe
```

---

## Menu Options

```
======================================================
              TASK TRACKER CONSOLE APP                
======================================================

--- TASK OPERATIONS ---
 1. List All Tasks
 2. View Task Details
 3. Create New Task
 4. Update Task
 5. Delete Task
 6. Toggle Task Status (Done / Pending)

--- SUBTASK OPERATIONS ---
 7. Add Subtask to Task
 8. Update Subtask
 9. Delete Subtask
10. Toggle Subtask Status (Done / Pending)

--- VIEWS & SEARCH ---
11. Filter Tasks
12. Search Tasks
13. View Statistics & Metrics

 0. Exit Application
------------------------------------------------------
```
