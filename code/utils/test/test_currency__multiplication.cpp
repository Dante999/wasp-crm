#include <gtest/gtest.h>

#include "utils/currency.hpp"

TEST(CurrencyTests_conversion, multiplication)
{
    Currency cur;

    cur.from_cents(100);

    const auto result = cur * 5.0;

    EXPECT_EQ(100, cur.as_cents());
    EXPECT_EQ(500, result.as_cents());
}

TEST(CurrencyTests_conversion, multiplication_const)
{
    Currency cur;

    cur.from_cents(100);

    const auto &c_cur = cur;

    const auto result = c_cur * 5;

    EXPECT_EQ(100, cur.as_cents());
    EXPECT_EQ(500, result.as_cents());
}
