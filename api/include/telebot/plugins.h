#pragma once

#include <string>
#include <map>
#include <boost/filesystem.hpp>
#include <boost/dll/smart_library.hpp>

namespace telebot::plugins {

class Plugin {
   private:
    // plugiun.json
    std::string id;
    std::string name;
    std::string author;
    std::string version;
    std::string description;
    std::string plugin_lib;
    std::string plugin_main;

    // paths
    boost::filesystem::path path;
    boost::filesystem::path dir;
    boost::filesystem::path temp_dir;

    // other
    boost::dll::experimental::smart_library* lib;

   public:
    Plugin(const std::string& id,
        const std::string& name,
        const std::string& author,
        const std::string& version,
        const std::string& description,
        const std::string& plugin_lib,
        const std::string& plugin_main,
        const boost::filesystem::path& path,
        const boost::filesystem::path& dir,
        const boost::filesystem::path& temp_dir,
        boost::dll::experimental::smart_library* lib = nullptr)
        : id(id),
        name(name),
        author(author),
        version(version),
        description(description),
        plugin_lib(plugin_lib),
        plugin_main(plugin_main),
        path(path),
        dir(dir),
        temp_dir(temp_dir),
        lib(lib) {};

    const boost::filesystem::path& getPath() const { return path; }

    const boost::filesystem::path& getDir() const { return dir; }

    const boost::filesystem::path& getTempDir() const { return temp_dir; }

    const std::string& getId() const { return id; }

    const std::string& getName() const { return name; }

    const std::string& getAuthor() const { return author; }

    const std::string& getVersion() const { return version; }

    const std::string& getDescription() const { return description; }

    const std::string& getPluginLib() const { return plugin_lib; }

    const std::string& getPluginMain() const { return plugin_main; }
};

extern std::map<std::string, Plugin*> loaded_plugins;

Plugin* load(const boost::filesystem::path& zip_path, bool sub_path = true);

}  // namespace telebot::plugins
