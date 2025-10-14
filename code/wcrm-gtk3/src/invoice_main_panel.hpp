#ifndef INVOICE_MAIN_PANE_HPP
#define INVOICE_MAIN_PANE_HPP

#include "object_main_panel.hpp"

#include "invoice_editor.hpp"
#include "invoice_selector.hpp"

#include <memory>

class InvoiceMainPanel : public ObjectMainPanel<Invoice> {

    public:
        InvoiceMainPanel(AppContext &app_context)
            : ObjectMainPanel(app_context,
                              std::make_shared<InvoiceEditor>(app_context),
                              std::make_shared<InvoiceSelector>(app_context),
                              app_context.invoice_manager)
        {}
};



#endif // INVOICE_MAIN_PANE_HPP
