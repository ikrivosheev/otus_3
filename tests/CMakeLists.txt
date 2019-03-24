find_package (Threads)

add_executable(test_allocator test_allocator.cpp)

set_target_properties(test_allocator gtest PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

target_link_libraries(test_allocator
    gtest
    ${CMAKE_THREAD_LIBS_INIT}
    utils
)

target_include_directories(gtest PRIVATE ${GTEST_INCLUDE_DIRS})

add_test(test_allocator test_allocator)

