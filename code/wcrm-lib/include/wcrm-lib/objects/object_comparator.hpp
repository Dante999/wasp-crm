#ifndef OBJECT_COMPARATOR_HPP
#define OBJECT_COMPARATOR_HPP

#include "wcrm-lib/objects/article.hpp"

#include <string>
#include <vector>

struct CompareDiff {
    const std::string attribute_name;
    const std::string value_lhs;
    const std::string value_rhs;
};


std::vector<CompareDiff> get_object_diff(const Article& lhs, const Article& rhs);

#endif // OBJECT_COMPARATOR_HPP
