#include "utils/config_file.hpp"

#include <fstream>

#include "utils/string_utils.hpp"

void ConfigFile::load(const std::filesystem::path &filepath)
{
    m_values.clear();

    auto is = std::ifstream(filepath);

    std::string ns = "";
    std::string line;

    int line_number = 1;

    while (getline(is, line)) {

        line = utils::str_trim(line);

        if (line.empty() || line.at(0) == '#') {
            continue;
        }

        if (line.at(0) == '[') {

            const auto ns_end = line.find(']');

            if (ns_end == std::string::npos) {
                throw std::runtime_error("namespace started with '[' but no ']' found at line " +
                                         std::to_string(line_number));
            }

            ns = utils::str_trim(line.substr(1, ns_end)) + ".";
        }

        const auto delimiter = line.find('=');

        if (delimiter == std::string::npos) {
            throw std::runtime_error("no '=' delimiter found for line " + std::to_string(line_number));
        }

        const auto key   = ns + utils::str_trim(line.substr(0, delimiter));
        const auto value = utils::str_trim(line.substr(delimiter + 1));

        m_values.insert(std::make_pair(key, value));
    }
}

std::string &ConfigFile::get_string(const std::string &key)
{
    if (const auto &val = m_values.find(key); val != m_values.end()) {
        return val->second;
    }

    throw std::runtime_error("no value for key '" + key + "' found!");
}

float ConfigFile::get_float(const std::string &key) { return std::stof(get_string(key)); }

int ConfigFile::get_int(const std::string &key) { return std::stoi(get_string(key)); }

unsigned int ConfigFile::get_uint(const std::string &key)
{
    return static_cast<unsigned int>(std::stoul(get_string(key)));
}

bool ConfigFile::does_key_exist(const std::string &key) { return m_values.find(key) != std::end(m_values); }