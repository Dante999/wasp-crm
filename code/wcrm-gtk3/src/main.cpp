#include <gtkmm/main.h>
#include <spdlog/spdlog.h>

#include "app_context.hpp"
#include "main_window.hpp"
#include "util_translate.hpp"

#include "wcrm-lib/manager/article_manager_json.hpp"
#include "wcrm-lib/manager/vendor_manager_json.hpp"
#include "wcrm-lib/manager/customer_manager_json.hpp"
#include "wcrm-lib/manager/invoice_manager_json.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        SPDLOG_ERROR("Basepath argument not given!");
        return -1;
    }


    spdlog::set_level(spdlog::level::debug);

    Gtk::Main kit(argc, argv);

    AppContext app_context(argv[1]);
    app_context.article_manager  = std::make_shared<ArticleManagerJson>(app_context.basepath / "data" / "articles");
    app_context.vendor_manager   = std::make_shared<VendorManagerJson>(app_context.basepath / "data" / "vendors");
    app_context.customer_manager = std::make_shared<CustomerManagerJson>(app_context.basepath / "data" / "customers");
    app_context.invoice_manager  = std::make_shared<InvoiceManagerJson>(app_context.basepath / "data" / "invoices");

    util_translate::init(app_context.translation_filepath);

    MainWindow main_window{app_context};
    // Shows the window and returns when it is closed.
    Gtk::Main::run(main_window);

    return 0;
}
