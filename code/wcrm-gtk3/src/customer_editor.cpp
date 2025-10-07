#include "customer_editor.hpp"

#include <spdlog/spdlog.h>


void CustomerEditor::write_to_gui(const Customer &customer)
{
    SPDLOG_INFO("writing to gui '{} {} {}'", customer.get_id_as_string(), customer.firstname, customer.lastname);

    value_to_gui(customer.get_id_as_string() , ui_customer_id);
    value_to_gui(customer.created_at         , ui_created_at);
    value_to_gui(customer.modfied_at         , ui_last_modified);

    value_to_gui(customer.firstname                , ui_firstname);
    value_to_gui(customer.lastname                 , ui_lastname);
    value_to_gui(gender_to_string(customer.gender) , ui_gender);
    value_to_gui(customer.description              , ui_description);
    value_to_gui(customer.street                   , ui_street);
    value_to_gui(customer.zip_code                 , ui_zip_code);
    value_to_gui(customer.city                     , ui_city);
    value_to_gui(customer.country                  , ui_country);
    value_to_gui(customer.email                    , ui_email);
    value_to_gui(customer.homepage                 , ui_homepage);
    value_to_gui(customer.phone                    , ui_phone);
}

void CustomerEditor::read_from_gui(Customer &customer)
{
    SPDLOG_INFO("reading from gui '{} {} {}'", customer.get_id_as_string(), customer.firstname, customer.lastname);

    value_from_gui(customer.firstname   , ui_firstname);
    value_from_gui(customer.lastname    , ui_lastname);
    customer.gender = gender_from_string(ui_gender.input.get_text());
    value_from_gui(customer.description , ui_description);
    value_from_gui(customer.street      , ui_street);
    value_from_gui(customer.zip_code    , ui_zip_code);
    value_from_gui(customer.city        , ui_city);
    value_from_gui(customer.country     , ui_country);
    value_from_gui(customer.email       , ui_email);
    value_from_gui(customer.homepage    , ui_homepage);
    value_from_gui(customer.phone       , ui_phone);
}

CustomerEditor::CustomerEditor(AppContext &context) : ObjectEditorPanel(context)
{
    ui_flowbox.set_selection_mode(Gtk::SelectionMode::SELECTION_NONE);

    ui_image = Gtk::Image{m_app_context.basepath / "resources/image-placeholder.svg"};
    ui_flowbox.add(ui_frame_system_info);
    ui_frame_system_info.add_element(ui_customer_id);
    ui_frame_system_info.add_element(ui_created_at);
    ui_frame_system_info.add_element(ui_last_modified);
    ui_frame_system_info.m_grid.attach(ui_image, 2, 0, 1, 3);


    int row = 0;
    ui_flowbox.add(ui_frame_base_info);
    ui_frame_base_info.add_full_width(row++, ui_firstname);
    ui_frame_base_info.add_full_width(row++, ui_lastname);
    ui_frame_base_info.add_full_width(row++, ui_gender);
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
