#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <gtkmm/listviewtext.h>
#include <gtkmm/paned.h>
#include <gtkmm/window.h>
#include <gtkmm/notebook.h>

#include "app_context.hpp"
#include "article_main_panel.hpp"
#include "vendor_main_panel.hpp"
#include "customer_main_panel.hpp"

class MainWindow : public Gtk::Window {
    private:
        AppContext        &m_app_context;
        ArticleMainPanel  ui_article_panel;
        VendorMainPanel   ui_vendor_panel;
        CustomerMainPanel ui_customer_panel;
        Gtk::Paned        ui_invoice_panel;
        Gtk::Notebook     ui_notebook;

    public:
        MainWindow(AppContext &app_context);
};

#endif // MAIN_WINDOW_HPP
