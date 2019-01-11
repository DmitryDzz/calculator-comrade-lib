//
// Created by dmitrydzz on 21.10.18.
//

#include <gmock/gmock.h>

#include "calculator/config.h"
#include "calculator/register.h"

using calculatorcomrade::Register;

const uint8_t Register::NO_POINT;

TEST(TestRegister, DefaultState) {
    Register reg(Config::DEFAULT_DIGITS);
    ASSERT_EQ(0, reg.getAbsIntValue());
    ASSERT_EQ(Register::NO_POINT, reg.pointPos);
    ASSERT_EQ(false, reg.negative);
    ASSERT_EQ(false, reg.overflow);
}

TEST(TestRegister, SetPositiveValue) {
    Register reg(Config::DEFAULT_DIGITS);
    reg.setValue(1974);
    ASSERT_EQ(1974, reg.getAbsIntValue());
    ASSERT_EQ(4, reg[0]);
    ASSERT_EQ(7, reg[1]);
    ASSERT_EQ(9, reg[2]);
    ASSERT_EQ(1, reg[3]);
    ASSERT_EQ(Register::NO_POINT, reg.pointPos);
    ASSERT_EQ(false, reg.negative);
    ASSERT_EQ(false, reg.overflow);
}

TEST(TestRegister, SetNegativeValue) {
    Register reg(Config::DEFAULT_DIGITS);
    reg.setValue(-1974);
    ASSERT_EQ(1974, reg.getAbsIntValue());
    ASSERT_EQ(Register::NO_POINT, reg.pointPos);
    ASSERT_EQ(true, reg.negative);
    ASSERT_EQ(false, reg.overflow);
}

TEST(TestRegister, Assigning) {
    Register regA(8);
    regA.setValue(-1234567890);

    Register regB(8);
    regB.set(regA);
    ASSERT_EQ(12345678, regB.getAbsIntValue());
    ASSERT_EQ(6, regB.pointPos);
    ASSERT_EQ(true, regB.negative);
    ASSERT_EQ(true, regB.overflow);
}

TEST(TestRegister, SetPositiveOverflowValue) {
    Register reg(5);

    reg.setValue(123456789);
    ASSERT_EQ(12345, reg.getAbsIntValue());
    ASSERT_EQ(1, reg.pointPos);
    ASSERT_EQ(false, reg.negative);
    ASSERT_EQ(true, reg.overflow); // Err1234.5

    Register reg2(5);
    reg2.setValue(123456789, 0); // 123456789.
    ASSERT_EQ(reg, reg2);

    reg.clear();
    reg.setValue(123456789, 3); // 123456.789
    ASSERT_EQ(12345, reg.getAbsIntValue());
    ASSERT_EQ(4, reg.pointPos);
    ASSERT_EQ(false, reg.negative);
    ASSERT_EQ(true, reg.overflow); // Err1.2345
}

TEST(TestRegister, SetNegativeOverflowValue) {
    Register reg(5);
    reg.setValue(-123456789);
    ASSERT_EQ(12345, reg.getAbsIntValue());
    ASSERT_EQ(1, reg.pointPos);
    ASSERT_EQ(true, reg.negative);
    ASSERT_EQ(true, reg.overflow); // Err-1234.5

    Register reg2(5);
    reg2.setValue(-123456789, 0); // -123456789.
    ASSERT_EQ(reg, reg2);

    reg.clear();
    reg.setValue(-123456789, 3); // -123456.789
    ASSERT_EQ(12345, reg.getAbsIntValue());
    ASSERT_EQ(4, reg.pointPos);
    ASSERT_EQ(true, reg.negative);
    ASSERT_EQ(true, reg.overflow); // Err-1.2345
}

TEST(TestRegister, PointPos) {
    Register reg(5);
    reg.setValue(123456789, 4); // 12345.6789
    ASSERT_EQ(12345, reg.getAbsIntValue());
    ASSERT_EQ(Register::NO_POINT, reg.pointPos);
    ASSERT_EQ(false, reg.negative);
    ASSERT_EQ(false, reg.overflow);

    reg.clear();
    reg.setValue(123456789, 5); // 1234.56789
    ASSERT_EQ(12345, reg.getAbsIntValue());
    ASSERT_EQ(1, reg.pointPos);
    ASSERT_EQ(false, reg.negative);
    ASSERT_EQ(false, reg.overflow);

    reg.clear();
    reg.setValue(123, 1); // 12.3
    ASSERT_EQ(123, reg.getAbsIntValue());
    ASSERT_EQ(1, reg.pointPos);
    ASSERT_EQ(false, reg.negative);
    ASSERT_EQ(false, reg.overflow);

    reg.clear();
    reg.setValue(12, 0); // 12
    ASSERT_EQ(12, reg.getAbsIntValue());
    ASSERT_EQ(Register::NO_POINT, reg.pointPos);
    ASSERT_EQ(false, reg.negative);
    ASSERT_EQ(false, reg.overflow);

    reg.clear();
    reg.setValue(12); // 12
    ASSERT_EQ(12, reg.getAbsIntValue());
    ASSERT_EQ(Register::NO_POINT, reg.pointPos);
    ASSERT_EQ(false, reg.negative);
    ASSERT_EQ(false, reg.overflow);

    reg.clear();
    reg.setValue(123, 3); // 0.123
    ASSERT_EQ(123, reg.getAbsIntValue());
    ASSERT_EQ(3, reg.pointPos);
    ASSERT_EQ(false, reg.negative);
    ASSERT_EQ(false, reg.overflow);

    reg.clear();
    reg.setValue(123, 7); // 0.0000123
    ASSERT_EQ(0, reg.getAbsIntValue());
    ASSERT_EQ(Register::NO_POINT, reg.pointPos);
    ASSERT_EQ(false, reg.negative);
    ASSERT_EQ(false, reg.overflow);

    reg.clear();
    reg.setValue(1234567, 8); // 0.01234567
    ASSERT_EQ(123, reg.getAbsIntValue());
    ASSERT_EQ(4, reg.pointPos);
    ASSERT_EQ(false, reg.negative);
    ASSERT_EQ(false, reg.overflow);
}