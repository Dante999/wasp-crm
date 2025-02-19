#ifndef FILESYSTEM_UTILS_HPP
#define FILESYSTEM_UTILS_HPP

#include <filesystem>
#include <string>
#include <vector>

namespace utils {

std::vector<std::string> get_directories(const std::filesystem::path &basepath);

}

#endif // FILESYSTEM_UTILS_HPP