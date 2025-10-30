#ifndef CURRENCY_HPP
#define CURRENCY_HPP

#include <cstdint>
#include <string>

class Currency {
    public:
        static constexpr int precision = 1'000;

    private:
        const std::string unit               = "€";
        const std::string thousand_separator = ".";
        const std::string fraction_separator = ",";

        uint64_t m_raw_value = 0;

    public:
        Currency() = default;
        Currency(const Currency &other) : m_raw_value{other.m_raw_value} {}

        static Currency create_from_cents(uint64_t cents)
        {
            Currency cur;
            cur.from_cents(cents);
            return cur;
        }


        void from_raw_value(uint64_t raw_value);
        void from_cents(uint64_t cents);
        void from_string(std::string s);

        [[nodiscard]] uint64_t    as_raw_value() const;
        [[nodiscard]] uint64_t    as_cents() const;
        [[nodiscard]] std::string as_string() const;

        Currency  operator*(double val) const;
        Currency  operator*(size_t val) const;
        Currency  operator*(int val) const;
        Currency  operator+(const Currency &rhs) const;
        Currency &operator+=(const Currency &rhs);
        Currency &operator=(const Currency &other) noexcept;
};

#endif // CURRENCY_HPP
