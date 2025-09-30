#ifndef OBJECT_REFERENCER_HPP
#define OBJECT_REFERENCER_HPP

#include <memory>
#include <optional>

#include "object_selector_panel.hpp"
#include "wcrm-lib/manager/manager_interface.hpp"

#include "gtkmm/dialog.h"

template<class Tobject>
class ObjectReferencerDialog {

private:
    std::unique_ptr<ObjectSelectorPanel<Tobject>> m_selector;
    std::shared_ptr<IManager<Tobject>>            m_manager;
    Gtk::Window&                                  m_window;
    std::optional<Tobject>                        m_choosen_object {std::nullopt};

public:

    ObjectReferencerDialog( std::unique_ptr<ObjectSelectorPanel<Tobject>> &&selector,
                            const std::shared_ptr<IManager<Tobject>>& manager,
                            Gtk::Window& window)
        : m_selector{std::move(selector)}
        , m_manager{manager}
        , m_window{window} {


        m_selector->refresh_object_list(manager->get_list());


        m_selector->set_callback_on_object_filter_changed([&](void) {
            manager->refresh_list();
            auto obj_list = manager->get_list();
            if (!obj_list.empty()) {
                m_selector->refresh_object_list(obj_list);
            }
        });

        }

        std::optional<Tobject> run();
};



template<class Tobject>
std::optional<Tobject> ObjectReferencerDialog<Tobject>::run()
{
    Gtk::Dialog dialog("Selector", m_window);

    //dialog.set_secondary_text(
    //        "Click YES to discard unsaved changes\n"
    //        "or click NO to save them");
    m_selector->set_callback_on_object_selected([&](Tobject o) -> bool{
            m_choosen_object = o;
            dialog.close();
            return false;
    });


    dialog.get_content_area()->pack_start(*m_selector, Gtk::PACK_EXPAND_WIDGET);
    dialog.show_all_children();
    dialog.set_default_size(600, 400);
    std::ignore = dialog.run();
    return m_choosen_object;
}

#endif // OBJECT_REFERENCER_HPP
