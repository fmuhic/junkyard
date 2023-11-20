cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(custom_allocator VERSION 1.0)

add_executable(alloc
    src/alloc.cpp
    src/main.cpp
)

target_include_directories(alloc PRIVATE include)
