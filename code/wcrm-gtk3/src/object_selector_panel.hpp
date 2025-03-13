#ifndef OBJECT_SELECTOR_PANEL_HPP
#define OBJECT_SELECTOR_PANEL_HPP

#include <functional>

#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/buttonbox.h>
//#include <gtkmm/listviewtext.h>
#include <gtkmm/listbox.h>
#include <gtkmm/paned.h>
#include <gtkmm/searchentry.h>
#include <spdlog/spdlog.h>

#include "app_context.hpp"

template <class T>
class ObjectSelectorPanel : public Gtk::Paned {
    private:
        Gtk::ListBox                 ui_element_list;
        Gtk::Box                     ui_top_hbox;
        Gtk::SearchEntry             ui_search_entry;

        std::vector<std::pair<Gtk::Label,T>>  m_cached_objects;
        std::function<void(T)>                m_callback_on_object_selected;


    protected:
        virtual std::string get_element_display_name(const T& element) = 0;

    private:
        void on_row_selected(Gtk::ListBoxRow* row);

    public:
        ObjectSelectorPanel(AppContext &context);

        void set_callback_on_object_selected(std::function<void(T)> cb) { m_callback_on_object_selected = cb;}
        void select_object(const T& object);
        void refresh_object_list(const std::vector<T>& objects);
};

template <class T>
ObjectSelectorPanel<T>::ObjectSelectorPanel([[maybe_unused]] AppContext &context)
{

    ui_top_hbox.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
    ui_top_hbox.pack_start(ui_search_entry, true, true);


    this->set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
    this->pack1(ui_top_hbox, false, false);
    this->pack2(ui_element_list, true, false);

    ui_element_list.signal_row_selected().connect(
        sigc::mem_fun(*this, &ObjectSelectorPanel::on_row_selected));

}

template <class T>
void ObjectSelectorPanel<T>::on_row_selected(Gtk::ListBoxRow* row)
{
    SPDLOG_INFO("on_row_selected()");

    if (row == nullptr) return;

    if (m_callback_on_object_selected) {
        m_callback_on_object_selected(m_cached_objects.at(row->get_index()).second);
    }
}

template <class T>
void ObjectSelectorPanel<T>::refresh_object_list(const std::vector<T>& objects)
{
    SPDLOG_INFO("refreshing object list with {} entries", objects.size());


    for (auto child : ui_element_list.get_children()) {
        ui_element_list.remove(*child);
    }
   

    m_cached_objects.clear();
    m_cached_objects.reserve(objects.size());

    for (const auto& object: objects) {
        m_cached_objects.emplace_back(
                std::make_pair(
                    Gtk::Label(get_element_display_name(object), Gtk::Align::ALIGN_START, Gtk::Align::ALIGN_START), 
                    object
                )
        );

        ui_element_list.append(m_cached_objects.back().first);

    }

        ui_element_list.show_all_children();
}


template <class T>
void ObjectSelectorPanel<T>::select_object(const T& object)
{
    std::ignore = object;
// TODO
#if 0
    const auto target_name = get_element_display_name(object);

    for (size_t i=0; i < m_cached_objects.size(); ++i) {
        if (m_cached_objects.at(i).get_id() == object.get_id()) {
            ui_element_list.set_cursor(ui_element_list.get_model()->children()->get_value(i)->get
        }

    }
#if 0
        if (element.get_id_as_string() == last_selected_id) {
            auto model = ui_element_list.get_model();
            const auto rows = model->children();

            if (rows.size() > 0) {
                ui_element_list.set_cursor(model->get_path(--rows.end()));
            }

        }
#endif
#endif
}


#endif /* OBJECT_SELECTOR_PANEL_HPP */
