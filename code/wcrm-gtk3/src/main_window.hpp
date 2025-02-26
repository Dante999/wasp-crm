#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <gtkmm/listviewtext.h>
#include <gtkmm/paned.h>
#include <gtkmm/window.h>


#include "app_context.hpp"
#include "article_main_pane.hpp"

class MainWindow : public Gtk::Window {
    private:
        AppContext       &m_app_context;
        ArticleMainPanel ui_article_panel;

    public:
        MainWindow(AppContext &app_context);
};

#endif // MAIN_WINDOW_HPP
