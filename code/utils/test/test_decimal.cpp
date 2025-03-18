#include <gtest/gtest.h>

#include "utils/decimal.hpp"


TEST(DecimalTest, test_from_string)
{
    Decimal<3> d;

    d.from_float(1.1234f);
    EXPECT_EQ(1.123f, d.as_float());

    d.from_float(1.1235f);
    EXPECT_EQ(1.124f, d.as_float());

    d.from_string("1.1234");
    EXPECT_EQ("1.123", d.as_string());

    d.from_string("1.1235");
    EXPECT_EQ("1.124", d.as_string());
}
