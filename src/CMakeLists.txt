configure_file(config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h)

add_executable(allocator main.cpp)

add_library(utils version.cpp)

set_target_properties(allocator PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

target_link_libraries(allocator utils)
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


install(TARGETS allocator RUNTIME DESTINATION bin)

