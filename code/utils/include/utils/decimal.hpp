#ifndef DECIMAL_HPP
#define DECIMAL_HPP

#include <string>
#include <cstring>
#include <cmath>

template <int PRECISSION>
class Decimal
{
private:
    float m_raw = 0;

public:
    Decimal() = default;
    Decimal(float f) { from_float(f);}


    [[nodiscard]] std::string as_string() {
        char buffer[255];
        snprintf(buffer, sizeof(buffer), "%0.*f", PRECISSION, static_cast<double>(m_raw));
        return std::string(buffer);
   
    }

    [[nodiscard]] float as_float() { return m_raw;}

    void from_float(float f)
    {
        const float factor = std::pow(10.0f, PRECISSION);
        m_raw = std::round(f * factor) / factor;
    }

    void from_string(const std::string &s)
    {
        if (s.empty()) {
            m_raw = 0;
        }
        else {
            from_float(std::stof(s));
        }
        
    }
};

#endif // DECIMAL_HPP

