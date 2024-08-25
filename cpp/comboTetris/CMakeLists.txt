cmake_minimum_required(VERSION 3.16)
include(FetchContent)
 
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(game VERSION 0.0.1)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

FetchContent_Declare(
	raylib
	GIT_REPOSITORY https://github.com/raysan5/raylib.git
	GIT_TAG master
	GIT_SHALLOW TRUE
	GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(raylib)

add_executable(game
    src/main.cpp
    src/entity.cpp
    src/board.cpp
    src/game.cpp
    src/renderer.cpp
)

target_include_directories(game PRIVATE include)

target_link_libraries(game PRIVATE raylib)

if (MSVC)
    target_compile_options(game PRIVATE /W4 /WX)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT game)
	set_property(TARGET game PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
else()
    target_compile_options(game PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()	
