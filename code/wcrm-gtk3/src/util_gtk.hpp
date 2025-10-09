#ifndef UTIL_GTK_HPP
#define UTIL_GTK_HPP

#include <gtkmm/entry.h>
#include <gtkmm/frame.h>
#include <gtkmm/label.h>
#include <gtkmm/grid.h>
#include <gtkmm/enums.h>
#include <gtkmm/button.h>
#include <gtkmm/textbuffer.h>
#include <gtkmm/textview.h>
#include <gtkmm/scrolledwindow.h>
#include "util_translate.hpp"
#include "utils/string_utils.hpp"

#include <filesystem>
#include <type_traits>

namespace util_gtk {

template <typename Tgui, typename Tvalue>
void value_to_gui(const Tvalue value, Tgui &ui)
{
    if constexpr (std::is_same_v<Tvalue, std::string>) {
        ui.input.set_text(value);
    }
    else {
        ui.input.set_text(value.as_string());
    }
}

template <typename Tgui, typename Tvalue>
void value_from_gui(Tvalue& value, const Tgui &ui)
{
    if constexpr (std::is_same_v<Tvalue, std::string>) {
        value = utils::str_trim(ui.input.get_text());
    }
    else {
        value.from_string(utils::str_trim(ui.input.get_text()));
    }
}

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

struct ObjectChooser {
    struct Chooser : Gtk::Button{
        void set_text(const std::string& text) {this->set_label(text);}
        std::string get_text(void) const {return this->get_label();}
    };
    Gtk::Label label;
    Chooser input;
    std::function<void(void)> cb_on_choose_object;

    void on_choose_clicked()
    {
        if (cb_on_choose_object) cb_on_choose_object();
    }

    ObjectChooser(const std::string label_text, const std::string input_text = "", int width = 20)
    {
        label.set_text(util_translate::translate(label_text));
        std::ignore = input_text;
        std::ignore = width;
        //input.set_text(input_text);
        //input.set_width_chars(width);
        //input.set_max_width_chars(width);
            input.signal_clicked().connect(
                    sigc::mem_fun(*this, &ObjectChooser::on_choose_clicked));
    }
};

struct TextMultilineInput {
    Gtk::Label    label;
#if 1
    struct TextContent : Gtk::Frame
    {
        Gtk::ScrolledWindow window;
        Gtk::TextView       textview;

        TextContent()
        {
            textview.set_can_focus(true);
            textview.set_accepts_tab(false);
            textview.set_wrap_mode(Gtk::WRAP_WORD);

            window.set_focus_on_click(false);
            window.add(textview);
            window.set_hexpand(true);
            window.set_vexpand(true);
            window.set_border_width(3);

            add(window);
        }
        std::string get_text() const { return textview.get_buffer()->get_text();}
        void set_text(const std::string& text) { textview.get_buffer()->set_text(text);}
    } input;
    #else
    struct TextContent : Gtk::ScrolledWindow
    {
        Gtk::TextView       textview;

        TextContent()
        {
            //set_can_focus(false);
            //textview.set_can_focus(true);
            set_focus_on_click(false);
            set_can_focus(false);

            textview.set_focus_on_click(true);
            textview.set_can_focus(true);
            //window.add(textview);
            //window.set_hexpand(true);
            set_border_width(3);

            add(textview);
        }

        std::string get_text() const { return textview.get_buffer()->get_text();}
        void set_text(const std::string& text) { textview.get_buffer()->set_text(text);}
    } input;

    #endif
    TextMultilineInput(const std::string label_text, const std::string input_text = "")
    {
        label.set_text(util_translate::translate(label_text));
        input.set_text(" " + input_text);
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
    void add_full_width(int row, T &element, int height = 1)
    {
        m_grid.attach(element.label, 0, row, 1, height);
        m_grid.attach(element.input, 1, row, 5, height);
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
