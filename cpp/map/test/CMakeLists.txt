add_executable(test
    main.cpp
)

set_target_properties(test PROPERTIES
    CPP_STANDARD 17
    CPP_STANDARD_REQUIRED YES
    CPP_EXTENSIONS NO
)

target_include_directories(test PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(test map)
