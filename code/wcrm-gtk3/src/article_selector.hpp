#ifndef ARTICLE_SELECTOR_HPP
#define ARTICLE_SELECTOR_HPP

#include "object_selector_panel.hpp"
#include "wcrm-lib/objects/article.hpp"
#include "utils/string_utils.hpp"

#include <fmt/format.h>
class ArticleSelector : public ObjectSelectorPanel<Article> {
public:
    std::string get_element_display_name(const Article& element) override {
        std::string new_name = element.name;

        return fmt::format("{}__{}__L{}xB{}xH{}cm",
                element.get_id_as_string(),
                utils::str_replace(new_name, " ", "_"),
                element.length_cm.as_string(),
                element.width_cm.as_string(),
                element.height_cm.as_string());
    }

public:
    using ObjectSelectorPanel::ObjectSelectorPanel;
};

#endif // ARTICLE_SELECTOR_HPP
