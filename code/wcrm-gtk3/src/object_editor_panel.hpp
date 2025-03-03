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

template <class T>
class ObjectEditorPanel : public Gtk::Box {

    private:
        T                             m_object{0};
        std::function<void(T object)> m_callback_on_save_object;

        Gtk::Button    ui_save_button{"save"};
        Gtk::ButtonBox ui_button_box;

    private:
        void on_button_save_object_clicked()
        {
            read_from_gui(m_object);

            if (m_callback_on_save_object) {
                m_callback_on_save_object(m_object);
            }
        }

    protected:
        Gtk::FlowBox   ui_flowbox;
        virtual void write_to_gui(const T &object) = 0;
        virtual void read_from_gui(T &object)      = 0;

    public:
        ObjectEditorPanel()
        {
            set_margin_start(20);
            set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);

            ui_button_box.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
            ui_button_box.add(ui_save_button);

            ui_flowbox.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
            ui_flowbox.set_can_focus(false);
            
            this->pack_start(ui_button_box, false, false);
            this->pack_start(ui_flowbox, true, true);

            ui_save_button.signal_clicked().connect(
                sigc::mem_fun(*this, &ObjectEditorPanel::on_button_save_object_clicked));
        }

        void load_object(T object)
        {
            m_object = object;
            write_to_gui(object);
        }

        void set_callback_save_object(std::function<void(T object)> cb) { m_callback_on_save_object = cb; }
};

#endif /* OBJECT_EDITOR_PANEL_HPP */
