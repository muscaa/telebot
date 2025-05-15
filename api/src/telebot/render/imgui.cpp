#include "telebot/render/imgui.h"

#include <imgui.h>

#include "telebot/telebot.h"
#include "telebot/events.h"
#include "telebot/plugins.h"

namespace telebot::render::imgui {

static void window_plugins() {
    ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Plugins")) {
        ImGui::End();
        return;
    }

    for (const auto& [id, plugin] : telebot::plugins::loaded_plugins) {
        if (ImGui::CollapsingHeader(plugin->getName().c_str())) {
            ImGui::Text("ID: %s", plugin->getId().c_str());
            ImGui::Text("Author: %s", plugin->getAuthor().c_str());
            ImGui::Text("Version: %s", plugin->getVersion().c_str());
            ImGui::SeparatorText("Description");
            ImGui::Text("%s", plugin->getDescription().c_str());
        }
    }

    ImGui::End();
}

void build() {
    telebot::events::pre_imgui_build();

    window_plugins();

    telebot::events::post_imgui_build();
}

} // namespace telebot::render::imgui
