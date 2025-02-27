#ifndef ARTICLE_MAIN_PANE_HPP
#define ARTICLE_MAIN_PANE_HPP

#include <gtkmm/paned.h>

#include "app_context.hpp"
#include "article_editor.hpp"
#include "object_selector_panel.hpp"

class ArticleMainPanel : public Gtk::Paned {
    private:
        AppContext                   &m_app_context;
        ArticleEditor                ui_article_editor;
        ObjectSelectorPanel<Article> ui_article_list;

    public:
        ArticleMainPanel(AppContext &app_context)
            : m_app_context{app_context}
            , ui_article_list{app_context.article_manager, app_context}
        {
            set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);

            pack1(ui_article_list);
            pack2(ui_article_editor);
            set_margin_start(20);
            set_margin_end(20);

            ui_article_list.set_callback_on_object_selected(
                [&](Article article) { ui_article_editor.load_object(article); });

            ui_article_editor.set_callback_save_object([&](const Article &article) {
                const auto saved_article = m_app_context.article_manager->save_element(article);
                ui_article_editor.load_object(saved_article);
                ui_article_list.refresh_object_list();
            });

            activate();
            set_margin_end(20);
        }
};

#endif // ARTICLE_MAIN_PANE_HPP
