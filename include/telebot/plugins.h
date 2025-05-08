#pragma once

#include <string>
#include <boost/filesystem.hpp>

namespace telebot::plugins {

class Plugin {
   private:
    boost::filesystem::path path;
    std::string name;
    std::string version;

   public:
    Plugin(const boost::filesystem::path& plugin_path, bool sub_path = true);

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
