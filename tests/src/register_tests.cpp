//
// Created by dmitrydzz on 21.10.18.
//

#include <gmock/gmock.h>

#include "calculator/config.h"
#include "calculator/register.h"
#include "calc_helper.h"

using calculatorcomrade::Register;

TEST(TestRegister, DefaultState) {
    Register reg(Config::DEFAULT_SIZE);
    ASSERT_EQ(0, getAbsIntValue(reg));
    ASSERT_EQ(0, reg.getPointPos());
    ASSERT_EQ(false, reg.isNegative());
    ASSERT_EQ(false, reg.hasError());
}

TEST(TestRegister, SetPositiveValue) {
    Register reg(Config::DEFAULT_SIZE);
    setValue(reg, 1974);
    ASSERT_EQ(1974, getAbsIntValue(reg));
    ASSERT_EQ(4, reg.getDigit(0));
    ASSERT_EQ(7, reg.getDigit(1));
    ASSERT_EQ(9, reg.getDigit(2));
    ASSERT_EQ(1, reg.getDigit(3));
    ASSERT_EQ(0, reg.getPointPos());
    ASSERT_EQ(false, reg.isNegative());
    ASSERT_EQ(false, reg.hasError());
}

TEST(TestRegister, SetNegativeValue) {
    Register reg(Config::DEFAULT_SIZE);
    setValue(reg, -1974);
    ASSERT_EQ(1974, getAbsIntValue(reg));
    ASSERT_EQ(0, reg.getPointPos());
    ASSERT_EQ(true, reg.isNegative());
    ASSERT_EQ(false, reg.hasError());
}

TEST(TestRegister, SetSameSize) {
    Register regA(8);
    setValue(regA, -1234567890);

    Register regB(8);
    regB.set(regA);
    ASSERT_EQ(-12345678, getIntValue(regB));
    ASSERT_EQ(6, regB.getPointPos());
    ASSERT_EQ(true, regB.hasError());
}

TEST(TestRegister, SetSmallToBig) {
    Register regS(4);
    setValue(regS, -1234, 2);

    Register regB(8);
    regB.set(regS);
    ASSERT_EQ(-1234, getIntValue(regB));
    ASSERT_EQ(2, regB.getPointPos());
    ASSERT_EQ(false, regB.hasError());
}

TEST(TestRegister, SetSafeSameSize) {
    Register regA(8);
    setValue(regA, -12345678, 6);

    Register regB(8);
    regB.setSafe(regA);
    ASSERT_EQ(-12345678, getIntValue(regB));
    ASSERT_EQ(6, regB.getPointPos());
    ASSERT_EQ(false, regB.hasError());
}

TEST(TestRegister, SetSafeSmallToBig) {
    Register regS(4);
    setValue(regS, -1234, 2);

    Register regB(8);
    regB.setSafe(regS);
    ASSERT_EQ(-1234, getIntValue(regB));
    ASSERT_EQ(2, regB.getPointPos());
    ASSERT_EQ(false, regB.hasError());
}

TEST(TestRegister, SetSafeBigToSmall) {
    Register regB(8);
    Register regS(4);

    setValue(regB, -12345678);
    regS.setSafe(regB);
    ASSERT_EQ(-1234, getIntValue(regS));
    ASSERT_EQ(0, regS.getPointPos());
    ASSERT_EQ(true, regS.hasError());

    setValue(regB, -12345678, 2);
    regS.setSafe(regB);
    ASSERT_EQ(-1234, getIntValue(regS));
    ASSERT_EQ(2, regS.getPointPos());
    ASSERT_EQ(true, regS.hasError());

    setValue(regB, -12345678, 4);
    regS.setSafe(regB);
    ASSERT_EQ(-1234, getIntValue(regS));
    ASSERT_EQ(0, regS.getPointPos());
    ASSERT_EQ(false, regS.hasError());

    setValue(regB, -12345678, 6);
    regS.setSafe(regB);
    ASSERT_EQ(-1234, getIntValue(regS));
    ASSERT_EQ(2, regS.getPointPos());
    ASSERT_EQ(false, regS.hasError());

    setValue(regB, -1234567, 7);
    regS.setSafe(regB);
    ASSERT_EQ(-123, getIntValue(regS));
    ASSERT_EQ(3, regS.getPointPos());
    ASSERT_EQ(false, regS.hasError());

    setValue(regB, -123456, 7);
    regS.setSafe(regB);
    ASSERT_EQ(-12, getIntValue(regS));
    ASSERT_EQ(3, regS.getPointPos());
    ASSERT_EQ(false, regS.hasError());

    setValue(regB, -12, 1);
    regS.setSafe(regB);
    ASSERT_EQ(-12, getIntValue(regS));
    ASSERT_EQ(1, regS.getPointPos());
    ASSERT_EQ(false, regS.hasError());
}

