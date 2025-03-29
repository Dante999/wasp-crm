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
        icon_placeholder {Gtk::make_managed<Gtk::Image>(basepath / "resources" / "image-placeholder.svg")}
    {}
};

struct AppContext {
        Gtk::Window                       *main_window{nullptr};
        const std::filesystem::path        basepath;
        const Icons                        icons;
        ConfigFile                         configfile;
        const std::filesystem::path        translation_filepath;
        const std::filesystem::path        icon_new_file;
        const std::filesystem::path        icon_save_file;
        const std::filesystem::path        icon_waspcrm;

        std::shared_ptr<IManager<Article>> article_manager;

        AppContext(std::filesystem::path _basepath) :
            basepath  { _basepath},
            icons                { _basepath },
            configfile           { _basepath / "config" / "wasp-crm.conf"},
            translation_filepath { _basepath / "config" / configfile.get_string("languagefile")},
            icon_new_file        { _basepath / "resources" / "icon-create-file.svg"},
            icon_save_file       { _basepath / "resources" / "icon-save-file.svg"},
            icon_waspcrm         { _basepath / "resources" / "icon-wasp-crm.png"}
        {
            //article_manager->refresh_list();
        }

};

#endif // APP_CONFIG_HPP
