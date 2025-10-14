#ifndef OBJECT_COMPARATOR_HPP
#define OBJECT_COMPARATOR_HPP

#include "wcrm-lib/objects/article.hpp"
#include "wcrm-lib/objects/vendor.hpp"
#include "wcrm-lib/objects/customer.hpp"
#include "wcrm-lib/objects/invoice.hpp"


#include <string>
#include <vector>

struct CompareDiff {
    const std::string attribute_name;
    const std::string value_lhs;
    const std::string value_rhs;
};


std::vector<CompareDiff> get_object_diff(const Article& lhs, const Article& rhs);
std::vector<CompareDiff> get_object_diff(const Vendor& lhs, const Vendor& rhs);
std::vector<CompareDiff> get_object_diff(const Customer& lhs, const Customer& rhs);
std::vector<CompareDiff> get_object_diff(const Invoice& lhs, const Invoice& rhs);

#endif // OBJECT_COMPARATOR_HPP
