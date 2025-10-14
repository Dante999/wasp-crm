#ifndef INVOICE_SELECTOR_HPP
#define INVOICE_SELECTOR_HPP

#include "object_selector_panel.hpp"
#include "wcrm-lib/objects/invoice.hpp"
#include "utils/string_utils.hpp"

#include <fmt/format.h>
class InvoiceSelector : public ObjectSelectorPanel<Invoice> {
public:
    std::string get_element_display_name(const Invoice& element) override {
        std::string new_name = element.payee_field;
        utils::str_replace(new_name, "\n", " ");

        return fmt::format("{}__{}",
                element.get_id_as_string(),
                utils::str_replace(new_name, " ", "_"));
    }

public:
    using ObjectSelectorPanel::ObjectSelectorPanel;
};

#endif // INVOICE_SELECTOR_HPP
