#ifndef BASE_MAIN_PANE_HPP
#define BASE_MAIN_PANE_HPP

#include <gtkmm/paned.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include <sstream>

#include "app_context.hpp"
#include "util_gtk.hpp"
#include "object_editor_panel.hpp"
#include "object_selector_panel.hpp"

template <class Tobject>
class ObjectMainPanel : public Gtk::Paned {
    private:
        AppContext&      m_app_context;
        Gtk::Paned       ui_bottom_hpaned{Gtk::Orientation::ORIENTATION_HORIZONTAL};
        Gtk::Box         ui_top_hbox{Gtk::Orientation::ORIENTATION_HORIZONTAL};
        Gtk::Box         ui_main_vbox{Gtk::Orientation::ORIENTATION_VERTICAL};
        Gtk::Button      ui_button_new;
        Gtk::Button      ui_button_save;


        void on_create_button_clicked()
        {
            auto o = m_manager->create_element();
            ui_editor->load_object(o);
        }

        void on_save_button_clicked() {
            save_object_in_editor();
        }

        void save_object_in_editor(bool refresh_list_after_save = true)
        {
            auto obj = ui_editor->get_object();
            SPDLOG_INFO("saving {}", obj.get_id_as_string());

            const auto saved_obj= m_manager->save_element(obj);

            if (refresh_list_after_save) {
                m_manager->refresh_list();
                ui_selector->refresh_object_list(m_manager->get_list());
            }
        }

        bool on_object_selected(Tobject obj)
        {
            bool should_refresh = false;

            const auto current_obj     = ui_editor->get_object();
            const auto unsaved_changes = ui_editor->get_unsaved_changes();

            if (!unsaved_changes.empty() && current_obj.get_id() != obj.get_id()) {

                std::stringstream ss;

                ss << fmt::format("{} unsaved changes!\n", unsaved_changes.size());
                for (const auto &diff : unsaved_changes) {
                    ss << fmt::format("\t{:<20}: {:<20} -> {}\n",
                            diff.attribute_name,
                            diff.value_lhs,
                            diff.value_rhs);
                }

                SPDLOG_WARN(ss.str());

                // TODO
                // - Error when saving via dialog: (wcrm_gtk3:19223): Gtk-CRITICAL **: 14:02:22.429: gtk_list_box_row_grab_focus: assertion 'box != NULL' failed
                // - Maybe log the object diff as info when saving
                Gtk::MessageDialog dialog(*m_app_context.main_window,
                    "Discard changes?",
                    false /* use_markup */,
                    Gtk::MessageType::MESSAGE_WARNING,
                    Gtk::BUTTONS_YES_NO);

                dialog.set_secondary_text(
                    "Click YES to discard unsaved changes\n"
                    "or click NO to save them");

                int result = dialog.run();
                //Handle the response:
                switch(result) {
                    case(Gtk::RESPONSE_YES):
                        save_object_in_editor(false);
                        should_refresh = true;
                        break;
                        break;
                }
            }

            ui_editor->load_object(std::move(obj));
            return should_refresh;
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
            : m_app_context{app_context}
            , ui_editor{_ui_editor}
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
                    sigc::mem_fun(*this, &ObjectMainPanel::on_create_button_clicked));

            ui_button_save.signal_clicked().connect(
                    sigc::mem_fun(*this, &ObjectMainPanel::on_save_button_clicked));

            ui_selector->set_callback_on_object_selected([&](Tobject obj) {
               return on_object_selected(obj);
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
