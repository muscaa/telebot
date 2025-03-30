cmake_minimum_required(VERSION 3.23)
project(telebot)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# Conan packages
find_package(SDL3 REQUIRED)

# Main
file(GLOB_RECURSE MAIN_SOURCES "src/*.cpp")

# ImGui
file(GLOB_RECURSE IMGUI_SOURCES "lib/imgui/*.cpp")

add_executable(${PROJECT_NAME}
    ${MAIN_SOURCES}
    ${IMGUI_SOURCES}
)
target_include_directories(${PROJECT_NAME} PRIVATE
    include
    lib/imgui
)

# SDL
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
