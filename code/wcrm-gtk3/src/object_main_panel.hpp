#ifndef BASE_MAIN_PANE_HPP
#define BASE_MAIN_PANE_HPP

#include <gtkmm/paned.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>


#include "app_context.hpp"
#include "util_gtk.hpp"
#include "object_editor_panel.hpp"
#include "object_selector_panel.hpp"

template <class Tobject>
class ObjectMainPanel : public Gtk::Paned {
    private:
        Gtk::Paned       ui_bottom_hpaned{Gtk::Orientation::ORIENTATION_HORIZONTAL};
        Gtk::Box         ui_top_hbox{Gtk::Orientation::ORIENTATION_HORIZONTAL};
        Gtk::Box         ui_main_vbox{Gtk::Orientation::ORIENTATION_VERTICAL};
        Gtk::Button      ui_button_new;
        Gtk::Button      ui_button_save;


        void on_create_object()
        {
            auto o = m_manager->create_element();
            ui_editor->load_object(o);
        }

        void on_save_object()
        {
            auto obj = ui_editor->get_object();
            const auto saved_obj= m_manager->save_element(obj);
            m_manager->refresh_list();
            ui_selector->refresh_object_list(m_manager->get_list());
            ui_selector->select_object(saved_obj);
        }

        void on_object_selected(Tobject obj)
        {
            const auto unsaved_changes = ui_editor->get_unsaved_changes();

            if (!unsaved_changes.empty()) {
                SPDLOG_WARN("{} unsaved changes!", unsaved_changes.size());
            }


#if 0
            Gtk::MessageDialog dialog(*this,
                    "Unsaved Changes!",
                    false /* use_markup */,
                    Gtk::MessageType::MESSAGE_WARNING,
                    Gtk::BUTTONS_OK_CANCEL);

            dialog.set_secondary_text(
                    "You have unsaved changes!\n"
                    "\n"
                    "Click OK to continue and discard changes\n"
                    "or click CANCEL to stay on the page");

            int result = dialog.run();

            //Handle the response:
            switch(result) {
              case(Gtk::RESPONSE_OK): break;
              case(Gtk::RESPONSE_CANCEL): return;
          }
#endif
            // TODO: check for unsaved changes before loading another obj
            ui_editor->load_object(std::move(obj));
        }

    protected:
        std::shared_ptr<ObjectEditorPanel<Tobject>>   ui_editor;
        std::shared_ptr<ObjectSelectorPanel<Tobject>> ui_selector;
        std::shared_ptr<IManager<Tobject>>            m_manager;

    public:
        ObjectMainPanel(AppContext &app_context,
                  std::shared_ptr<ObjectEditorPanel<Tobject>>   _ui_editor,
                  std::shared_ptr<ObjectSelectorPanel<Tobject>> _ui_selector,
                  std::shared_ptr<IManager<Tobject>>            _manager)
            : ui_editor{_ui_editor}
            , ui_selector{_ui_selector}
            , m_manager{_manager}
        {
            set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);

            util_gtk::set_button_icon(ui_button_new , app_context.icon_new_file);
            util_gtk::set_button_icon(ui_button_save, app_context.icon_save_file);

            ui_top_hbox.pack_start(ui_button_new, false, false);
            ui_top_hbox.pack_start(ui_button_save, false, false);
            ui_top_hbox.set_margin_bottom(30);
            ui_top_hbox.set_spacing(5);

            ui_bottom_hpaned.pack1(*ui_selector);
            ui_bottom_hpaned.pack2(*ui_editor);


            ui_main_vbox.pack_start(ui_top_hbox, false, false);
            ui_main_vbox.pack_start(ui_bottom_hpaned);
            ui_main_vbox.set_margin_top(10);
            ui_main_vbox.set_margin_left(20);
            ui_main_vbox.set_margin_right(20);
            ui_main_vbox.set_margin_bottom(30);

            this->add(ui_main_vbox);

            ui_button_new.signal_clicked().connect(
                    sigc::mem_fun(*this, &ObjectMainPanel::on_create_object));

            ui_button_save.signal_clicked().connect(
                    sigc::mem_fun(*this, &ObjectMainPanel::on_save_object));

            ui_selector->set_callback_on_object_selected([&](Tobject obj) {
               on_object_selected(obj);     
            });

            activate();

            m_manager->refresh_list();
            auto obj_list = m_manager->get_list();
            if (!obj_list.empty()) {
                ui_selector->refresh_object_list(obj_list);

                SPDLOG_INFO("selecting first entry");
                ui_selector->select_object(obj_list.at(0));
            }

        }
};


#endif // BASE_MAIN_PANE_HPP
