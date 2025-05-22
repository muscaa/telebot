# Sources
file(GLOB_RECURSE MAIN_SOURCES "src/*.cpp")
file(GLOB_RECURSE IMGUI_SOURCES "lib/imgui/src/*.cpp")
file(GLOB_RECURSE TCP_SERVER_CLIENT_SOURCES "lib/tcp_server_client/src/*.cpp")

add_library(${TELEBOT_API} SHARED
    ${MAIN_SOURCES}
    ${IMGUI_SOURCES}
    ${TCP_SERVER_CLIENT_SOURCES}
)
set_target_properties(${TELEBOT_API} PROPERTIES
    PREFIX ""
)
target_include_directories(${TELEBOT_API} PUBLIC
    include
    lib/imgui/include
    lib/tcp_server_client/include
)
target_compile_definitions(${TELEBOT_API} PRIVATE
    API_EXPORT
)

# VCPKG links
target_link_libraries(${TELEBOT_API} PUBLIC
    SDL3::SDL3
    ${Stb_INCLUDE_DIR}
    libzippp::libzippp
    Boost::system
    Boost::dll
    Boost::json
    Boost::signals2
)

# Platform specific
if (WIN32)
    target_link_libraries(${TELEBOT_API} PRIVATE ws2_32)
endif()
