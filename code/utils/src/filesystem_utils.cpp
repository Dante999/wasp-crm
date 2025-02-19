#include "utils/filesystem_utils.hpp"

namespace utils {

std::vector<std::string> get_directories(const std::filesystem::path &basepath)
{
    std::vector<std::string> r;
    for (auto &p : std::filesystem::recursive_directory_iterator(basepath))
        if (p.is_directory())
            r.push_back(p.path().filename());
    return r;
}

} // namespace utils