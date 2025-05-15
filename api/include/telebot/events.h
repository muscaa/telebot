#pragma once

#include <boost/signals2.hpp>
#include <SDL3/SDL.h>

namespace telebot::events {

extern boost::signals2::signal<void ()> tick;
extern boost::signals2::signal<void (SDL_Scancode code, bool repeat)> key_down;
extern boost::signals2::signal<void (SDL_Scancode code)> key_up;
extern boost::signals2::signal<void ()> pre_imgui_build;
extern boost::signals2::signal<void ()> post_imgui_build;
extern boost::signals2::signal<void ()> pre_render;
extern boost::signals2::signal<void ()> render;
extern boost::signals2::signal<void ()> post_render;

} // namespace telebot::events
