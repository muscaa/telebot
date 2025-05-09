#include "telebot/plugins.h"

#include <boost/dll.hpp>
#include <boost/json.hpp>
#include <libzippp.h>

#include "telebot/utils/files.h"
#include "telebot/utils/logging.h"

namespace telebot::plugins {

namespace log = telebot::utils::logging;

Plugin::Plugin(const boost::filesystem::path& plugin_path, bool sub_path) {
    log::info("Loading plugin: {}", "mata");

    this->path = sub_path ? telebot::utils::files::PLUGINS_DIR / plugin_path : plugin_path;

    if (!boost::filesystem::exists(path)) {
        log::warn("Plugin {} does not exist!", plugin_path.string());
    }
    
    libzippp::ZipArchive zip(path.string());
    zip.open(libzippp::ZipArchive::ReadOnly);

    libzippp::ZipEntry plugin_json_entry = zip.getEntry("plugin.json");
    boost::json::object plugin_json = boost::json::parse(plugin_json_entry.readAsText()).as_object();

    this->name = plugin_json["name"].as_string();
    this->author = plugin_json["author"].as_string();
    this->version = plugin_json["version"].as_string();

    log::info("{} v{} ({})", name, version, author);

    // extract platform specific library
    
    zip.close();
}

} // namespace telebot::plugins
