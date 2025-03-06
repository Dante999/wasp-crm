#ifndef OBJECT_SELECTOR_PANEL_HPP
#define OBJECT_SELECTOR_PANEL_HPP

#include <functional>

#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/listviewtext.h>
#include <gtkmm/paned.h>
#include <gtkmm/searchentry.h>
#include <spdlog/spdlog.h>

#include "app_context.hpp"
#include "wcrm-lib/manager/manager_interface.hpp"

template <class T>
class ObjectSelectorPanel : public Gtk::Paned {
    private:
        Gtk::ListViewText            ui_element_list{1};
        Gtk::Box                     ui_top_hbox;
        Gtk::Button                  ui_button_create;
        Gtk::Button                  ui_button_refresh;
        Gtk::SearchEntry             ui_search_entry;
        std::shared_ptr<IManager<T>> m_manager;
        std::vector<T>               m_cached_objects;
        std::function<void(T)>       m_callback_on_object_selected;


    protected:
        virtual std::string get_display_name(const T& element) = 0;

    private:

        void on_selected_element_changed()
        {
            if (ui_element_list.size() == 0) {
                // do nothing on empty list
                return;
            }

            SPDLOG_DEBUG("on_selected_element_changed()");

            if (m_callback_on_object_selected) {
                const auto selected_column = ui_element_list.get_selected().at(0);

                m_callback_on_object_selected(m_cached_objects.at(selected_column));
            }
        }

        void on_button_create_element_clicked()
        {
            SPDLOG_DEBUG("on_button_create_element_clicked()");

            const auto element = m_manager->create_element();
            m_manager->save_element(element);
            refresh_object_list();

            auto model = ui_element_list.get_model();
            const auto rows = model->children();

            if (rows.size() > 0) {
                ui_element_list.set_cursor(model->get_path(--rows.end()));
            }
        }

        void on_button_refresh_clicked()
        {
            SPDLOG_DEBUG("on_button_refresh_clicked()");

            refresh_object_list();
        }

    public:
        ObjectSelectorPanel(std::shared_ptr<IManager<T>> manager, AppContext &context) : m_manager{manager}
        {
            refresh_object_list();

            ui_button_create.set_image(*context.icons.icon_new);
            ui_button_refresh.set_image(*context.icons.icon_refresh);

            ui_top_hbox.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
            ui_top_hbox.pack_start(ui_search_entry, true, true);
            ui_top_hbox.pack_start(ui_button_create, false, false);
            ui_top_hbox.pack_start(ui_button_refresh, false, false);

            ui_element_list.set_column_title(0, "");

            this->set_border_width(10);
            this->set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
            this->pack1(ui_top_hbox, false, false);
            this->pack2(ui_element_list, true, false);

            ui_element_list.signal_cursor_changed().connect(
                sigc::mem_fun(*this, &ObjectSelectorPanel::on_selected_element_changed));

            ui_button_create.signal_clicked().connect(
                sigc::mem_fun(*this, &ObjectSelectorPanel::on_button_create_element_clicked));

            ui_button_refresh.signal_clicked().connect(
                sigc::mem_fun(*this, &ObjectSelectorPanel::on_button_refresh_clicked));
        }

        void set_callback_on_object_selected(std::function<void(T)> cb)
        {
            m_callback_on_object_selected = cb;
        }

        void refresh_object_list()
        {

            SPDLOG_DEBUG("refreshing object list");
            m_manager->refresh_list();
            m_cached_objects = m_manager->get_list();

            SPDLOG_DEBUG("having {} elements cached", m_cached_objects.size());


            ui_element_list.clear_items();


            for (const auto &element : m_cached_objects) {
                // TODO: replace with child-overriden call of get_display_name(element);
                std::string display_name = element.get_id_as_string() + " " + element.name;

                ui_element_list.append(display_name);
            }

        }

};

#endif /* OBJECT_SELECTOR_PANEL_HPP */
