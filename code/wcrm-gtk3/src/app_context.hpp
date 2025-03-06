#ifndef APP_CONFIG_HPP
#define APP_CONFIG_HPP

#include "wcrm-lib/manager/article_manager_json.hpp"
#include "utils/config_file.hpp"
// std
#include <filesystem>
#include <memory>
#include <gtkmm/image.h>
#include <gtkmm/icontheme.h>
struct Icons {
    Gtk::Widget *icon_new;
    Gtk::Widget *icon_refresh;
    Gtk::Widget *icon_placeholder;

    Icons(std::filesystem::path basepath) :
        icon_new         {Gtk::make_managed<Gtk::Image>(basepath / "resources" / "icon-new_16x16.svg")},
        icon_refresh     {Gtk::make_managed<Gtk::Image>(basepath / "resources" / "icon-refresh_16x16.svg")},
        icon_placeholder {Gtk::make_managed<Gtk::Image>(basepath / "resources" / "image-placeholder.svg")}
    {}
};

struct AppContext {
        const std::filesystem::path        basepath;
        ConfigFile                         configfile;
        const std::filesystem::path        translation_filepath;
        std::shared_ptr<IManager<Article>> article_manager;
        const Icons                        icons;

        AppContext(std::filesystem::path _basepath) :
            basepath  { _basepath},
            configfile           { _basepath / "config" / "wasp-crm.conf"},
            translation_filepath { _basepath / "config" / configfile.get_string("languagefile")},
            icons                { _basepath }
        {}

};

#endif // APP_CONFIG_HPP
