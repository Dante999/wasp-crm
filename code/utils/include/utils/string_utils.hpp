
#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <string>
#include <vector>

namespace utils {

[[nodiscard]] const std::vector<std::string> str_split_text_into_lines(const std::string &text, size_t column_width);
[[nodiscard]] const std::vector<std::string> str_get_highlighted_text(const std::string &text, char marker_start,
                                                                      char marker_end);

[[nodiscard]] const std::string str_add_newline_on_column_width(const std::string &text, size_t column_width);
[[nodiscard]] const std::string str_remove_newlines(const std::string &text);

[[nodiscard]] bool str_equals_ignorecase(const std::string &s1, const std::string &s2);
[[nodiscard]] bool str_equals_one_of(const std::string &s, const std::vector<std::string> &s_list);

[[nodiscard]] std::string str_ltrim(const std::string &s);
[[nodiscard]] std::string str_rtrim(const std::string &s);
[[nodiscard]] std::string str_trim(const std::string &s);

std::string &str_replace(std::string &text, const std::string &old_word, const std::string &new_word);

[[nodiscard]] bool str_starts_with(const std::string &s, const std::string &start);
[[nodiscard]] bool str_ends_with(const std::string &s, const std::string &end);

[[nodiscard]] std::string float_to_string(float value, int precision);
} // namespace utils

#endif // STRING_UTILS_HPP
