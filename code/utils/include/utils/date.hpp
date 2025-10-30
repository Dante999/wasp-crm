#ifndef DATE_HPP
#define DATE_HPP

#include <cstring>
#include <string>

struct Date {
    int day   = 0;
    int month = 0;
    int year  = 0;

    std::string to_string() const
    {
        char tmp[20];

        snprintf(tmp, sizeof(tmp), "%02d.%02d.%04d", day, month, year);
        return tmp;
    }

    void from_string(const std::string &s) { sscanf(s.c_str(), "%02d.%02d.%04d", &day, &month, &year); }
};

#endif // DATE_HPP
