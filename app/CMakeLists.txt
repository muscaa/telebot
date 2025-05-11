# Sources
file(GLOB_RECURSE MAIN_SOURCES "src/*.cpp")

add_executable(${TELEBOT_APP}
    ${MAIN_SOURCES}
)
set_target_properties(${TELEBOT_APP} PROPERTIES
    PREFIX ""
)
target_include_directories(${TELEBOT_APP} PRIVATE
    include
)

target_link_libraries(${TELEBOT_APP} PRIVATE
    ${TELEBOT_API}
)
