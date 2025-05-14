#include "telebot/plugins.h"

#include <boost/dll.hpp>
#include <boost/dll/smart_library.hpp>
#include <boost/json.hpp>
#include <boost/function.hpp>
#include <libzippp.h>
#include <fstream>

#include "telebot/utils/files.h"
#include "telebot/utils/logging.h"
#include "telebot/utils/platform.h"

namespace telebot::plugins {

namespace log = telebot::utils::logging;

std::map<std::string, Plugin*> loaded_plugins;

Plugin* load(const boost::filesystem::path& zip_path, bool sub_path) {
    log::info("Loading {}...", zip_path.string());

    boost::filesystem::path path = sub_path ? telebot::utils::files::PLUGINS_DIR / zip_path : zip_path;
    if (!boost::filesystem::exists(path)) {
        log::warn("Plugin {} does not exist!", zip_path.string());
        return nullptr;
    }
    
    libzippp::ZipArchive zip(path.string());
    zip.open(libzippp::ZipArchive::ReadOnly);

    libzippp::ZipEntry plugin_json_entry = zip.getEntry("plugin.json");
    boost::json::object plugin_json = boost::json::parse(plugin_json_entry.readAsText()).as_object();

    // no id ? return nullptr

    std::string id = std::string(plugin_json["id"].as_string());
    std::string name = std::string(plugin_json["name"].as_string());
    std::string author = std::string(plugin_json["author"].as_string());
    std::string version = std::string(plugin_json["version"].as_string());
    std::string description = std::string(plugin_json["description"].as_string());
    std::string plugin_lib = std::string(plugin_json["plugin_lib"].as_string());
    std::string plugin_main = std::string(plugin_json["plugin_main"].as_string());

    // check id for duplicates

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
    boost::function<void()> main = lib->get_function<void()>(plugin_main);
    main();

    Plugin* plugin = new Plugin(id, name, author, version, description, plugin_lib, plugin_main, path, dir, temp_dir, lib);
    loaded_plugins[id] = plugin;
    return plugin;
}

} // namespace telebot::plugins
