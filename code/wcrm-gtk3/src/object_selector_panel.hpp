#ifndef OBJECT_SELECTOR_PANEL_HPP
#define OBJECT_SELECTOR_PANEL_HPP

#include <functional>

#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/listbox.h>
#include <gtkmm/paned.h>
#include <gtkmm/searchentry.h>
#include <gtkmm/scrolledwindow.h>
#include <spdlog/spdlog.h>

#include "app_context.hpp"

template <class T>
class ObjectSelectorPanel : public Gtk::Paned {
    private:
        Gtk::ScrolledWindow          ui_scrolled_window_element_list;
        Gtk::ListBox                 ui_element_list;
        Gtk::Box                     ui_top_hbox;
        Gtk::SearchEntry             ui_search_entry;

        std::vector<std::pair<Gtk::Label,T>>  m_cached_objects;
        std::function<bool(T)>                m_callback_on_object_selected;


    protected:
        virtual std::string get_element_display_name(const T& element) = 0;

    private:
        void on_row_selected(Gtk::ListBoxRow* row);
        int get_index_of_object_with_id(uint64_t obj_id);

    public:
        ObjectSelectorPanel(AppContext &context);

        void set_callback_on_object_selected(std::function<bool(T)> cb) { m_callback_on_object_selected = cb;}
        void select_object(const T& object);
        void refresh_object_list(const std::vector<T>& objects);
};

template <class T>
ObjectSelectorPanel<T>::ObjectSelectorPanel([[maybe_unused]] AppContext &context)
{

    ui_top_hbox.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
    ui_top_hbox.pack_start(ui_search_entry, true, true);

    ui_scrolled_window_element_list.add(ui_element_list);
    ui_scrolled_window_element_list.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    this->set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
    this->pack1(ui_top_hbox, false, false);
    this->pack2(ui_scrolled_window_element_list, true, false);

    ui_element_list.signal_row_selected().connect(
        sigc::mem_fun(*this, &ObjectSelectorPanel::on_row_selected));

}


template <class T>
void ObjectSelectorPanel<T>::on_row_selected(Gtk::ListBoxRow* row)
{
    SPDLOG_INFO("on_row_selected(): row={}", row != nullptr ? row->get_index() : -1);

    if (row == nullptr) return;

    if (m_callback_on_object_selected) {
        const auto should_refresh = m_callback_on_object_selected(
                m_cached_objects.at(static_cast<size_t>(row->get_index())).second);

        // TODO: somehow invoke ui_main_panel that refresh_object_list() is called
        std::ignore = should_refresh;
    }
}


template <class T>
void ObjectSelectorPanel<T>::refresh_object_list(const std::vector<T>& objects)
{
    SPDLOG_INFO("refreshing object list with {} entries", objects.size());


    uint64_t selected_object_id = 0;
    auto current_selected_row = ui_element_list.get_selected_row();
    if (current_selected_row != nullptr) {
        selected_object_id = m_cached_objects.at(static_cast<size_t>(current_selected_row->get_index())).second.get_id();

    }

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

        if (const auto row_index = get_index_of_object_with_id(selected_object_id); row_index > 0) {
            auto row = ui_element_list.get_row_at_index(row_index);
            ui_element_list.select_row(*row);
        }
}


template <class T>
void ObjectSelectorPanel<T>::select_object(const T& object)
{
    const int target_index = get_index_of_object_with_id(object.get_id());

    if (target_index != -1) {
        SPDLOG_INFO("selecting object at row with index {}", target_index);
        auto row = ui_element_list.get_row_at_index(target_index);
        ui_element_list.select_row(*row);
    }
    else {
        SPDLOG_WARN("unable to find row with object id {}", object.get_id());
    }
}

template <class T>
int ObjectSelectorPanel<T>::get_index_of_object_with_id(uint64_t obj_id)
{
    int result = -1;
    for (size_t i=0; i < m_cached_objects.size(); ++i) {

        const auto id = m_cached_objects.at(i).second.get_id();
        if (id == obj_id) {
            result = static_cast<int>(i);
            break;
        }
    }

    return result;
}

#endif /* OBJECT_SELECTOR_PANEL_HPP */
