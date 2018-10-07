#include <gmock/gmock.h>

#include <calculator/main.h>

TEST(MainTest, CheckSomeResults)
{
    EXPECT_EQ(5, getValue());
}
