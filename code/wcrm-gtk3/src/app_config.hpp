#ifndef APP_CONFIG_HPP
#define APP_CONFIG_HPP

#include "wcrm-lib/manager/article_manager_json.hpp"

// std
#include <filesystem>
#include <memory>

struct AppConfig {
        std::filesystem::path              basepath;
        std::filesystem::path              translation_filepath;
        std::shared_ptr<IManager<Article>> article_manager;
};

#endif // APP_CONFIG_HPP