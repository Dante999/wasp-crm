#include "utils/datetime_utils.hpp"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace utils {
std::string get_current_datetime()
{
    auto t  = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d.%m.%Y %H:%M:%S");
    return oss.str();
}

std::string get_current_date()
{
    auto t  = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d.%m.%Y");
    return oss.str();
}

} // namespace utils
