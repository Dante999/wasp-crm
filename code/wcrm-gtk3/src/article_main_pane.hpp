#ifndef ARTICLE_MAIN_PANE_HPP
#define ARTICLE_MAIN_PANE_HPP

#include <gtkmm/paned.h>

#include "app_context.hpp"
#include "article_editor.hpp"
#include "article_selector.hpp"

class ArticleMainPanel : public Gtk::Paned {
    private:
        AppContext       &m_app_context;
        ArticleEditor    ui_article_editor;
        ArticleSelector  ui_article_selector;


    public:
        ArticleMainPanel(AppContext &app_context)
            : m_app_context{app_context}
            , ui_article_editor{app_context}
            , ui_article_selector{app_context}
        {
            set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);

            pack1(ui_article_selector);
            pack2(ui_article_editor);
            set_margin_start(20);
            set_margin_end(20);

            ui_article_selector.set_callback_on_object_selected([&](Article article) { 
                ui_article_editor.load_object(article); 
            });

            ui_article_selector.set_callback_on_create_object([&]() {
                auto new_article = m_app_context.article_manager->create_element();
                ui_article_selector.refresh_object_list(m_app_context.article_manager->get_list());
                ui_article_selector.select_object(new_article);
            });

            ui_article_editor.set_callback_save_object([&](const Article &article) {
                const auto saved_article = m_app_context.article_manager->save_element(article);
                m_app_context.article_manager->refresh_list();

                ui_article_selector.refresh_object_list(m_app_context.article_manager->get_list());
                //ui_article_selector.select_object(saved_article);
            });

            m_app_context.article_manager->refresh_list();
            auto article_list = m_app_context.article_manager->get_list();
            if (!article_list.empty()) {
                ui_article_selector.refresh_object_list(article_list);
                ui_article_selector.select_object(article_list.at(0));
            }


            activate();
            set_margin_end(20);
        }
};

#endif // ARTICLE_MAIN_PANE_HPP
