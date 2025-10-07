#ifndef CUSTOMER_SELECTOR_HPP
#define CUSTOMER_SELECTOR_HPP

#include "object_selector_panel.hpp"
#include "wcrm-lib/objects/customer.hpp"
#include "utils/string_utils.hpp"

#include <fmt/format.h>
class CustomerSelector : public ObjectSelectorPanel<Customer> {
public:
    std::string get_element_display_name(const Customer& element) override {
        std::string new_name = element.firstname + " " + element.lastname;

        return fmt::format("{}__{}",
                element.get_id_as_string(),
                utils::str_replace(new_name, " ", "_"));
    }

public:
    using ObjectSelectorPanel::ObjectSelectorPanel;
};

#endif // CUSTOMER_SELECTOR_HPP
