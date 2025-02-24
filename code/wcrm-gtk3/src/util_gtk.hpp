#ifndef UTIL_GTK_HPP
#define UTIL_GTK_HPP

#include <gtkmm/entry.h>
#include <gtkmm/frame.h>
#include <gtkmm/label.h>

#include "util_translate.hpp"

namespace util_gtk {

struct TextInput {
        Gtk::Label label;
        Gtk::Entry input;

        TextInput(const std::string label_text, const std::string input_text = "", int width = 20)
        {
            label.set_text(util_translate::translate(label_text));
            input.set_text(input_text);
            input.set_width_chars(width);
        }
};

struct TextMultilineInput {
        Gtk::Label label;
        Gtk::Entry input;

        TextMultilineInput(const std::string label_text, const std::string input_text = "", int width = 20)
        {
            label.set_text(util_translate::translate(label_text));
            input.set_text(input_text);
            input.set_width_chars(width);
        }
};

struct TextInputReadonly {
        Gtk::Label label;
        Gtk::Entry input;

        TextInputReadonly(const std::string label_text, const std::string input_text = "", int width = 20)
        {
            label.set_text(util_translate::translate(label_text));
            input.set_text(input_text);
            input.set_width_chars(width);

            input.set_editable(false);
            input.set_can_focus(false);
        }
};

struct FrameFormLayout : Gtk::Frame {

        int       column = 0;
        Gtk::Grid m_grid;

        FrameFormLayout(const std::string &name)
        {
            m_grid.set_row_spacing(2);
            m_grid.set_column_spacing(10);

            this->set_can_focus(false);
            this->set_label(name);
            // m_Frame.set_label_align(Gtk::ALIGN_END, Gtk::ALIGN_START);
            this->set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
            this->add(m_grid);
        }

        template <class T>
        void add_element(T &element)
        {
            m_grid.attach(element.label, 0, column);
            m_grid.attach(element.input, 1, column);
            column++;
        }
};

} // namespace util_gtk

#endif // UTIL_GTK_HPP
