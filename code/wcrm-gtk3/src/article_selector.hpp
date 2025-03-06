#ifndef ARTICLE_SELECTOR_HPP
#define ARTICLE_SELECTOR_HPP

#include "object_selector_panel.hpp"
#include "wcrm-lib/objects/article.hpp"


class ArticleSelector : public ObjectSelectorPanel<Article> {
private:
    std::string get_display_name(const Article& element) override {
            return element.get_id_as_string() + " -> " + element.name;
    }

public:
        ArticleSelector(std::shared_ptr<IManager<Article>> manager, AppContext &context) : ObjectSelectorPanel{manager, context} {}
};

#endif // ARTICLE_SELECTOR_HPP
