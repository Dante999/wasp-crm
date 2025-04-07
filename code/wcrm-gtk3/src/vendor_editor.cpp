#include "vendor_editor.hpp"

#include <spdlog/spdlog.h>


void VendorEditor::write_to_gui(const Vendor &vendor)
{
    SPDLOG_INFO("writing to gui '{} {}'", vendor.get_id_as_string(), vendor.name);

    value_to_gui(vendor.get_id_as_string() , ui_vendor_id);
    value_to_gui(vendor.created_at         , ui_created_at);
    value_to_gui(vendor.modfied_at         , ui_last_modified);

    value_to_gui(vendor.name        , ui_name);
    value_to_gui(vendor.description , ui_description);
    value_to_gui(vendor.street      , ui_street);
    value_to_gui(vendor.zip_code    , ui_zip_code);
    value_to_gui(vendor.city        , ui_city);
    value_to_gui(vendor.country     , ui_country);
    value_to_gui(vendor.email       , ui_email);
    value_to_gui(vendor.homepage    , ui_homepage);
    value_to_gui(vendor.phone       , ui_phone);
}

void VendorEditor::read_from_gui(Vendor &vendor)
{
    SPDLOG_INFO("reading from gui '{} {}'", vendor.get_id_as_string(), vendor.name);

    value_from_gui(vendor.name        , ui_name);
    value_from_gui(vendor.description , ui_description);
    value_from_gui(vendor.street      , ui_street);
    value_from_gui(vendor.zip_code    , ui_zip_code);
    value_from_gui(vendor.city        , ui_city);
    value_from_gui(vendor.country     , ui_country);
    value_from_gui(vendor.email       , ui_email);
    value_from_gui(vendor.homepage    , ui_homepage);
    value_from_gui(vendor.phone       , ui_phone);
}

VendorEditor::VendorEditor(AppContext &context) : ObjectEditorPanel(context)
{
    ui_flowbox.set_selection_mode(Gtk::SelectionMode::SELECTION_NONE);

    ui_image = Gtk::Image{m_app_context.basepath / "resources/image-placeholder.svg"};
    ui_flowbox.add(ui_frame_system_info);
    ui_frame_system_info.add_element(ui_vendor_id);
    ui_frame_system_info.add_element(ui_created_at);
    ui_frame_system_info.add_element(ui_last_modified);
    ui_frame_system_info.m_grid.attach(ui_image, 2, 0, 1, 3);


    int row = 0;
    ui_flowbox.add(ui_frame_base_info);
    ui_frame_base_info.add_full_width(row++, ui_name);
    ui_frame_base_info.add_full_width(row++, ui_description);

    row = 0;
    ui_flowbox.add(ui_frame_address);
    ui_frame_address.add_full_width(row++, ui_street);
    ui_frame_address.add_full_width(row++, ui_zip_code);
    ui_frame_address.add_full_width(row++, ui_city);
    ui_frame_address.add_full_width(row++, ui_country);

    row = 0;
    ui_flowbox.add(ui_frame_contact);
    ui_frame_contact.add_full_width(row++, ui_email);
    ui_frame_contact.add_full_width(row++, ui_homepage);
    ui_frame_contact.add_full_width(row++, ui_phone);

    write_to_gui(m_object);
}
