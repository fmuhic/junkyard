cmake_minimum_required(VERSION 3.13.0)

project(simple)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(external/glfw)

target_link_directories(${PROJECT_NAME}
    PRIVATE
        external/glfw/src
)

target_link_libraries(${PROJECT_NAME} glfw)
# install(TARGETS simple DESTINATION bin)
