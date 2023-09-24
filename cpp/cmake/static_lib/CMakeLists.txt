cmake_minimum_required(VERSION 3.13)

project(simple)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(math)

target_link_libraries(${PROJECT_NAME} math)
