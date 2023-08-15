cmake_minimum_required(VERSION 3.13)

project(simple)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} main.cpp math/math.h)

target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/math/build)
target_link_libraries(${PROJECT_NAME} math)
