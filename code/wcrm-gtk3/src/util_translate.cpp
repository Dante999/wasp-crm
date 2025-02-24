#include "util_translate.hpp"

#include "utils/config_file.hpp"

namespace util_translate {
static ConfigFile translation_file;

void init(std::filesystem::path filepath) { translation_file.load(filepath); }

std::string translate(const std::string &key)
{
    if (translation_file.does_key_exist(key)) {
        return translation_file.get_string(key);
    }
    else {
        return key;
    }
}
} // namespace util_translate