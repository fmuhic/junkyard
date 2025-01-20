add_executable(test
    main.c
)

set_target_properties(test PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED YES
    C_EXTENSIONS NO
)

target_include_directories(test PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(test graph)
