#include "main_window.hpp"

#include <iostream>

#include <spdlog/spdlog.h>

MainWindow::MainWindow(AppConfig &app_config) : m_app_config{app_config}, ui_article_panel{app_config}
{
    // Set title and border of the window
    set_title("Simple CRM");
    set_default_size(1600, 1200);
    set_border_width(0);

    add(ui_article_panel);

    show_all_children();
}
