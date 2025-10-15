#ifndef INVOICE_EDITOR_HPP
#define INVOICE_EDITOR_HPP

#include <gtkmm/box.h>
#include <gtkmm/flowbox.h>
#include <gtkmm/frame.h>
#include <gtkmm/grid.h>
#include <gtkmm/image.h>
#include <gtkmm/notebook.h>

#include "wcrm-lib/objects/invoice.hpp"

#include "object_editor_panel.hpp"
#include "util_gtk.hpp"

class InvoiceEditor : public ObjectEditorPanel<Invoice> {
    private:
        Gtk::Notebook ui_notebook;
        Gtk::Box ui_base_info_pane  {Gtk::ORIENTATION_VERTICAL};
        Gtk::Box ui_payee_text_pane {Gtk::ORIENTATION_VERTICAL};

        util_gtk::Placeholder             ui_placeholder;

        util_gtk::FrameFormGridRow<1>     ui_frame_system_info{"system_info"};
        util_gtk::TextInputReadonly       ui_invoice_id{"id"};
        util_gtk::TextInputReadonly       ui_created_at{"created_at"};
        util_gtk::TextInputReadonly       ui_last_modified{"last_modified"};
        Gtk::Image                        ui_image;

        util_gtk::FrameFormGrid2      ui_frame_base_info{"payee"};
        util_gtk::ObjectChooser       ui_customer{"customer", ""};
        util_gtk::TextMultilineInput  ui_payee_field{"receiver", "", };

        util_gtk::TextInput           ui_text_subject{"subject", "", };
        util_gtk::TextMultilineInput  ui_text_opening{"opening_text", "", };
        util_gtk::TextMultilineInput  ui_text_closing{"closing_text", "", };

        util_gtk::FrameFormGrid2      ui_frame_contact{"contact"};
        util_gtk::TextInput           ui_homepage{"homepage", "", };
        util_gtk::TextInput           ui_phone{"phone", "", };

    private:
        void write_to_gui(const Invoice &invoice) override;
        void read_from_gui(Invoice &article) override;

    public:
        InvoiceEditor(AppContext &context);
};

#endif // INVOICE_EDITOR_HPP
