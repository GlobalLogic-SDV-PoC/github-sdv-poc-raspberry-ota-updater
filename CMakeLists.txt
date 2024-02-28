cmake_minimum_required(VERSION 3.16.3)

project(
    updater_app
    VERSION 1.0.0
    LANGUAGES CXX)

# add library
add_subdirectory(dep/internal/updater)

add_executable(updater_app
    src/main.cpp
    src/docker_updater.cpp
)
target_link_libraries(updater_app PRIVATE updater_core)