TEST(TestRegister, SetPositiveOverflowValue) {
    Register reg(5);

    setValue(reg, 123456789);
    ASSERT_EQ(12345, getAbsIntValue(reg));
    ASSERT_EQ(1, reg.getPointPos());
    ASSERT_EQ(false, reg.isNegative());
    ASSERT_EQ(true, reg.hasError()); // Err1234.5

    Register reg2(5);
    setValue(reg2, 123456789, 0); // 123456789.
    ASSERT_EQ(reg, reg2);

    reg.clear();
    setValue(reg, 123456789, 3); // 123456.789
    ASSERT_EQ(12345, getAbsIntValue(reg));
    ASSERT_EQ(4, reg.getPointPos());
    ASSERT_EQ(false, reg.isNegative());
    ASSERT_EQ(true, reg.hasError()); // Err1.2345
}

TEST(TestRegister, SetNegativeOverflowValue) {
    Register reg(5);
    setValue(reg, -123456789);
    ASSERT_EQ(12345, getAbsIntValue(reg));
    ASSERT_EQ(1, reg.getPointPos());
    ASSERT_EQ(true, reg.isNegative());
    ASSERT_EQ(true, reg.hasError()); // Err-1234.5

    Register reg2(5);
    setValue(reg2, -123456789, 0); // -123456789.
    ASSERT_EQ(reg, reg2);

    reg.clear();
    setValue(reg, -123456789, 3); // -123456.789
    ASSERT_EQ(12345, getAbsIntValue(reg));
    ASSERT_EQ(4, reg.getPointPos());
    ASSERT_EQ(true, reg.isNegative());
    ASSERT_EQ(true, reg.hasError()); // Err-1.2345
}

TEST(TestRegister, PointPos) {
    Register reg(5);
    setValue(reg, 123456789, 4); // 12345.6789
    ASSERT_EQ(12345, getAbsIntValue(reg));
    ASSERT_EQ(0, reg.getPointPos());
    ASSERT_EQ(false, reg.isNegative());
    ASSERT_EQ(false, reg.hasError());

    reg.clear();
    setValue(reg, 123456789, 5); // 1234.56789
    ASSERT_EQ(12345, getAbsIntValue(reg));
    ASSERT_EQ(1, reg.getPointPos());
    ASSERT_EQ(false, reg.isNegative());
    ASSERT_EQ(false, reg.hasError());

    reg.clear();
    setValue(reg, 123, 1); // 12.3
    ASSERT_EQ(123, getAbsIntValue(reg));
    ASSERT_EQ(1, reg.getPointPos());
    ASSERT_EQ(false, reg.isNegative());
    ASSERT_EQ(false, reg.hasError());

    reg.clear();
    setValue(reg, 12, 0); // 12
    ASSERT_EQ(12, getAbsIntValue(reg));
    ASSERT_EQ(0, reg.getPointPos());
    ASSERT_EQ(false, reg.isNegative());
    ASSERT_EQ(false, reg.hasError());

    reg.clear();
    setValue(reg, 12); // 12
    ASSERT_EQ(12, getAbsIntValue(reg));
    ASSERT_EQ(0, reg.getPointPos());
    ASSERT_EQ(false, reg.isNegative());
    ASSERT_EQ(false, reg.hasError());

    reg.clear();
    setValue(reg, 123, 3); // 0.123
    ASSERT_EQ(123, getAbsIntValue(reg));
    ASSERT_EQ(3, reg.getPointPos());
    ASSERT_EQ(false, reg.isNegative());
    ASSERT_EQ(false, reg.hasError());

    reg.clear();
    setValue(reg, 123, 7); // 0.0000123
    ASSERT_EQ(0, getAbsIntValue(reg));
    ASSERT_EQ(0, reg.getPointPos());
    ASSERT_EQ(false, reg.isNegative());
    ASSERT_EQ(false, reg.hasError());

    reg.clear();
    setValue(reg, 1234567, 8); // 0.01234567
    ASSERT_EQ(123, getAbsIntValue(reg));
    ASSERT_EQ(4, reg.getPointPos());
    ASSERT_EQ(false, reg.isNegative());
    ASSERT_EQ(false, reg.hasError());
}