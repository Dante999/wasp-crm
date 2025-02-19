#ifndef CONFIG_FILE_HPP
#define CONFIG_FILE_HPP

#include <filesystem>
#include <map>
#include <string>

class ConfigFile {
    private:
        std::map<std::string, std::string> m_values;

    public:
        ConfigFile() = default;
        ConfigFile(const std::filesystem::path &filepath) { load(filepath); };

        void load(const std::filesystem::path &filepath);

        bool         does_key_exist(const std::string &key);
        std::string &get_string(const std::string &key);
        float        get_float(const std::string &key);
        int          get_int(const std::string &key);
        unsigned int get_uint(const std::string &key);
};

#endif // CONFIG_FILE_HPP
