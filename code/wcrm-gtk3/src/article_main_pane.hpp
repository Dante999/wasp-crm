#ifndef ARTICLE_MAIN_PANE_HPP
#define ARTICLE_MAIN_PANE_HPP

#include <gtkmm/paned.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>


#include "app_context.hpp"
#include "article_editor.hpp"
#include "article_selector.hpp"

class ArticleMainPanel : public Gtk::Paned {
    private:
        AppContext       &m_app_context;

        Gtk::Paned       ui_bottom_hpaned{Gtk::Orientation::ORIENTATION_HORIZONTAL};
        Gtk::Box         ui_top_hbox{Gtk::Orientation::ORIENTATION_HORIZONTAL};
        Gtk::Box         ui_main_vbox{Gtk::Orientation::ORIENTATION_VERTICAL};
        Gtk::Button      ui_button_new;
        Gtk::Button      ui_button_save;

        ArticleEditor    ui_article_editor;
        ArticleSelector  ui_article_selector;

        void on_create_object()
        {
            auto new_article = m_app_context.article_manager->create_element();
//            ui_article_selector.refresh_object_list(m_app_context.article_manager->get_list());
            ui_article_editor.load_object(new_article);
        }

        void on_save_object() {
            auto article = ui_article_editor.get_object();
            const auto saved_article = m_app_context.article_manager->save_element(article);
            m_app_context.article_manager->refresh_list();
            ui_article_selector.refresh_object_list(m_app_context.article_manager->get_list());
            ui_article_selector.select_object(saved_article);
            ui_article_editor.load_object(saved_article); // TODO: remove when ui_article_selector.select_object() works
        }

    public:
        ArticleMainPanel(AppContext &app_context)
            : m_app_context{app_context}
            , ui_article_editor{app_context}
            , ui_article_selector{app_context}
        {
            set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);

            util_gtk::set_button_icon(ui_button_new , app_context.icon_new_file);
            util_gtk::set_button_icon(ui_button_save, app_context.icon_save_file);

            ui_top_hbox.pack_start(ui_button_new, false, false);
            ui_top_hbox.pack_start(ui_button_save, false, false);
            ui_top_hbox.set_margin_bottom(30);
            ui_top_hbox.set_spacing(5);

            ui_bottom_hpaned.pack1(ui_article_selector);
            ui_bottom_hpaned.pack2(ui_article_editor);


            ui_main_vbox.pack_start(ui_top_hbox, false, false);
            ui_main_vbox.pack_start(ui_bottom_hpaned);
            ui_main_vbox.set_margin_top(10);
            ui_main_vbox.set_margin_left(20);
            ui_main_vbox.set_margin_right(20);
            ui_main_vbox.set_margin_bottom(30);

            this->add(ui_main_vbox);

            ui_button_new.signal_clicked().connect(
                    sigc::mem_fun(*this, &ArticleMainPanel::on_create_object));

            ui_button_save.signal_clicked().connect(
                    sigc::mem_fun(*this, &ArticleMainPanel::on_save_object));

            ui_article_selector.set_callback_on_object_selected([&](Article article) {
                // TODO: check for unsaved changes before loading another article
                ui_article_editor.load_object(article);
            });

            m_app_context.article_manager->refresh_list();
            auto article_list = m_app_context.article_manager->get_list();
            if (!article_list.empty()) {
                ui_article_selector.refresh_object_list(article_list);
                ui_article_selector.select_object(article_list.at(0));
            }


            activate();

        }
};



#endif // ARTICLE_MAIN_PANE_HPP
