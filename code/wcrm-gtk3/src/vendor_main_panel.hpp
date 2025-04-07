#ifndef VENDOR_MAIN_PANE_HPP
#define VENDOR_MAIN_PANE_HPP

#include "object_main_panel.hpp"

#include "vendor_editor.hpp"
#include "vendor_selector.hpp"

#include <memory>

class VendorMainPanel : public ObjectMainPanel<Vendor> {

    public:
        VendorMainPanel(AppContext &app_context)
            : ObjectMainPanel(app_context, 
                              std::make_shared<VendorEditor>(app_context),
                              std::make_shared<VendorSelector>(app_context),
                              app_context.vendor_manager)
        {}
};



#endif // VENDOR_MAIN_PANE_HPP
