#ifndef BASE_MAIN_PANE_HPP
#define BASE_MAIN_PANE_HPP

#include <gtkmm/paned.h>

#include "app_context.hpp"
#include "article_editor.hpp"
#include "article_selector.hpp"

template <class TuiSelector, class TuiEditor>
class BaseMainPanel : public Gtk::Paned {
    private:
        AppContext  &m_app_context;
        TuiEditor   ui_article_editor;
        TuiSelector ui_article_list;

    public:
        ArticleMainPanel(AppContext &app_context)
            : m_app_context{app_context}
            , ui_article_editor{app_context}
            , ui_article_list{app_context}
        {
            set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);

            pack1(ui_article_list);
            pack2(ui_article_editor);
            set_margin_start(20);
            set_margin_end(20);

            ui_article_list.set_callback_on_object_selected([&](Article article) { 
                ui_article_editor.load_object(article); 
            });

            ui_article_editor.set_callback_save_object([&](const Article &article) {
                const auto saved_article = m_app_context.article_manager->save_element(article);
                ui_article_list.refresh_object_list();
//                ui_article_editor.load_object(saved_article);
            });

            activate();
            set_margin_end(20);
        }
};


#endif // BASE_MAIN_PANE_HPP
