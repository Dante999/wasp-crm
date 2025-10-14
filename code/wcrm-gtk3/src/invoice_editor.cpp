#include "invoice_editor.hpp"

#include <spdlog/spdlog.h>
#include "object_referencer_dialog.hpp"
#include "customer_selector.hpp"

void InvoiceEditor::write_to_gui(const Invoice &invoice)
{
    SPDLOG_INFO("writing to gui '{}'", invoice.get_id_as_string());

    value_to_gui(invoice.get_id_as_string() , ui_invoice_id);
    value_to_gui(invoice.created_at         , ui_created_at);
    value_to_gui(invoice.modfied_at         , ui_last_modified);

    //value_to_gui(invoice.payee_firstname                , ui_firstname);
    //value_to_gui(invoice.payee_lastname                 , ui_lastname);
    //value_to_gui(gender_to_string(invoice.payee_gender) , ui_gender);
    //value_to_gui(invoice.payee_street                   , ui_street);
    //value_to_gui(invoice.payee_zip_code                 , ui_zip_code);
    //value_to_gui(invoice.payee_city                     , ui_city);
    //value_to_gui(invoice.payee_country                  , ui_country);
}

void InvoiceEditor::read_from_gui(Invoice &invoice)
{
    SPDLOG_INFO("reading from gui '{}'", invoice.get_id_as_string());

    //value_from_gui(invoice.payee_firstname   , ui_firstname);
    //value_from_gui(invoice.payee_lastname    , ui_lastname);
    //invoice.payee_gender = gender_from_string(ui_gender.input.get_text());
    //value_from_gui(invoice.payee_street      , ui_street);
    //value_from_gui(invoice.payee_zip_code    , ui_zip_code);
    //value_from_gui(invoice.payee_city        , ui_city);
    //value_from_gui(invoice.payee_country     , ui_country);
}

InvoiceEditor::InvoiceEditor(AppContext &context) : ObjectEditorPanel(context)
{
    ui_image = Gtk::Image{m_app_context.basepath / "resources/image-placeholder.svg"};
    ui_mainpanel.add(ui_frame_system_info);
    ui_frame_system_info.add_element(ui_invoice_id);
    ui_frame_system_info.add_element(ui_created_at);
    ui_frame_system_info.add_element(ui_last_modified);
    ui_frame_system_info.m_grid.attach(ui_image, 2, 0, 1, 3);


    int row = 0;
    ui_mainpanel.add(ui_frame_base_info);
    ui_frame_base_info.add_full_width(row++, ui_customer);
    ui_frame_base_info.add_full_width(row++, ui_placeholder);
    ui_frame_base_info.add_full_width(row++, ui_payee_field);
    //ui_frame_base_info.add_left(row, ui_firstname);
    //ui_frame_base_info.add_right(row++, ui_street);

    //ui_frame_base_info.add_left(row, ui_lastname);
    //ui_frame_base_info.add_right(row++, ui_zip_code);
    //
    //ui_frame_base_info.add_left(row, ui_gender);
    //ui_frame_base_info.add_right(row++, ui_city);
    //ui_frame_base_info.add_right(row++, ui_country);

    //row = 0;
    //ui_mainpanel.add(ui_frame_address);

    row = 0;
    ui_mainpanel.add(ui_frame_contact);
    ui_frame_contact.add_full_width(row++, ui_email);
    ui_frame_contact.add_full_width(row++, ui_homepage);
    ui_frame_contact.add_full_width(row++, ui_phone);

    write_to_gui(m_object);

    ui_customer.cb_on_choose_object = [&]() {
        ObjectReferencerDialog<Customer> dialog(std::make_unique<CustomerSelector>(m_app_context),
                m_app_context.customer_manager,
                *m_app_context.main_window);

        const auto customer = dialog.run();

        if (customer.has_value()) {
            ui_customer.input.set_text(customer->get_id_as_string());
            std::string payee;

            payee += fmt::format("{} {}\n", customer->firstname, customer->lastname);
            payee += fmt::format("{}\n",    customer->street);
            payee += fmt::format("{} {}\n", customer->zip_code, customer->city);
            payee += fmt::format("{}",    customer->country);

            ui_payee_field.input.set_text(payee);
            //ui_firstname.input.set_text( customer->firstname);
            //ui_lastname.input.set_text( customer->lastname);
            //ui_zip_code.input.set_text(customer->zip_code);
            //ui_street.input.set_text(customer->street);
            //ui_city.input.set_text(customer->city);
            //ui_country.input.set_text(customer->country);
        }

    };
}
