#ifndef UTIL_GTK_HPP
#define UTIL_GTK_HPP

#include <gtkmm/entry.h>
#include <gtkmm/frame.h>
#include <gtkmm/label.h>
#include <gtkmm/grid.h>
#include <gtkmm/enums.h>
#include <gtkmm/button.h>

#include "util_translate.hpp"

#include <filesystem>

namespace util_gtk {

inline void set_button_icon(Gtk::Button &button, const std::filesystem::path icon_path)
{
    Gtk::Widget *icon = Gtk::make_managed<Gtk::Image>(icon_path);
    button.set_vexpand(false);
    button.set_image(*icon);
}

struct Placeholder {
    Gtk::Label label;
    Gtk::Label input;
};

struct TextInput {
    Gtk::Label label;
    Gtk::Entry input;

    TextInput(const std::string label_text, const std::string input_text = "", int width = 20)
    {
        label.set_text(util_translate::translate(label_text));
        input.set_text(input_text);
        input.set_width_chars(width);
        input.set_max_width_chars(width);
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
        input.set_max_width_chars(width);

        input.set_sensitive(false);
        input.set_editable(true);
    }
};

struct FrameFormGrid : Gtk::Frame {
    Gtk::Grid m_grid;

    FrameFormGrid(const std::string &name)
    {
        m_grid.set_row_spacing(2);
        m_grid.set_column_spacing(10);
        m_grid.set_margin_top(10);
        m_grid.set_margin_bottom(10);
        m_grid.set_margin_left(10);
        m_grid.set_margin_right(10);

        this->set_label(util_translate::translate(name));
        this->add(m_grid);
    }
};

struct FrameFormGrid2 : FrameFormGrid {
    FrameFormGrid2(const std::string &name) : FrameFormGrid{name} {}

    template <class T>
    void add_left(int row, T &element) 
    {
        m_grid.attach(element.label, 0, row, 1, 1);
        m_grid.attach(element.input, 1, row, 1, 1);
    }
    
    template <class T>
    void add_right(int row, T &element) 
    {
        m_grid.attach(element.label, 3, row, 1, 1);
        m_grid.attach(element.input, 4, row, 1, 1);
    }
    
    template <class T>
    void add_full_width(int row, T &element) 
    {
        m_grid.attach(element.label, 0, row, 1, 1);
        m_grid.attach(element.input, 1, row, 5, 1);
    }
};


template<size_t NUM_COLUMNS>
struct FrameFormGridRow : FrameFormGrid{
    std::array<int, NUM_COLUMNS> m_row_counter {0};


    FrameFormGridRow(const std::string &name) : FrameFormGrid(name){}

    template <class T>
    void add_element(T &element, int column = 0, int width = 1, int height = 1)
    {
        m_grid.attach(element.label, 0+(column*2), m_row_counter.at(static_cast<size_t>(column)));
        m_grid.attach(element.input, 1+(column*2), m_row_counter.at(static_cast<size_t>(column)), width, height);
        m_row_counter.at(static_cast<size_t>(column))++;
    }

    void add_spacer(int column = 0)
    {
        m_row_counter.at(static_cast<size_t>(column))++;
    }

};

} // namespace util_gtk

#endif // UTIL_GTK_HPP
