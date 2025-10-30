#ifndef INVOICE_HPP
#define INVOICE_HPP

#include "base_object.hpp"

#include "utils/date.hpp"
#include "utils/decimal.hpp"
#include "utils/price.hpp"

#include <vector>

struct Invoice : public BaseObject {

        struct Item {
            std::string article_id;
            std::string name;
            std::string description;
            float quantity{0};
            Price       single_price;
        };

        Invoice(uint64_t id) : BaseObject{id} {}

        std::string get_id_prefix() const override { return "R-"; }

        std::string external_invoice_id;

        uint64_t    customer_id;
        std::string payee_field;
        std::string text_subject;
        std::string text_opening;
        std::string text_closing;

        Date invoice_date;
        Date due_date;
        Date paid_date;

        std::vector<Item> items;
};

#endif // INVOICE_HPP
