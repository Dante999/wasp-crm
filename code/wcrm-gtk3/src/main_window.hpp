#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <gtkmm/listviewtext.h>
#include <gtkmm/paned.h>
#include <gtkmm/window.h>


#include "app_config.hpp"
#include "article_main_pane.hpp"

class MainWindow : public Gtk::Window {
    private:
        AppConfig       &m_app_config;
        ArticleMainPanel ui_article_panel;

    public:
        MainWindow(AppConfig &app_config);
};

#endif // MAIN_WINDOW_HPP
