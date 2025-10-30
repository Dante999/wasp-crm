#include "invoice_editor.hpp"

#include "customer_selector.hpp"
#include "object_referencer_dialog.hpp"
#include <spdlog/spdlog.h>

namespace {
std::string customer_to_displayname(const Customer &customer)
{
    return customer.firstname + " " + customer.lastname + " (" + customer.get_id_as_string() + ")";
}

uint64_t customer_id_from_displayname(const std::string &displayname)
{
    if (displayname.empty())
        return 0;

    size_t pos_start = displayname.find('(');
    size_t pos_end   = displayname.find(')');

    assert(pos_start != std::string::npos);
    assert(pos_end != std::string::npos);
    assert(pos_start < pos_end);
    pos_start++;
    auto substr = displayname.substr(pos_start, pos_end - pos_start);

    pos_start = substr.find('-');
    assert(pos_start != std::string::npos);
    assert(pos_start < substr.length());
    pos_start++;
    substr = substr.substr(pos_start, substr.length() - pos_start);

    return std::stoul(substr);
}
} // namespace

void InvoiceEditor::write_to_gui(const Invoice &invoice)
{
    SPDLOG_INFO("writing to gui '{}'", invoice.get_id_as_string());

    value_to_gui(invoice.get_id_as_string(), ui_invoice_id);
    value_to_gui(invoice.created_at, ui_created_at);
    value_to_gui(invoice.modfied_at, ui_last_modified);

    auto        customer             = m_app_context.customer_manager->get_element_by_id(invoice.customer_id);
    std::string customer_displayname = customer.has_value() ? customer_to_displayname(*customer) : "";

    value_to_gui(customer_displayname, ui_customer);
    value_to_gui(invoice.payee_field, ui_payee_field);
    value_to_gui(invoice.text_subject, ui_text_subject);
    value_to_gui(invoice.text_opening, ui_text_opening);
    value_to_gui(invoice.text_closing, ui_text_closing);

    ui_article_table.set_items(invoice.items);
    ui_article_table.refresh();
    // value_to_gui(invoice.payee_firstname                , ui_firstname);
    // value_to_gui(invoice.payee_lastname                 , ui_lastname);
    // value_to_gui(gender_to_string(invoice.payee_gender) , ui_gender);
    // value_to_gui(invoice.payee_street                   , ui_street);
    // value_to_gui(invoice.payee_zip_code                 , ui_zip_code);
    // value_to_gui(invoice.payee_city                     , ui_city);
    // value_to_gui(invoice.payee_country                  , ui_country);
}

void InvoiceEditor::read_from_gui(Invoice &invoice)
{
    SPDLOG_INFO("reading from gui '{}'", invoice.get_id_as_string());

    invoice.customer_id = customer_id_from_displayname(ui_customer.input.get_text());

    value_from_gui(invoice.payee_field, ui_payee_field);
    value_from_gui(invoice.text_subject, ui_text_subject);
    value_from_gui(invoice.text_opening, ui_text_opening);
    value_from_gui(invoice.text_closing, ui_text_closing);

    // value_from_gui(invoice.payee_firstname   , ui_firstname);
    // value_from_gui(invoice.payee_lastname    , ui_lastname);
    // invoice.payee_gender = gender_from_string(ui_gender.input.get_text());
    // value_from_gui(invoice.payee_street      , ui_street);
    // value_from_gui(invoice.payee_zip_code    , ui_zip_code);
    // value_from_gui(invoice.payee_city        , ui_city);
    // value_from_gui(invoice.payee_country     , ui_country);
}

InvoiceEditor::InvoiceEditor(AppContext &context) : ObjectEditorPanel(context)
{
    ui_mainpanel.add(ui_notebook);

    ui_base_info_pane.add(ui_frame_system_info);
    ui_image = Gtk::Image{m_app_context.basepath / "resources/image-placeholder.svg"};
    ui_frame_system_info.add_element(ui_invoice_id);
    ui_frame_system_info.add_element(ui_created_at);
    ui_frame_system_info.add_element(ui_last_modified);
    ui_frame_system_info.m_grid.attach(ui_image, 2, 0, 1, 3);

    int row = 0;
    ui_payee_text_pane.add(ui_frame_base_info);
    ui_frame_base_info.add_full_width(row++, ui_customer);
    ui_frame_base_info.add_full_width(row++, ui_placeholder);
    ui_frame_base_info.add_full_width(row++, ui_payee_field);
    ui_frame_base_info.add_full_width(row++, ui_text_subject);
    ui_frame_base_info.add_full_width(row++, ui_text_opening);
    ui_frame_base_info.add_full_width(row++, ui_text_closing);

    ui_article_pane.add(ui_article_table);
    // ui_frame_base_info.add_right(row++, ui_street);

    // ui_frame_base_info.add_left(row, ui_lastname);
    // ui_frame_base_info.add_right(row++, ui_zip_code);
    //
    // ui_frame_base_info.add_left(row, ui_gender);
    // ui_frame_base_info.add_right(row++, ui_city);
    // ui_frame_base_info.add_right(row++, ui_country);

    // row = 0;
    // ui_mainpanel.add(ui_frame_address);
    ui_notebook.append_page(ui_base_info_pane, util_translate::translate("base_data"));
    ui_notebook.append_page(ui_payee_text_pane, util_translate::translate("payee"));
    ui_notebook.append_page(ui_article_pane, util_translate::translate("article"));

    write_to_gui(m_object);

    ui_customer.cb_on_choose_object = [&]() {
        ObjectReferencerDialog<Customer> dialog(std::make_unique<CustomerSelector>(m_app_context),
                                                m_app_context.customer_manager, *m_app_context.main_window);

        const auto customer = dialog.run();

        if (customer.has_value()) {
            ui_customer.input.set_text(customer_to_displayname(*customer));
            std::string payee;

            payee += fmt::format("{} {}\n", customer->firstname, customer->lastname);
            payee += fmt::format("{}\n", customer->street);
            payee += fmt::format("{} {}\n", customer->zip_code, customer->city);
            payee += fmt::format("{}", customer->country);

            ui_payee_field.input.set_text(payee);
        }
    };
}
