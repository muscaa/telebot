#pragma once

#include <boost/signals2.hpp>
#include <SDL3/SDL.h>

#include "telebot/api.h"
#include "telebot/plugins.h"

namespace telebot::events {

extern API boost::signals2::signal<void ()> tick;
extern API boost::signals2::signal<void (SDL_Scancode code, bool repeat)> key_down;
extern API boost::signals2::signal<void (SDL_Scancode code)> key_up;
extern API boost::signals2::signal<void ()> pre_imgui_build;
extern API boost::signals2::signal<void (const telebot::plugins::Plugin&)> imgui_plugin;
extern API boost::signals2::signal<void ()> post_imgui_build;
extern API boost::signals2::signal<void ()> pre_render;
extern API boost::signals2::signal<void ()> render;
extern API boost::signals2::signal<void ()> post_render;

} // namespace telebot::events
