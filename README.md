# CLI Task Manager (C++)

A lightweight console-based task management application written in Modern C++ using Object-Oriented Programming (OOP) principles.

## Features
- **Task Hierarchy**: Polymorphic architecture with base `Task` class and standard (`SimpleTask`) and time-bound (`DeadlineTask`) implementations.
- **Modern Memory Management**: Automatic memory cleanup using `std::unique_ptr` and `std::move` semantics without manual allocation overhead.
- **State Persistence**: File serialization (`std::ofstream`) to export application state.

## Technologies Used
- C++14
- Standard Template Library (STL): `std::vector`, `std::unique_ptr`, `std::string`, `std::ofstream`
- Object-Oriented Programming (OOP): Encapsulation, Inheritance, Polymorphism, Abstract Classes

## How to Build & Run
```bash
g++ -std=c++14 task.cpp -o task
./task
