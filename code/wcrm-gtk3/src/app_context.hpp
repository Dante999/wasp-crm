#ifndef APP_CONFIG_HPP
#define APP_CONFIG_HPP

#include "wcrm-lib/manager/article_manager_json.hpp"
#include "utils/config_file.hpp"
// std
#include <filesystem>
#include <memory>

struct AppContext {
        std::filesystem::path              basepath;
        ConfigFile                         configfile;
        std::filesystem::path              translation_filepath;
        std::shared_ptr<IManager<Article>> article_manager;
};

#endif // APP_CONFIG_HPP
