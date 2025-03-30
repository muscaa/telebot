cmake_minimum_required(VERSION 3.16)
project(telebot)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# Main
file(GLOB_RECURSE MAIN_SOURCES "src/*.cpp")

# ImGui
file(GLOB_RECURSE IMGUI_SOURCES "lib/imgui/*.cpp")

add_executable(telebot
    ${MAIN_SOURCES}
    ${IMGUI_SOURCES}
)
target_include_directories(telebot PRIVATE
    include
    lib/imgui
)

# SDL
add_subdirectory(lib/SDL EXCLUDE_FROM_ALL)
target_link_libraries(telebot PRIVATE SDL3::SDL3)
