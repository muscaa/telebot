#pragma once

#include <string>
#include <boost/filesystem.hpp>

namespace telebot::plugins {

class Plugin {
   private:
    boost::filesystem::path path;
    boost::filesystem::path dir;
    boost::filesystem::path temp_dir;

    std::string id;
    std::string name;
    std::string author;
    std::string version;
    std::string description;
    std::string plugin_lib;
    std::string plugin_main;

   public:
    Plugin(const boost::filesystem::path& plugin_path, bool sub_path = true);

    const boost::filesystem::path& getPath() const {
        return path;
    }

    const boost::filesystem::path& getDir() const {
        return dir;
    }

    const boost::filesystem::path& getTempDir() const {
        return temp_dir;
    }

    const std::string& getId() const {
        return id;
    }

    const std::string& getName() const {
        return name;
    }

    const std::string& getAuthor() const {
        return author;
    }

    const std::string& getVersion() const {
        return version;
    }

    const std::string& getDescription() const {
        return description;
    }

    const std::string& getPluginLib() const {
        return plugin_lib;
    }

    const std::string& getPluginMain() const {
        return plugin_main;
    }
};

}  // namespace telebot::plugins
