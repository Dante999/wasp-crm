#ifndef TRANSLATION_HPP
#define TRANSLATION_HPP

#include <filesystem>
#include <string>

namespace util_translate {
void init(std::filesystem::path filepath);

std::string translate(const std::string &key);
} // namespace util_translate

#endif /* TRANSLATION_HPP */
