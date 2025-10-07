#include "main_window.hpp"

#include <gtkmm.h>
#include <gdkmm/pixbuf.h>

MainWindow::MainWindow(AppContext &app_context) 
    : m_app_context{app_context}
    , ui_article_panel{app_context}
    , ui_vendor_panel{app_context}
    , ui_customer_panel{app_context}
{
    m_app_context.main_window = this;
    // Set title and border of the window
    set_title("WaspCRM");
//    set_default_size(1600, 1200);
    set_border_width(20);

    auto icon = Gdk::Pixbuf::create_from_file(m_app_context.icon_waspcrm);
    set_icon(icon);


    ui_notebook.append_page(ui_article_panel, util_translate::translate("articles"));
    ui_notebook.append_page(ui_vendor_panel, util_translate::translate("vendors"));
    ui_notebook.append_page(ui_customer_panel, util_translate::translate("customers"));
    ui_notebook.append_page(ui_invoice_panel, util_translate::translate("invoices"));

    add(ui_notebook);

    show_all_children();
}
