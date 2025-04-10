//$Id: main.cc 836 2007-05-09 03:02:38Z jjongsma $ -*- c++ -*-

/* gtkmm example Copyright (C) 2002 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

// thirdparty
#include <gtkmm/main.h>
#include <spdlog/spdlog.h>

#include "app_context.hpp"
#include "main_window.hpp"
#include "util_translate.hpp"

#include "wcrm-lib/manager/article_manager_json.hpp"
#include "wcrm-lib/manager/vendor_manager_json.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        SPDLOG_ERROR("Basepath argument not given!");
        return -1;
    }


    spdlog::set_level(spdlog::level::debug);

    Gtk::Main kit(argc, argv);

    AppContext app_context(argv[1]);
    app_context.article_manager = std::make_shared<ArticleManagerJson>(app_context.basepath / "data" / "articles");
    app_context.vendor_manager  = std::make_shared<VendorManagerJson>(app_context.basepath / "data" / "vendors");

    util_translate::init(app_context.translation_filepath);

    MainWindow main_window{app_context};
    // Shows the window and returns when it is closed.
    Gtk::Main::run(main_window);

    return 0;
}
