#ifndef CUSTOMER_MAIN_PANE_HPP
#define CUSTOMER_MAIN_PANE_HPP

#include "object_main_panel.hpp"

#include "customer_editor.hpp"
#include "customer_selector.hpp"

#include <memory>

class CustomerMainPanel : public ObjectMainPanel<Customer> {

    public:
        CustomerMainPanel(AppContext &app_context)
            : ObjectMainPanel(app_context,
                              std::make_shared<CustomerEditor>(app_context),
                              std::make_shared<CustomerSelector>(app_context),
                              app_context.customer_manager)
        {}
};



#endif // CUSTOMER_MAIN_PANE_HPP
