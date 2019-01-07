//
// Created by dmitrydzz on 21.10.18.
//

#include <gmock/gmock.h>

#include "calculator/config.h"
#include "calculator/register.h"

using calculatorcomrade::Register;

TEST(TestRegister, DefaultState) {
    Register reg(Config::DEFAULT_DIGITS);
    ASSERT_EQ(0, reg.getValue());
    ASSERT_EQ(0xFF, reg.pointPos);
    ASSERT_EQ(false, reg.negative);
    ASSERT_EQ(false, reg.overflow);
}

TEST(TestRegister, SetPositiveValue) {
    Register reg(Config::DEFAULT_DIGITS);
    reg.setValue(1974);
    ASSERT_EQ(1974, reg.getValue());
    ASSERT_EQ(4, reg[0]);
    ASSERT_EQ(7, reg[1]);
    ASSERT_EQ(9, reg[2]);
    ASSERT_EQ(1, reg[3]);
    ASSERT_EQ(0xFF, reg.pointPos);
    ASSERT_EQ(false, reg.negative);
    ASSERT_EQ(false, reg.overflow);
}

TEST(TestRegister, SetNegativeValue) {
    Register reg(Config::DEFAULT_DIGITS);
    reg.setValue(-1974);
    ASSERT_EQ(1974, reg.getValue());
    ASSERT_EQ(0xFF, reg.pointPos);
    ASSERT_EQ(true, reg.negative);
    ASSERT_EQ(false, reg.overflow);
}

TEST(TestRegister, SetPositiveOverflowValue) {
    Register reg(8);
    reg.setValue(1234567890);
    ASSERT_EQ(34567890, reg.getValue());
    ASSERT_EQ(2, reg.pointPos);
    ASSERT_EQ(false, reg.negative);
    ASSERT_EQ(true, reg.overflow);
}

TEST(TestRegister, SetNegativeOverflowValue) {
    Register reg(8);
    reg.setValue(-1234567890);
    ASSERT_EQ(34567890, reg.getValue());
    ASSERT_EQ(2, reg.pointPos);
    ASSERT_EQ(true, reg.negative);
    ASSERT_EQ(true, reg.overflow);
}
