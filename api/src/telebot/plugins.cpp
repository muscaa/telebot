#include "telebot/plugins.h"

#include <boost/dll.hpp>
#include <boost/dll/smart_library.hpp>
#include <boost/json.hpp>
#include <boost/function.hpp>
#include <libzippp/libzippp.h>
#include <fstream>

#include "telebot/utils/files.h"
#include "telebot/utils/logging.h"
#include "telebot/utils/platform.h"

namespace telebot::plugins {

namespace log = telebot::utils::logging;

std::map<std::string, Plugin*> loaded_plugins;

Plugin* extract(const boost::filesystem::path& zip_path) {
    log::info("Extracting {}...", zip_path.string());

    if (!boost::filesystem::exists(zip_path)) {
        log::warn("Plugin {} does not exist!", zip_path.string());
        return nullptr;
    }
    
    libzippp::ZipArchive zip(zip_path.string());
    zip.open(libzippp::ZipArchive::ReadOnly);

    libzippp::ZipEntry plugin_json_entry = zip.getEntry("plugin.json");
    boost::json::object plugin_json = boost::json::parse(plugin_json_entry.readAsText()).as_object();

    if (!plugin_json.contains("id")) {
        log::warn("{} doesnt have an id!", zip_path.string());
        return nullptr;
    }

    if (!plugin_json.contains("plugin_lib")) {
        log::warn("{} doesnt have a plugin_lib!", zip_path.string());
        return nullptr;
    }

    if (!plugin_json.contains("plugin_main")) {
        log::warn("{} doesnt have a plugin_main!", zip_path.string());
        return nullptr;
    }

    std::string id = std::string(plugin_json["id"].as_string());
    std::string name = plugin_json.contains("name") ? std::string(plugin_json["name"].as_string()) : id;
    std::string author = plugin_json.contains("author") ? std::string(plugin_json["author"].as_string()) : "unknown";
    std::string version = plugin_json.contains("version") ? std::string(plugin_json["version"].as_string()) : "unknown";
    std::string description = plugin_json.contains("description") ? std::string(plugin_json["description"].as_string()) : "No description.";
    std::string plugin_lib = std::string(plugin_json["plugin_lib"].as_string());
    std::string plugin_main = std::string(plugin_json["plugin_main"].as_string());
    std::string plugin_main_cli = std::string(plugin_json["plugin_main_cli"].as_string());

    if (loaded_plugins.find(id) != loaded_plugins.end()) {
        log::warn("Plugin {} with id {} is already loaded!", zip_path.string(), id);
        return nullptr;
    }

    boost::filesystem::path dir = telebot::utils::files::dir(telebot::utils::files::PLUGINS_DIR / id);
    boost::filesystem::path temp_dir = telebot::utils::files::dir(telebot::utils::files::TEMP_DIR / id);

    for (libzippp::ZipEntry entry : zip.getEntries()) {
        if (entry.isDirectory()) {
            continue;
        }

        boost::filesystem::path extract_path = temp_dir / entry.getName();
        boost::filesystem::path extract_dir = telebot::utils::files::dir(extract_path.parent_path());
        std::string filename = extract_path.filename().string();

        if (filename[0] == '(') {
            size_t pos = filename.find(')');

            if (pos != std::string::npos) {
                std::string system_arch = filename.substr(1, pos - 1);
                size_t dash_pos = system_arch.find('-');

                if (dash_pos != std::string::npos) {
                    std::string system = system_arch.substr(0, dash_pos);
                    std::string arch = system_arch.substr(dash_pos + 1);

                    if (system != telebot::utils::platform::SYSTEM || arch != telebot::utils::platform::ARCH) {
                        continue;
                    }

                    filename = filename.substr(pos + 1);
                    extract_path = extract_dir / filename;
                }
            }
        }

        std::ofstream out(extract_path.string(), std::ios::binary);
        out.write(static_cast<const char*>(entry.readAsBinary()), entry.getSize());
        out.close();
    }
    
    zip.close();

    boost::dll::experimental::smart_library* lib = new boost::dll::experimental::smart_library(temp_dir / (plugin_lib + telebot::utils::platform::LIB_EXT));
    Plugin* plugin = new Plugin(id, name, author, version, description, plugin_lib, plugin_main, plugin_main_cli, zip_path, dir, temp_dir, lib);
    return plugin;
}

Plugin* load(const boost::filesystem::path& zip_path) {
    Plugin* plugin = extract(zip_path);
    if (plugin == nullptr) {
        log::warn("Failed to load plugin from {}", zip_path.string());
        return nullptr;
    }

    log::info("Loading {}...", zip_path.string());

    loaded_plugins[plugin->getId()] = plugin;

    boost::function<void (const telebot::plugins::Plugin&)> main = plugin->getLib()->get_function<void (const telebot::plugins::Plugin&)>(plugin->getPluginMain());
    main(*plugin);

    return plugin;
}

void load_from(const boost::filesystem::path& dir) {
    for (boost::filesystem::directory_iterator it(dir); it != boost::filesystem::directory_iterator {}; it++) {
        boost::filesystem::directory_entry& entry = *it;
        if (!entry.is_regular_file()) {
            continue;
        }

        boost::filesystem::path path = entry.path();
        if (path.extension() != ".zip") {
            continue;
        }

        telebot::plugins::load(path);
    }
}

Plugin* load_cli(const boost::filesystem::path& zip_path) {
    Plugin* plugin = extract(zip_path);
    if (plugin == nullptr) {
        log::warn("Failed to load plugin from {}", zip_path.string());
        return nullptr;
    }

    log::info("Loading {}...", zip_path.string());

    loaded_plugins[plugin->getId()] = plugin;

    boost::function<void (const telebot::plugins::Plugin&)> main_cli = plugin->getLib()->get_function<void (const telebot::plugins::Plugin&)>(plugin->getPluginMainCli());
    main_cli(*plugin);

    return plugin;
}

void load_cli_from(const boost::filesystem::path& dir) {
    for (boost::filesystem::directory_iterator it(dir); it != boost::filesystem::directory_iterator {}; it++) {
        boost::filesystem::directory_entry& entry = *it;
        if (!entry.is_regular_file()) {
            continue;
        }

        boost::filesystem::path path = entry.path();
        if (path.extension() != ".zip") {
            continue;
        }

        telebot::plugins::load_cli(path);
    }
}

} // namespace telebot::plugins
