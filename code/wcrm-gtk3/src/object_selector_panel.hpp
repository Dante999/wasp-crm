#ifndef OBJECT_SELECTOR_PANEL_HPP
#define OBJECT_SELECTOR_PANEL_HPP

#include <functional>

#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/listviewtext.h>
#include <gtkmm/paned.h>
#include <spdlog/spdlog.h>

#include "wcrm-lib/manager/manager_interface.hpp"

template <class T>
class ObjectSelectorPanel : public Gtk::Paned {
    private:
        Gtk::ListViewText            ui_element_list{1};
        Gtk::ButtonBox               ui_button_box;
        Gtk::Button                  ui_button_create{"create"};
        Gtk::Button                  ui_button_refresh{"refresh"};
        std::shared_ptr<IManager<T>> m_manager;
        std::vector<T>               m_cached_objects;
        std::function<void(T)>       m_callback_on_object_selected;

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
        ObjectSelectorPanel(std::shared_ptr<IManager<T>> manager) : m_manager{manager}
        {
            refresh_object_list();

            ui_button_box.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
            ui_button_box.pack_start(ui_button_create);
            ui_button_box.pack_start(ui_button_refresh);

            set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
            pack1(ui_button_box);
            pack2(ui_element_list);

            ui_element_list.signal_cursor_changed().connect(
                sigc::mem_fun(*this, &ObjectSelectorPanel::on_selected_element_changed));

            ui_button_create.signal_clicked().connect(
                sigc::mem_fun(*this, &ObjectSelectorPanel::on_button_create_element_clicked));

            ui_button_refresh.signal_clicked().connect(
                sigc::mem_fun(*this, &ObjectSelectorPanel::on_button_refresh_clicked));
        }

        void set_callback_on_object_selected(std::function<void(T)> cb) { m_callback_on_object_selected = cb; }

        void refresh_object_list()
        {

            SPDLOG_DEBUG("refreshing object list");
            m_manager->refresh_list();
            m_cached_objects = m_manager->get_list();

            SPDLOG_DEBUG("having {} elements cached", m_cached_objects.size());


            ui_element_list.clear_items();


            for (const auto &element : m_cached_objects) {
                std::string display_name = element.get_id_as_string() + " " + element.name;

                ui_element_list.append(display_name);
            }

        }

};

#endif /* OBJECT_SELECTOR_PANEL_HPP */
