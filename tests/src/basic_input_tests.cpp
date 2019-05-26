/**
 * Calculator Comrade Library
 * License: https://github.com/DmitryDzz/calculator-comrade-lib/blob/master/LICENSE
 * Author: Dmitry Dzakhov
 * Email: info@robot-mitya.ru
 */
#include <gmock/gmock.h>

#include "calculator/calculator.h"
#include "calculator/button.h"
#include "calculator/operation.h"
#include "calc_helper.h"

using namespace calculatorcomrade;

#define TEST_CALCULATOR_INPUT(test_name) TEST(BasicInput, test_name)

TEST_CALCULATOR_INPUT(ClearEntry1) {
    Calculator calc(Config::DEFAULT_SIZE);
    Register defaultRegister(Config::DEFAULT_SIZE);
    ASSERT_EQ(defaultRegister, calc.getX());
    ASSERT_EQ(defaultRegister, calc.getY());
    ASSERT_EQ(defaultRegister, calc.getM());
    ASSERT_EQ(Operation::add, calc.getOperation());
    calc.input(Button::d1);
    ASSERT_NE(defaultRegister, calc.getX());
    ASSERT_EQ(defaultRegister, calc.getY());
    ASSERT_EQ(defaultRegister, calc.getM());
    ASSERT_EQ(Operation::add, calc.getOperation());
    calc.input(Button::ce);
    ASSERT_EQ(defaultRegister, calc.getX());
    ASSERT_EQ(defaultRegister, calc.getY());
    ASSERT_EQ(defaultRegister, calc.getM());
    ASSERT_EQ(Operation::add, calc.getOperation());
}

TEST_CALCULATOR_INPUT(ClearEntry2) {
    Calculator calc;
    Register &x = calc.getX();

    calc.input(Button::d1);
    calc.input(Button::plus);
    calc.input(Button::d2);
    calc.input(Button::ce);
    calc.input(Button::d3);
    calc.input(Button::equals);
    ASSERT_EQ(4, getIntValue(x));
    calc.input(Button::ce);
    ASSERT_EQ(4, getIntValue(x));
}

TEST_CALCULATOR_INPUT(ClearEntry3) {
    Calculator c;
    Register &x = c.getX();
    Register &y = c.getY();

    c.input(Button::d2);
    c.input(Button::plus);
    c.input(Button::equals);
    c.input(Button::equals);
    ASSERT_EQ(4, getIntValue(x));
    ASSERT_EQ(2, getIntValue(y));
    c.input(Button::ce);
    ASSERT_EQ(4, getIntValue(x));
    ASSERT_EQ(2, getIntValue(y));
}

TEST_CALCULATOR_INPUT(ClearEntry4) {
    Calculator c;
    Register &x = c.getX();
    Register &y = c.getY();

    c.input(Button::d3);
    c.input(Button::mul);
    c.input(Button::ce);
    c.input(Button::equals);
    ASSERT_EQ(9, getIntValue(x));
    ASSERT_EQ(3, getIntValue(y));
}

