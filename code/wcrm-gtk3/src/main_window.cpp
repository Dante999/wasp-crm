#include "main_window.hpp"


MainWindow::MainWindow(AppContext &app_context) : m_app_context{app_context}, ui_article_panel{app_context}
{
    // Set title and border of the window
    set_title("WaspCRM");
    set_default_size(1600, 1200);
    set_border_width(0);

    add(ui_article_panel);

    show_all_children();
}
