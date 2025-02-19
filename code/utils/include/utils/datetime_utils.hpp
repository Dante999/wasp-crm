#ifndef DATETIME_UTILS_HPP
#define DATETIME_UTILS_HPP

#include <string>

namespace utils {
[[nodiscard]] std::string get_current_datetime();
[[nodiscard]] std::string get_current_date();
} // namespace utils

#endif // DATETIME_UTILS_HPP
