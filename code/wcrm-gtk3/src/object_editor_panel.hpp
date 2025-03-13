#ifndef OBJECT_EDITOR_PANEL_HPP
#define OBJECT_EDITOR_PANEL_HPP

// thirdparty
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/flowbox.h>
#include <gtkmm/box.h>
// std
#include <functional>

// locals
#include "app_context.hpp"


template <class Tobject>
class ObjectEditorPanel : public Gtk::Box {

    private:
        Tobject                       m_object{0};


    protected:
        AppContext&    m_app_context;
        Gtk::FlowBox   ui_flowbox;
        virtual void write_to_gui(const Tobject &object) = 0;
        virtual void read_from_gui(Tobject &object)      = 0;

    public:
        ObjectEditorPanel(AppContext &context) : m_app_context{context}
        {
            set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);

            ui_flowbox.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
            ui_flowbox.set_can_focus(false);

            this->pack_start(ui_flowbox, true, true);
        }

        void load_object(Tobject object)
        {
            SPDLOG_DEBUG("load_object()");
            m_object = object;
            write_to_gui(object);
        }

        Tobject get_object() { 
            read_from_gui(m_object);
            return m_object; 
        }

};

#endif /* OBJECT_EDITOR_PANEL_HPP */
