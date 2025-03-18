#include <gtest/gtest.h>

#include "utils/currency.hpp"

class CurrencyTests_conversion : public ::testing::TestWithParam<std::tuple<uint64_t, uint64_t, std::string>> {
    protected:
        const uint64_t    expected_raw_value = std::get<0>(GetParam());
        const uint64_t    expected_cents     = std::get<1>(GetParam());
        const std::string expected_string    = std::get<2>(GetParam());
};

TEST_P(CurrencyTests_conversion, from_cents)
{
    Currency cur;
    cur.from_cents(expected_cents);

    ASSERT_EQ(expected_cents, cur.as_cents());
    ASSERT_EQ(expected_cents * Currency::precision, cur.as_raw_value());
    ASSERT_EQ(expected_string, cur.as_string());
}

TEST_P(CurrencyTests_conversion, from_string)
{
    Currency cur;
    cur.from_string(expected_string);

    ASSERT_EQ(expected_cents, cur.as_cents());
    ASSERT_EQ(expected_cents * Currency::precision, cur.as_raw_value());
    ASSERT_EQ(expected_string, cur.as_string());
}

TEST_P(CurrencyTests_conversion, from_raw_value)
{
    Currency cur;
    cur.from_raw_value(expected_raw_value);

    ASSERT_EQ(expected_cents, cur.as_cents());
    ASSERT_EQ(expected_raw_value, cur.as_raw_value());
    ASSERT_EQ(expected_string, cur.as_string());
}

INSTANTIATE_TEST_SUITE_P(currency_initialization, CurrencyTests_conversion,
                         ::testing::Values(std::make_tuple(10'000, 10, "0,10€"), std::make_tuple(11'000, 11, "0,11€"),
                                           std::make_tuple(99'000, 99, "0,99€"), std::make_tuple(99'499, 99, "0,99€"),
                                           std::make_tuple(99'500, 100, "1,00€"),
                                           std::make_tuple(1'000'00'000, 1'000'00, "1000,00€"),
                                           std::make_tuple(1'000'00'499, 1'000'00, "1000,00€"),
                                           std::make_tuple(1'000'00'500, 1'000'01, "1000,01€"),
                                           std::make_tuple(1'000'000'00'000, 1'000'000'00, "1000000,00€"),
                                           std::make_tuple(1'000'000'00'499, 1'000'000'00, "1000000,00€"),
                                           std::make_tuple(1'000'000'00'500, 1'000'000'01, "1000000,01€")

                                               ));
