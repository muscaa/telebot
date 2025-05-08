#pragma once

#include <string>
#include <boost/dll.hpp>
#include <boost/json.hpp>
#include <libzippp.h>

namespace telebot::plugins {

class Plugin {
   private:
    boost::filesystem::path path;
    std::string name;
    std::string version;

   public:
    Plugin(const boost::filesystem::path& plugin_path, bool sub_path = true) {
        this->path = sub_path ? boost::dll::program_location() / "plugins" / plugin_path : plugin_path;
        
        libzippp::ZipArchive zip(path.string());
        zip.open(libzippp::ZipArchive::ReadOnly);

        libzippp::ZipEntry plugin_json_entry = zip.getEntry("plugin.json");
        boost::json::object plugin_json = boost::json::parse(plugin_json_entry.readAsText()).as_object();

        this->name = plugin_json["name"].as_string();
        this->version = plugin_json["version"].as_string();

        // extract platform specific library
      
        zip.close();
    }

    const boost::filesystem::path& getPath() const {
        return path;
    }

    const std::string& getName() const {
        return name;
    }

    const std::string& getVersion() const {
        return version;
    }
};

}  // namespace telebot::plugins
