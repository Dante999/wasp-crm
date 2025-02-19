#include "utils/currency.hpp"

#include <cmath>
#include <error.h>
#include <stdexcept>
#include <cstring>

#include "utils/string_utils.hpp"

void Currency::from_raw_value(uint64_t raw_value) { m_raw_value = raw_value; }

void Currency::from_cents(uint64_t cents) { m_raw_value = cents * precision; }

void Currency::from_string(std::string s)
{

    s = utils::str_replace(s, "€", "");
    s = utils::str_replace(s, ".", "");

    const auto separator = s.find(',');

    if (separator == std::string::npos) {
        from_cents(std::stoull(s) * 100);
        return;
    }

    auto cents = std::stoull(s.substr(separator + 1, 2));
    cents += std::stoull(s.substr(0, separator)) * 100;

    from_cents(cents);
}

uint64_t Currency::as_cents() const
{
    return static_cast<uint64_t>(std::round(static_cast<double>(m_raw_value) / precision));
}

uint64_t Currency::as_raw_value() const { return m_raw_value; }

std::string Currency::as_string() const
{
    const auto euro_part  = as_cents() / 100;
    const auto cents_part = as_cents() % 100;

    // TODO: bit hacky, use a better and safer c++ approach
    char buffer[255];

    snprintf(buffer, sizeof(buffer), "%lu""%s""%02lu€", euro_part, fraction_separator.c_str(), cents_part);
    return std::string(buffer);
}

Currency Currency::operator*(double val) const
{
    Currency other;
    other.from_raw_value(static_cast<uint64_t>(val * static_cast<double>(m_raw_value)));
    return other;
}

Currency Currency::operator*(size_t val) const
{
    Currency other;
    other.from_raw_value(val * static_cast<size_t>(m_raw_value));
    return other;
}

Currency Currency::operator*(int val) const
{
    if (val < 0) {
        throw std::invalid_argument("multiply with negative value!");
    }

    Currency other;
    other.from_raw_value(static_cast<uint64_t>(val) * m_raw_value);
    return other;
}

Currency Currency::operator+(const Currency &rhs) const
{
    Currency other;
    other.from_raw_value(m_raw_value + rhs.m_raw_value);
    return other;
}

Currency &Currency::operator+=(const Currency &rhs)
{
    m_raw_value += rhs.m_raw_value;
    return *this;
}

Currency &Currency::operator=(const Currency &other) noexcept
{
    // Guard self assignment
    if (this == &other) {
        return *this;
    }

    m_raw_value = other.m_raw_value;

    return *this;
}
