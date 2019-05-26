/**
 * Calculator Comrade Library
 * License: https://github.com/DmitryDzz/calculator-comrade-lib/blob/master/LICENSE
 * Author: Dmitry Dzakhov
 * Email: info@robot-mitya.ru
 */
#include <gmock/gmock.h>

#include "calculator/calculator.h"
#include "calculator/config.h"
#include "calculator/register.h"
#include "calc_helper.h"

using calculatorcomrade::Calculator;
using calculatorcomrade::Config;
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

TEST(TestRegister, GetDisplayDigit) {
    Register reg(8);

    ASSERT_EQ(0, reg.getDisplayDigit(0));
    ASSERT_EQ(-1, reg.getDisplayDigit(1));
    ASSERT_EQ(-1, reg.getDisplayDigit(2));
    ASSERT_EQ(-1, reg.getDisplayDigit(3));
    ASSERT_EQ(-1, reg.getDisplayDigit(4));
    ASSERT_EQ(-1, reg.getDisplayDigit(5));
    ASSERT_EQ(-1, reg.getDisplayDigit(6));
    ASSERT_EQ(-1, reg.getDisplayDigit(7));

    setValue(reg, 1, 4); // 0000.0001
    ASSERT_EQ(1, reg.getDisplayDigit(0));
    ASSERT_EQ(0, reg.getDisplayDigit(1));
    ASSERT_EQ(0, reg.getDisplayDigit(2));
    ASSERT_EQ(0, reg.getDisplayDigit(3));
    ASSERT_EQ(0, reg.getDisplayDigit(4));
    ASSERT_EQ(-1, reg.getDisplayDigit(5));
    ASSERT_EQ(-1, reg.getDisplayDigit(6));
    ASSERT_EQ(-1, reg.getDisplayDigit(7));

    setValue(reg, 30001, 2); // 000300.01
    ASSERT_EQ(1, reg.getDisplayDigit(0));
    ASSERT_EQ(0, reg.getDisplayDigit(1));
    ASSERT_EQ(0, reg.getDisplayDigit(2));
    ASSERT_EQ(0, reg.getDisplayDigit(3));
    ASSERT_EQ(3, reg.getDisplayDigit(4));
    ASSERT_EQ(-1, reg.getDisplayDigit(5));
    ASSERT_EQ(-1, reg.getDisplayDigit(6));
    ASSERT_EQ(-1, reg.getDisplayDigit(7));
}

TEST(TestRegister, ExchangeXY) {
    Calculator c(8);
    Register& x = c.getX();
    Register& y = c.getY();

    setValue(x, -1234567890); // expecting overflow error flag
    setValue(y, 1974);
    c.exchangeXY();

    ASSERT_EQ(1974, getAbsIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(false, x.isNegative());
    ASSERT_EQ(false, x.hasError());

    ASSERT_EQ(12345678, getAbsIntValue(y));
    ASSERT_EQ(6, y.getPointPos());
    ASSERT_EQ(true, y.isNegative());
    ASSERT_EQ(true, y.hasError()); // overflow error flag
}