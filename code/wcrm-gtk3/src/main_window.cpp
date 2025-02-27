#include "main_window.hpp"


MainWindow::MainWindow(AppContext &app_context) : m_app_context{app_context}, ui_article_panel{app_context}
{
    // Set title and border of the window
    set_title("WaspCRM");
//    set_default_size(1600, 1200);
    set_border_width(20);

    ui_notebook.append_page(ui_article_panel, util_translate::translate("article"));
    ui_notebook.append_page(ui_customer_panel, util_translate::translate("customer"));
    ui_notebook.append_page(ui_invoice_panel, util_translate::translate("invoice"));
    
    add(ui_notebook);

    show_all_children();
}
