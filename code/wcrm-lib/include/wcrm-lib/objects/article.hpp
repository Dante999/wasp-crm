#ifndef ARTICLE_HPP
#define ARTICLE_HPP

#include "base_object.hpp"

// #include "utils/currency.hpp"

struct Article : public BaseObject {
        Article(uint64_t id) : BaseObject{id} {}

        std::string get_id_prefix() const override { return "A-"; }

        std::string vendor_name;
        std::string vendor_article_id;
        std::string vendor_article_name;
        std::string vendor_article_link;
};

#endif // ARTICLE_HPP
