cmake_minimum_required(VERSION 3.13.0)

set(CMAKE_C_STANDARD 17)

project(graph VERSION 1.0)

add_library(graph
    graph.h
    graph.c
)

target_include_directories(graph
    PUBLIC ${CMAKE_SOURCE_DIR}
)

add_subdirectory(
    test
)
