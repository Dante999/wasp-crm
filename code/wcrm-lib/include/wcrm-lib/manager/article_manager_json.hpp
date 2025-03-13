#ifndef IARTICLE_MANAGER_JSON_HPP
#define IARTICLE_MANAGER_JSON_HPP

#include "manager_interface.hpp"

#include "wcrm-lib/objects/article.hpp"

#include <spdlog/spdlog.h>

#include <filesystem>


class ArticleManagerJson : public IManager<Article> {
    private:
        const std::filesystem::path m_articles_basedir;

        std::string generate_folder_name(const Article &article);

        Article read_json_file(const std::filesystem::path &filepath);

        void do_refresh_list() override;
        Article do_save_element(Article element) override;

    public:
        ArticleManagerJson(const std::filesystem::path articles_basedir) : m_articles_basedir{articles_basedir} {
            if (!std::filesystem::exists(m_articles_basedir)) {
                std::filesystem::create_directories(m_articles_basedir);
                SPDLOG_INFO("articles basedir created since it didn't exist: {}", m_articles_basedir.string());
            }
        }
        ~ArticleManagerJson() {}

};

#endif // IARTICLE_MANAGER_HPP
