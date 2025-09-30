#include "wcrm-lib/objects/object_comparator.hpp"

#include <type_traits>
#define STRINGIFY(x) #x
#define COMPARE_OBJECT(RESULT_VEC, ATTR_NAME, LHS_OBJ, RHS_OBJ) add_if_different(RESULT_VEC, STRINGIFY(ATTR_NAME), lhs.ATTR_NAME, rhs.ATTR_NAME)

namespace {

    template<typename Tvalue>
    void add_if_different(std::vector<CompareDiff> &diff_vec,
                                 const std::string& attr_name,
                                 const Tvalue& lhs,
                                 const Tvalue& rhs)
    {
       if constexpr (std::is_same_v<Tvalue, std::string>) {
            if (lhs != rhs) diff_vec.push_back({attr_name, lhs, rhs});
       }
       else if constexpr (std::is_same_v<Tvalue, uint64_t>) {
            if (lhs != rhs) diff_vec.push_back({attr_name, std::to_string(lhs), std::to_string(rhs)});
       }
       else {
            if (lhs.as_string() != rhs.as_string()) diff_vec.push_back({attr_name, lhs.as_string(), rhs.as_string()});
       }
    }

}

std::vector<CompareDiff> get_object_diff(const Article& lhs, const Article& rhs)
{
    std::vector<CompareDiff> diff;

    COMPARE_OBJECT(diff, name       , lhs, rhs);
    COMPARE_OBJECT(diff, description, lhs, rhs);
    COMPARE_OBJECT(diff, unit       , lhs, rhs);
    COMPARE_OBJECT(diff, material   , lhs, rhs);
    COMPARE_OBJECT(diff, width_cm   , lhs, rhs);
    COMPARE_OBJECT(diff, height_cm  , lhs, rhs);
    COMPARE_OBJECT(diff, length_cm  , lhs, rhs);
    COMPARE_OBJECT(diff, weight_kg  , lhs, rhs);

    COMPARE_OBJECT(diff, vendor_id                  , lhs, rhs);
    COMPARE_OBJECT(diff, vendor_article_id          , lhs, rhs);
    COMPARE_OBJECT(diff, vendor_article_name        , lhs, rhs);
    COMPARE_OBJECT(diff, vendor_article_description , lhs, rhs);
    COMPARE_OBJECT(diff, vendor_article_weblink     , lhs, rhs);
    COMPARE_OBJECT(diff, vendor_article_price       , lhs, rhs);

    COMPARE_OBJECT(diff, sell_price, lhs, rhs);

    return diff;
}

std::vector<CompareDiff> get_object_diff(const Vendor& lhs, const Vendor& rhs)
{
    std::vector<CompareDiff> diff;

    COMPARE_OBJECT(diff, name       , lhs, rhs);
    COMPARE_OBJECT(diff, description, lhs, rhs);
    COMPARE_OBJECT(diff, street     , lhs, rhs);
    COMPARE_OBJECT(diff, zip_code   , lhs, rhs);
    COMPARE_OBJECT(diff, city       , lhs, rhs);
    COMPARE_OBJECT(diff, country    , lhs, rhs);
    COMPARE_OBJECT(diff, email      , lhs, rhs);
    COMPARE_OBJECT(diff, homepage   , lhs, rhs);
    COMPARE_OBJECT(diff, phone      , lhs, rhs);

    return diff;
}
