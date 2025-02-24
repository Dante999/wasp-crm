#include "wcrm-lib/manager/article_manager_json.hpp"

// std
#include <algorithm>
#include <fstream>

// thirdparty
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include "utils/filesystem_utils.hpp"
#include "utils/string_utils.hpp"

using json = nlohmann::json;

std::string ArticleManagerJson::generate_folder_name(const Article &article)
{
    std::string name = article.get_id_as_string() + "__" + article.name;

    return utils::str_replace(name, " ", "_");
}

Article ArticleManagerJson::read_json_file(const std::filesystem::path &filepath)
{
    std::ifstream f(filepath);

    json data = json::parse(f);

    Article article{data["id"].get<uint64_t>()};

    article.created_at = data["created_at"];
    article.modfied_at = data["last_modified_at"];

    article.name        = data["name"];
    article.description = data["description"];

    return article;
}

void ArticleManagerJson::do_refresh_list()
{
    SPDLOG_INFO("loading articles...");
#if 0
    const auto folder_prefix = Article{0}.get_id_prefix();

    const auto article_dirs = utils::get_directories(m_articles_basedir);

    for (const auto &dir : article_dirs) {
        if (!utils::str_starts_with(dir, folder_prefix)) {
            SPDLOG_DEBUG("skipped folder {} because it does not start with correct prefix {}", dir, folder_prefix);
            continue;
        }

        std::filesystem::path article_filepath = m_articles_basedir / dir / "article_info.json";

        if (!std::filesystem::exists(article_filepath)) {
            SPDLOG_DEBUG("skipped folder {} because file does not exist: {}", dir, article_filepath.string());
            continue;
        }

        m_elements.emplace_back(read_json_file(article_filepath));

        SPDLOG_DEBUG("successfully loaded {}", article_filepath.string());
    }
#endif 

    for(const auto & entry : std::filesystem::directory_iterator(m_articles_basedir)) {

        m_elements.emplace_back(read_json_file(entry.path()));

        SPDLOG_DEBUG("successfully loaded {}", article_filepath.string());
    }
    SPDLOG_INFO("finished loading {} Articles", m_elements.size());
}

Article ArticleManagerJson::save_element(Article article)
{

    SPDLOG_INFO("saving article {}...", article.get_id_as_string());
#if 0 // needed in future maybe
    const auto article_dirs = utils::get_directories(m_articles_basedir);

    const auto it = std::find_if(
        std::begin(article_dirs), std::end(article_dirs),
        [article_id = article.get_id_as_string()](const auto d) { return utils::str_starts_with(d, article_id); });

    std::filesystem::path article_dir;

    if (it != std::end(article_dirs)) {
        article_dir = *it;
        SPDLOG_DEBUG("article folder already exists: {}", article_dir.string());
    }
    else {
        article_dir = generate_folder_name(article);
        std::filesystem::create_directory(m_articles_basedir / article_dir);
        SPDLOG_DEBUG("creating article folder: {}", article_dir.string());
    }
#endif
    const std::string filename                   = article.get_id_as_string() + ".json";
    const std::filesystem::path article_filepath = m_articles_basedir / filename;

    article.modfied_at = utils::get_current_datetime();

    // clang-format off
    json data = {
        {"id"              , article.get_id()},                 
        {"created_at"      , article.created_at},       
        {"last_modified_at", article.modfied_at}, 
        {"name"            , article.name},               
        {"description"     , article.description}, 
    };
    // clang-format on

    std::ofstream o(article_filepath);
    o << data.dump(4) << std::endl;
    SPDLOG_INFO("successfully saved {}", article_filepath.string());

    return article;
}
