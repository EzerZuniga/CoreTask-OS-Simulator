# CoreTask OS Simulator

CoreTask OS Simulator is an academic, console-based operating system simulator built with modern C++17.
It is designed as a final Data Structures project and models key OS subsystems inspired by Windows Task Manager and Linux process tools.

## Project Description

The simulator provides a modular architecture where processes, CPU scheduling, RAM allocation, file explorer operations, action history, and recursive validations work together as a cohesive system.

The project emphasizes software engineering quality:

- Header/source separation
- Encapsulation and clean interfaces
- Dynamic memory management
- Professional naming and modular design
- SOLID-inspired organization for scalability

## Features

- Process Manager (dynamic linked list)
  - Create, delete, search, and list active processes
  - Unique PID validation using recursion
- CPU Scheduler (queue)
  - FIFO execution
  - Round Robin simulation
  - CPU queue visualization
- RAM Manager (dynamic linked list)
  - Allocate and release RAM by PID
  - RAM usage statistics with ASCII bars
- System History (stack)
  - Push actions, display history, undo last action
- File Explorer (dynamic linked list)
  - Create, delete, search, and list virtual files
- Recursion utilities
  - Recursive PID uniqueness validation
  - Recursive process search
  - Recursive file search
- Extra system features
  - Colored console UI (ANSI)
  - Logging to `data/system.log`
  - Statistics panel

## Data Structures Used

- Singly linked lists:
  - Process list
  - RAM allocations
  - File explorer list
- Queue:
  - CPU scheduler
- Stack:
  - System history
- Recursion:
  - Uniqueness checks, searches, and input validation

## Technologies

- C++17
- Standard Library (`<iostream>`, `<string>`, `<fstream>`, `<chrono>`, `<thread>`, `<random>`, etc.)
- Console ANSI styling

## Folder Structure

```text
CoreTask-OS-Simulator/
├── README.md
├── LICENSE
├── .gitignore
├── assets/
├── docs/
├── include/
├── src/
├── data/
├── tests/
└── build/
```

## Compilation

From project root:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude src/*.cpp -o build/coretask_os_simulator
```

Run:

```bash
./build/coretask_os_simulator
```

On Windows (PowerShell, MinGW):

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude src/*.cpp -o build/coretask_os_simulator.exe
.\build\coretask_os_simulator.exe
```

## Example Screenshots

Add your console captures here:

- `assets/menu_principal.png`
- `assets/ram_panel.png`
- `assets/estadisticas.png`

## Educational Purpose

This project was created for academic training in:

- Data Structures
- Object-Oriented Programming
- Dynamic memory and pointers
- Modular C++ architecture
- Console systems simulation
