#ifndef VENDOR_EDITOR_HPP
#define VENDOR_EDITOR_HPP

#include <gtkmm/box.h>
#include <gtkmm/flowbox.h>
#include <gtkmm/frame.h>
#include <gtkmm/grid.h>
#include <gtkmm/image.h>

#include "wcrm-lib/objects/vendor.hpp"

#include "object_editor_panel.hpp"
#include "util_gtk.hpp"

class VendorEditor : public ObjectEditorPanel<Vendor> {
    private:
        util_gtk::Placeholder             ui_placeholder;

        util_gtk::FrameFormGridRow<1>     ui_frame_system_info{"system_info"};
        util_gtk::TextInputReadonly       ui_vendor_id{"id"};
        util_gtk::TextInputReadonly       ui_created_at{"created_at"};
        util_gtk::TextInputReadonly       ui_last_modified{"last_modified"};
        Gtk::Image                        ui_image;

        util_gtk::FrameFormGrid2      ui_frame_base_info{"vendor"};
        util_gtk::TextInput           ui_name{"name", "", };
        util_gtk::TextInput           ui_description{"description", "", };

        util_gtk::FrameFormGrid2      ui_frame_address{"address"};
        util_gtk::TextInput           ui_street{"street", "", };
        util_gtk::TextInput           ui_zip_code{"zip_code", "", };
        util_gtk::TextInput           ui_city{"city", "", };
        util_gtk::TextInput           ui_country{"country", "", };

        util_gtk::FrameFormGrid2      ui_frame_contact{"contact"};
        util_gtk::TextInput           ui_email{"email", "", };
        util_gtk::TextInput           ui_homepage{"homepage", "", };
        util_gtk::TextInput           ui_phone{"phone", "", };

    private:
        void write_to_gui(const Vendor &vendor) override;
        void read_from_gui(Vendor &article) override;

    public:
        VendorEditor(AppContext &context);
};

#endif // VENDOR_EDITOR_HPP