TEST_CALCULATOR_INPUT(ClearAll) {
    Calculator c(8);
    Register &x = c.getX();
    Register &y = c.getY();


    c.input(Button::minus);
    for (int8_t i = 0; i < 8; i++)
        c.input(Button::d9);
    c.input(Button::mul);
    c.input(Button::d9);
    c.input(Button::equals);
    ASSERT_EQ(-89999999, getIntValue(x)); // 8.9999999 in X
    ASSERT_EQ(7, x.getPointPos());
    ASSERT_EQ(-99999999, getIntValue(y)); // 99999999 in Y
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_TRUE(x.isNegative());
    ASSERT_TRUE(x.hasError());
    ASSERT_TRUE(x.hasOverflow());

    c.input(Button::ca);
    ASSERT_EQ(0, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(0, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_FALSE(x.isNegative());
    ASSERT_FALSE(x.hasError());
    ASSERT_FALSE(x.hasOverflow());
}

TEST_CALCULATOR_INPUT(CeAfterOverflow) {
    Calculator c(8);
    Register &x = c.getX();
    Register &y = c.getY();

    for (int8_t i = 0; i < 8; i++)
        c.input(Button::d9);
    c.input(Button::mul);
    c.input(Button::d9);
    c.input(Button::equals);
    ASSERT_EQ(89999999, getIntValue(x)); // 8.9999999 in X
    ASSERT_EQ(7, x.getPointPos());
    ASSERT_EQ(99999999, getIntValue(y)); // 99999999 in Y
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_TRUE(x.hasError());
    ASSERT_TRUE(x.hasOverflow());

    c.input(Button::ce);
    ASSERT_EQ(89999999, getIntValue(x)); // 8.9999999 in X
    ASSERT_EQ(7, x.getPointPos());
    ASSERT_EQ(99999999, getIntValue(y)); // 99999999 in Y
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_FALSE(x.hasError());
    ASSERT_FALSE(x.hasOverflow());

    c.input(Button::ce);
    ASSERT_EQ(89999999, getIntValue(x)); // 8.9999999 in X
    ASSERT_EQ(7, x.getPointPos());
    ASSERT_EQ(99999999, getIntValue(y)); // 99999999 in Y
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_FALSE(x.hasError());
    ASSERT_FALSE(x.hasOverflow());
}

TEST_CALCULATOR_INPUT(CeCaAfterOverflow) {
    Calculator c(8);
    Register &x = c.getX();
    Register &y = c.getY();


    c.input(Button::minus);
    for (int8_t i = 0; i < 8; i++)
        c.input(Button::d9);
    c.input(Button::mul);
    c.input(Button::d9);
    c.input(Button::equals);
    ASSERT_EQ(-89999999, getIntValue(x)); // 8.9999999 in X
    ASSERT_EQ(7, x.getPointPos());
    ASSERT_EQ(-99999999, getIntValue(y)); // 99999999 in Y
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_TRUE(x.isNegative());
    ASSERT_TRUE(x.hasError());
    ASSERT_TRUE(x.hasOverflow());

    c.input(Button::ceca);
    ASSERT_EQ(-89999999, getIntValue(x)); // 8.9999999 in X
    ASSERT_EQ(7, x.getPointPos());
    ASSERT_EQ(-99999999, getIntValue(y)); // 99999999 in Y
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_TRUE(x.isNegative());
    ASSERT_FALSE(x.hasError());
    ASSERT_FALSE(x.hasOverflow());

    c.input(Button::ceca);
    ASSERT_EQ(0, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(0, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_FALSE(x.isNegative());
    ASSERT_FALSE(x.hasError());
    ASSERT_FALSE(x.hasOverflow());
}

TEST_CALCULATOR_INPUT(CeAfterError) {
    Calculator c(8);
    Register &x = c.getX();
    Register &y = c.getY();

    c.input(Button::d9);
    c.input(Button::div);
    c.input(Button::d0);
    c.input(Button::equals);
    ASSERT_EQ(0, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(x.hasError());
    ASSERT_FALSE(x.hasOverflow());

    c.input(Button::ce);
    ASSERT_EQ(0, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(x.hasError());
    ASSERT_FALSE(x.hasOverflow());

    c.input(Button::ca);
    ASSERT_EQ(0, getAbsIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(0, getAbsIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_FALSE(x.hasError());
    ASSERT_FALSE(x.hasOverflow());
}

TEST_CALCULATOR_INPUT(CeCaAfterError) {
    Calculator c(8);
    Register &x = c.getX();
    Register &y = c.getY();

    c.input(Button::d9);
    c.input(Button::div);
    c.input(Button::d0);
    c.input(Button::equals);
    ASSERT_EQ(0, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(x.hasError());
    ASSERT_FALSE(x.hasOverflow());

    c.input(Button::ceca);
    ASSERT_EQ(0, getAbsIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(0, getAbsIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_FALSE(x.hasError());
    ASSERT_FALSE(x.hasOverflow());
}

TEST_CALCULATOR_INPUT(CeCaAfterEquals) {
    Calculator c(8);
    Register &x = c.getX();
    Register &y = c.getY();
    Register &m = c.getM();

    c.input(Button::d2);
    c.input(Button::mul);
    c.input(Button::d3);
    c.input(Button::equals);
    c.input(Button::ceca);
    ASSERT_TRUE(x.isZero());
    ASSERT_TRUE(y.isZero());
    ASSERT_TRUE(c.getOperation() == Operation::add);

    c.input(Button::d2);
    c.input(Button::memPlus);
    c.input(Button::div);
    c.input(Button::d0);
    c.input(Button::equals);
    c.input(Button::ceca);
    ASSERT_TRUE(x.isZero());
    ASSERT_TRUE(y.isZero());
    ASSERT_FALSE(m.isZero());
    ASSERT_TRUE(c.getOperation() == Operation::add);
    ASSERT_FALSE(x.hasError());
    ASSERT_FALSE(x.hasOverflow());
}

TEST_CALCULATOR_INPUT(CeCaAfterOperation) {
    Calculator c(8);
    Register &x = c.getX();
    Register &y = c.getY();

    c.input(Button::d2);
    c.input(Button::mul);
    c.input(Button::ceca);
    ASSERT_TRUE(x.isZero());
    ASSERT_TRUE(y.isZero());
    ASSERT_TRUE(c.getOperation() == Operation::add);
}

TEST_CALCULATOR_INPUT(ZeroTyping) {
    Calculator c(4);
    Register defaultRegister(4);
    for (int i = 0; i < 10; i++) {
        c.input(Button::d0);
        ASSERT_EQ(defaultRegister, c.getX());
        ASSERT_EQ(defaultRegister, c.getY());
        ASSERT_EQ(defaultRegister, c.getM());
        ASSERT_EQ(Operation::add, c.getOperation());
    }
}

TEST_CALCULATOR_INPUT(ZeroTypingAfterPoint) {
    Calculator c(4);
    c.input(Button::point);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::d1);

    Register &x = c.getX();
    ASSERT_EQ(1, getIntValue(x));
    ASSERT_EQ(3, x.getPointPos());
}

TEST_CALCULATOR_INPUT(PositiveInt) {
    Calculator c(4);
    Register expected(4);
    Register& x = c.getX();

    c.input(Button::d1);
    expected.setDigit(0, 1);
    ASSERT_EQ(expected, x);

    c.input(Button::d2);
    expected.setDigit(0, 2);
    expected.setDigit(1, 1);
    ASSERT_EQ(expected, x);

    c.input(Button::d3);
    expected.setDigit(0, 3);
    expected.setDigit(1, 2);
    expected.setDigit(2, 1);
    ASSERT_EQ(expected, x);

    c.input(Button::d4);
    expected.setDigit(0, 4);
    expected.setDigit(1, 3);
    expected.setDigit(2, 2);
    expected.setDigit(3, 1);
    ASSERT_EQ(expected, x);

    c.input(Button::d5);
    ASSERT_EQ(expected, x);
}

TEST_CALCULATOR_INPUT(NegativeInt) {
    Calculator c(4);
    Register expected(4);
    Register& x = c.getX();

    c.input(Button::minus);
    ASSERT_EQ(expected, x);
    ASSERT_EQ(Operation::sub, c.getOperation());

    c.input(Button::d1);
    expected.setDigit(0, 1);
    ASSERT_EQ(expected, x);

    c.input(Button::d2);
    expected.setDigit(0, 2);
    expected.setDigit(1, 1);
    ASSERT_EQ(expected, x);

    c.input(Button::d3);
    expected.setDigit(0, 3);
    expected.setDigit(1, 2);
    expected.setDigit(2, 1);
    ASSERT_EQ(expected, x);

    c.input(Button::d4);
    expected.setDigit(0, 4);
    expected.setDigit(1, 3);
    expected.setDigit(2, 2);
    expected.setDigit(3, 1);
    ASSERT_EQ(expected, x);

    c.input(Button::d5);
    ASSERT_EQ(expected, x);
}

TEST_CALCULATOR_INPUT(PositiveReal) {
    Calculator c(4);
    Register& x = c.getX();

    c.input(Button::d1);
    ASSERT_EQ(1, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());

    c.input(Button::point);
    ASSERT_EQ(1, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());

    c.input(Button::d2);
    ASSERT_EQ(12, getIntValue(x));
    ASSERT_EQ(1, x.getPointPos());

    c.input(Button::d3);
    ASSERT_EQ(123, getIntValue(x));
    ASSERT_EQ(2, x.getPointPos());

    c.input(Button::point); // should ignore this input
    ASSERT_EQ(123, getIntValue(x));
    ASSERT_EQ(2, x.getPointPos());

    c.input(Button::d4);
    ASSERT_EQ(1234, getIntValue(x));
    ASSERT_EQ(3, x.getPointPos());

    c.input(Button::d5);
    ASSERT_EQ(1234, getIntValue(x));
    ASSERT_EQ(3, x.getPointPos());
}

TEST_CALCULATOR_INPUT(ZeroInHighDigit) {
    Calculator c(4);

    // ".1234" input should be "0.123" on display
    c.input(Button::point);
    c.input(Button::d1);
    c.input(Button::d2);
    c.input(Button::d3);
    c.input(Button::d4);

    Register &x = c.getX();
    ASSERT_EQ(0, x.getDigit(3));
    ASSERT_EQ(1, x.getDigit(2));
    ASSERT_EQ(2, x.getDigit(1));
    ASSERT_EQ(3, x.getDigit(0));
    ASSERT_EQ(3, x.getPointPos());
}

TEST_CALCULATOR_INPUT(SerialSum) {
    Calculator c(Config::MIN_SIZE);
    Register& x = c.getX();
    Register& y = c.getY();
    
    c.input(Button::d2);
    c.input(Button::plus);
    c.input(Button::d3);
    c.input(Button::equals);
    ASSERT_EQ(5, getAbsIntValue(x)); // 5 in X
    ASSERT_EQ(3, getAbsIntValue(y)); // 3 in Y
    c.input(Button::equals);
    ASSERT_EQ(8, getAbsIntValue(x)); // 8 in X
    ASSERT_EQ(3, getAbsIntValue(y)); // 3 in Y
    c.input(Button::equals);
    ASSERT_EQ(11, getAbsIntValue(x)); // 11 in X
    ASSERT_EQ(3, getAbsIntValue(y)); // 3 in Y
}

TEST_CALCULATOR_INPUT(SerialSub) {
    Calculator c(Config::MIN_SIZE);
    Register& x = c.getX();
    Register& y = c.getY();

    c.input(Button::d8);
    c.input(Button::minus);
    c.input(Button::d2);
    c.input(Button::equals);
    ASSERT_EQ(6, getAbsIntValue(x)); // 6 in X
    ASSERT_EQ(2, getAbsIntValue(y)); // 2 in Y
    c.input(Button::equals);
    ASSERT_EQ(4, getAbsIntValue(x)); // 4 in X
    ASSERT_EQ(2, getAbsIntValue(y)); // 2 in Y
    c.input(Button::equals);
    ASSERT_EQ(2, getAbsIntValue(x)); // 2 in X
    ASSERT_EQ(2, getAbsIntValue(y)); // 2 in Y
}

TEST_CALCULATOR_INPUT(SerialMul) {
    Calculator c(Config::MIN_SIZE);
    Register& x = c.getX();
    Register& y = c.getY();

    c.input(Button::d2);
    c.input(Button::mul);
    c.input(Button::d3);
    c.input(Button::equals);
    ASSERT_EQ(6, getAbsIntValue(x)); // 6 in X
    ASSERT_EQ(2, getAbsIntValue(y)); // 2 in Y
    c.input(Button::equals);
    ASSERT_EQ(12, getAbsIntValue(x)); // 12 in X
    ASSERT_EQ(2, getAbsIntValue(y)); // 2 in Y
    c.input(Button::equals);
    ASSERT_EQ(24, getAbsIntValue(x)); // 24 in X
    ASSERT_EQ(2, getAbsIntValue(y)); // 2 in Y
}

TEST_CALCULATOR_INPUT(SerialDiv) {
    Calculator c(4);
    Register& x = c.getX();
    Register& y = c.getY();

    c.input(Button::d2);
    c.input(Button::div);
    c.input(Button::d1);
    c.input(Button::d0);
    c.input(Button::equals);               // 2 / 10 = ...
    ASSERT_EQ(2, getAbsIntValue(x)); // 0.2 in X
    ASSERT_EQ(1, x.getPointPos());
    ASSERT_EQ(10, getAbsIntValue(y)); // 2 in Y
    c.input(Button::equals);
    ASSERT_EQ(2, getAbsIntValue(x)); // 0.02 in X
    ASSERT_EQ(2, x.getPointPos());
    ASSERT_EQ(10, getAbsIntValue(y)); // 2 in Y
    c.input(Button::equals);
    ASSERT_EQ(2, getAbsIntValue(x)); // 0.002 in X
    ASSERT_EQ(3, x.getPointPos());
    ASSERT_EQ(10, getAbsIntValue(y)); // 2 in Y
}

TEST_CALCULATOR_INPUT(DoubleOperation) {
    Calculator c(4);
    Register &x = c.getX();

    c.input(Button::d8);
    c.input(Button::div);
    c.input(Button::div);
    ASSERT_EQ(8, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
}

TEST_CALCULATOR_INPUT(ChangeSign1) {
    Calculator c(8);
    Register &x = c.getX();

    c.input(Button::d9);
    c.input(Button::plus);
    c.input(Button::d5);
    c.input(Button::changeSign);
    c.input(Button::equals);
    ASSERT_EQ(4, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
}

TEST_CALCULATOR_INPUT(ChangeSign2) {
    Calculator c(8);
    Register &x = c.getX();

    c.input(Button::d0);
    c.input(Button::changeSign);
    ASSERT_EQ(0, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_FALSE(x.isNegative());
}
