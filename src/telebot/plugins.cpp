#include "telebot/plugins.h"

#include <boost/dll.hpp>
#include <boost/json.hpp>
#include <libzippp.h>
#include <SDL3/SDL.h>

#include "telebot/utils/files.h"

namespace telebot::plugins {

Plugin::Plugin(const boost::filesystem::path& plugin_path, bool sub_path) {
    SDL_Log("Loading plugin: %s", plugin_path.c_str());

    this->path = sub_path ? telebot::utils::files::PLUGINS_DIR / plugin_path : plugin_path;
    
    libzippp::ZipArchive zip(path.string());
    zip.open(libzippp::ZipArchive::ReadOnly);

    libzippp::ZipEntry plugin_json_entry = zip.getEntry("plugin.json");
    boost::json::object plugin_json = boost::json::parse(plugin_json_entry.readAsText()).as_object();

    this->name = plugin_json["name"].as_string();
    this->author = plugin_json["author"].as_string();
    this->version = plugin_json["version"].as_string();

    SDL_Log("%s v%s (%s)", name.c_str(), version.c_str(), author.c_str());

    // extract platform specific library
    
    zip.close();
}

} // namespace telebot::plugins
