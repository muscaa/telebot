# Sources
file(GLOB_RECURSE MAIN_SOURCES "src/*.cpp")

add_executable(${TELEBOT_CLI}
    ${MAIN_SOURCES}
)
set_target_properties(${TELEBOT_CLI} PROPERTIES
    PREFIX ""
)
target_include_directories(${TELEBOT_CLI} PRIVATE
    include
)

target_link_libraries(${TELEBOT_CLI} PRIVATE
    ${TELEBOT_API}
)
