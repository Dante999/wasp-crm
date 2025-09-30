#ifndef ARTICLE_MAIN_PANE_HPP
#define ARTICLE_MAIN_PANE_HPP

#include "object_main_panel.hpp"

#include "article_editor.hpp"
#include "article_selector.hpp"

#include <memory>

class ArticleMainPanel : public ObjectMainPanel<Article> {

    public:
        ArticleMainPanel(AppContext &app_context)
            : ObjectMainPanel(app_context,
                              std::make_shared<ArticleEditor>(app_context),
                              std::make_shared<ArticleSelector>(app_context),
                              app_context.article_manager)
        {}
};



#endif // ARTICLE_MAIN_PANE_HPP
