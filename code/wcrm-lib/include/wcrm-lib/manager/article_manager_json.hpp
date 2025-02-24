#ifndef IARTICLE_MANAGER_JSON_HPP
#define IARTICLE_MANAGER_JSON_HPP

#include "manager_interface.hpp"

#include "wcrm-lib/objects/article.hpp"

#include <filesystem>

class ArticleManagerJson : public IManager<Article> {
    private:
        const std::filesystem::path m_articles_basedir;

        std::string generate_folder_name(const Article &article);

        Article read_json_file(const std::filesystem::path &filepath);

        void do_refresh_list() override;

    public:
        ArticleManagerJson(const std::filesystem::path articles_basedir) : m_articles_basedir{articles_basedir} {}
        ~ArticleManagerJson() {}

        Article save_element(Article element) override;
};

#endif // IARTICLE_MANAGER_HPP
