#ifndef OBJECT_EDITOR_PANEL_HPP
#define OBJECT_EDITOR_PANEL_HPP

// thirdparty
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/flowbox.h>
#include <gtkmm/box.h>
#include <gtkmm/messagedialog.h>

// locals
#include "app_context.hpp"
#include "wcrm-lib/objects/object_comparator.hpp"

#include <spdlog/spdlog.h>

template <class Tobject>
class ObjectEditorPanel : public Gtk::Box {

    private:
        Tobject m_object_old{0};


    protected:
        AppContext&  m_app_context;
        Tobject      m_object{0};
        Gtk::VBox    ui_mainpanel;

        virtual void write_to_gui(const Tobject &object) = 0;
        virtual void read_from_gui(Tobject &object)      = 0;

    public:
        ObjectEditorPanel(AppContext &context) : m_app_context{context}
        {
            set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);

            this->set_margin_left(10);
            this->pack_start(ui_mainpanel, true, true);
        }

        std::vector<CompareDiff> get_unsaved_changes()
        {
            read_from_gui(m_object);
            return get_object_diff(m_object_old, m_object);

        }

        void load_object(Tobject object)
        {
            SPDLOG_DEBUG("load_object()");
            m_object_old = object;
            m_object     = object;
            write_to_gui(object);
        }

        Tobject get_object() {
            read_from_gui(m_object);
            return m_object;
        }

};

#endif /* OBJECT_EDITOR_PANEL_HPP */
