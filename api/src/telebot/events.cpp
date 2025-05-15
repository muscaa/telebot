#include "telebot/events.h"

namespace telebot::events {

boost::signals2::signal<void ()> tick;
boost::signals2::signal<void (SDL_Scancode code, bool repeat)> key_down;
boost::signals2::signal<void (SDL_Scancode code)> key_up;
boost::signals2::signal<void ()> pre_imgui_build;
boost::signals2::signal<void ()> post_imgui_build;
boost::signals2::signal<void ()> pre_render;
boost::signals2::signal<void ()> render;
boost::signals2::signal<void ()> post_render;

} // namespace telebot::events
