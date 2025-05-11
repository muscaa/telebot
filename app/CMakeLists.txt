# Sources
file(GLOB_RECURSE MAIN_SOURCES "src/*.cpp")

add_executable(${TELEBOT_APP}
    ${MAIN_SOURCES}
)
target_include_directories(${TELEBOT_APP} PRIVATE
    include
)

target_link_libraries(${TELEBOT_APP} PRIVATE
    ${TELEBOT_API}
)
