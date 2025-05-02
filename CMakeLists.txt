cmake_minimum_required(VERSION 3.23)
project(telebot)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc -static-libstdc++")
endif()

# VCPKG packages
find_package(SDL3 CONFIG REQUIRED)
find_package(Stb REQUIRED)
# find_package(Boost REQUIRED COMPONENTS
#     system
# )

# Main
# file(GLOB_RECURSE MAIN_SOURCES "src/*.cpp")

# ImGui
file(GLOB_RECURSE IMGUI_SOURCES "lib/imgui/*.cpp")

add_executable(${PROJECT_NAME}
    #${MAIN_SOURCES}
    "test.cpp"
    ${IMGUI_SOURCES}
)
target_include_directories(${PROJECT_NAME} PRIVATE
    include
    lib/imgui
)

# SDL
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3::SDL3
    ${Stb_INCLUDE_DIR}
    # Boost::system
)

# Platform specific
# if (WIN32)
#     target_link_libraries(telebot PRIVATE ws2_32)
# endif()
