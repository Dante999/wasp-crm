#include "wcrm-lib/objects/object_comparator.hpp"

namespace {

    inline void add_if_different(std::vector<CompareDiff> &diff_vec,
                                 const std::string& attr_name,
                                 const std::string& lhs,
                                 const std::string& rhs)
    {
        if (lhs != rhs) diff_vec.push_back({attr_name, lhs, rhs});
    }

}

std::vector<CompareDiff> get_object_diff(const Article& lhs, const Article& rhs)
{
    std::vector<CompareDiff> diff;

    add_if_different(diff, "name",        lhs.name,        rhs.name);
    add_if_different(diff, "description", lhs.description, rhs.description);
    add_if_different(diff, "unit",        lhs.unit,        rhs.unit);
    add_if_different(diff, "material",    lhs.material,    rhs.material);

    // TODO
#if 0
    Decimal<1> width_cm;
    Decimal<1> height_cm;
    Decimal<1> length_cm;
    Decimal<3> weight_kg;

    std::string vendor_name;
    std::string vendor_article_id;
    std::string vendor_article_name;
    std::string vendor_article_description;
    std::string vendor_article_weblink;
    Currency    vendor_article_price;

    Currency sell_price;
#endif
    return diff;
}
