#ifndef INVOICE_HPP
#define INVOICE_HPP

#include "base_object.hpp"

#include "utils/currency.hpp"
#include "utils/decimal.hpp"
#include "utils/date.hpp"

struct Invoice : public BaseObject {
        Invoice(uint64_t id) : BaseObject{id} {}

        std::string get_id_prefix() const override { return "R-"; }

        uint64_t customer_id;
        std::string payee_field;

        Date invoice_date;
        Date due_date;
        Date paid_date;
};



#endif // INVOICE_HPP
