#ifndef VENDOR_SELECTOR_HPP
#define VENDOR_SELECTOR_HPP

#include "object_selector_panel.hpp"
#include "wcrm-lib/objects/vendor.hpp"
#include "utils/string_utils.hpp"

#include <fmt/format.h>
class VendorSelector : public ObjectSelectorPanel<Vendor> {
public:
    std::string get_element_display_name(const Vendor& element) override {
        std::string new_name = element.name;

        return fmt::format("{}__{}",
                element.get_id_as_string(),
                utils::str_replace(new_name, " ", "_"));
    }

public:
    using ObjectSelectorPanel::ObjectSelectorPanel;
};

#endif // VENDOR_SELECTOR_HPP
