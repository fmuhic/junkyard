cmake_minimum_required(VERSION 3.13)

project(custom_allocator C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(alloc main.c)

target_include_directories(alloc PRIVATE headers)
