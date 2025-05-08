cmake_minimum_required(VERSION 3.13.0)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(map VERSION 1.0)

add_library(map
    map.h
    map.cpp
    murmur3.cpp
)

target_include_directories(map
    PUBLIC ${CMAKE_SOURCE_DIR}
)

add_subdirectory(
    test
)
