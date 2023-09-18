cmake_minimum_required(VERSION 2.8)

project(simple)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} main.cpp)

# install(TARGETS simple DESTINATION bin)
