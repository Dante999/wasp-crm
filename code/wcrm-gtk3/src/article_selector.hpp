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
                utils::float_to_string(element.length_cm, 1), 
                utils::float_to_string(element.width_cm, 1),
                utils::float_to_string(element.height_cm, 1));
    }

public:
        ArticleSelector(std::shared_ptr<IManager<Article>> manager, AppContext &context) 
            : ObjectSelectorPanel{manager, context} 
        {
            refresh_object_list();
        }
};

#endif // ARTICLE_SELECTOR_HPP
