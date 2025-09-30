#ifndef ARTICLE_HPP
#define ARTICLE_HPP

#include "base_object.hpp"

#include "utils/currency.hpp"
#include "utils/decimal.hpp"

struct Article : public BaseObject {
        Article(uint64_t id) : BaseObject{id} {}

        std::string get_id_prefix() const override { return "A-"; }

        std::string name;
        std::string description;
        std::string unit;
        std::string material;
        std::string base64_image;
        Decimal<1> width_cm;
        Decimal<1> height_cm;
        Decimal<1> length_cm;
        Decimal<3> weight_kg;

        uint64_t vendor_id;
        std::string vendor_article_id;
        std::string vendor_article_name;
        std::string vendor_article_description;
        std::string vendor_article_weblink;
        Currency    vendor_article_price;

        Currency sell_price;
};



#endif // ARTICLE_HPP
