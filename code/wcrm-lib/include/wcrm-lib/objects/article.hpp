#ifndef ARTICLE_HPP
#define ARTICLE_HPP

#include "base_object.hpp"

#include "utils/currency.hpp"

struct Article : public BaseObject {
        Article(uint64_t id) : BaseObject{id} {}

        std::string get_id_prefix() const override { return "A-"; }

        std::string name;
        std::string description;
        std::string unit;
        std::string material;
        float width_cm;
        float height_cm;
        float length_cm;
        float weight_kg;
        
        std::string vendor_name;
        std::string vendor_article_id;
        std::string vendor_article_name;
        std::string vendor_article_description;
        std::string vendor_article_weblink;
        Currency    vendor_price;
};

#endif // ARTICLE_HPP
