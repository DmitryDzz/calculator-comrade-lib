/**
 * Calculator Comrade Library
 * License: https://github.com/DmitryDzz/calculator-comrade-lib/blob/master/LICENSE
 * Author: Dmitry Dzakhov
 * Email: info@robot-mitya.ru
 */
#include <gmock/gmock.h>

#include "calculator/calculator.h"
#include "calculator/config.h"
#include "calc_helper.h"

using namespace calculatorcomrade;

// Input: 2==
TEST(TestAddSub, NoOperations) {
    Calculator calc(Config::DEFAULT_SIZE);
    Register& x = calc.getX();
    Register& y = calc.getY();

    calc.input(Button::d2);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    ASSERT_EQ(Operation::add, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    ASSERT_EQ(Operation::add, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    ASSERT_EQ(Operation::add, calc.getOperation());
}

// Input: 2+==
TEST(TestAddSub, IncCounter) {
    Calculator calc(Config::DEFAULT_SIZE);
    Register& x = calc.getX();
    Register& y = calc.getY();

    calc.input(Button::d2);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    ASSERT_EQ(Operation::add, calc.getOperation());

    calc.input(Button::plus);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    ASSERT_EQ(Operation::add, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::add, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(4, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::add, calc.getOperation());
}

// Input: 2-==
TEST(TestAddSub, DecCounter) {
    Calculator calc(Config::DEFAULT_SIZE);
    Register& x = calc.getX();
    Register& y = calc.getY();

    calc.input(Button::d2);
    calc.input(Button::minus);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(0, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::sub, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(-2, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::sub, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(-4, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::sub, calc.getOperation());
}

// Input: 8-1===
TEST(TestAddSub, Subtraction) {
    Calculator calc(Config::DEFAULT_SIZE);
    Register& x = calc.getX();
    Register& y = calc.getY();

    calc.input(Button::d8);
    calc.input(Button::minus);
    calc.input(Button::d1);
    ASSERT_EQ(1, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(8, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::sub, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(7, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(1, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::sub, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(6, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(1, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::sub, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(5, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(1, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::sub, calc.getOperation());
}

// Input: -3+2===
TEST(TestAddSub, InvertedSubtraction) {
    Calculator calc(Config::DEFAULT_SIZE);
    Register& x = calc.getX();
    Register& y = calc.getY();

    calc.input(Button::minus);
    ASSERT_TRUE(x.isZero());
    ASSERT_TRUE(y.isZero());
    ASSERT_EQ(Operation::sub, calc.getOperation());

    calc.input(Button::d3);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    ASSERT_EQ(Operation::sub, calc.getOperation());

    calc.input(Button::plus);
    ASSERT_EQ(-3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    ASSERT_EQ(Operation::add, calc.getOperation());

    calc.input(Button::d2);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(-3, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::add, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(-1, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::add, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(1, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::add, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::add, calc.getOperation());
}

// Input: 2+3=8-1==
TEST(TestAddSub, TwoSeparateCalculationsInARow) {
    Calculator calc(Config::DEFAULT_SIZE);
    Register& x = calc.getX();
    Register& y = calc.getY();

    calc.input(Button::d2);
    calc.input(Button::plus);
    calc.input(Button::d3);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::add, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(5, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(3, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::add, calc.getOperation());

    calc.input(Button::d8);
    ASSERT_EQ(8, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(3, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::add, calc.getOperation());

    calc.input(Button::minus);
    ASSERT_EQ(8, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(3, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::sub, calc.getOperation());

    calc.input(Button::d1);
    ASSERT_EQ(1, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(8, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::sub, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(7, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(1, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::sub, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(6, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(1, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::sub, calc.getOperation());
}

// Input: 2+7-3+1==
TEST(TestAddSub, FourCalculationsInARow) {
    Calculator calc(Config::DEFAULT_SIZE);
    Register& x = calc.getX();
    Register& y = calc.getY();

    calc.input(Button::d2);
    calc.input(Button::plus);
    calc.input(Button::d7);
    calc.input(Button::minus);
    ASSERT_EQ(9, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    ASSERT_EQ(Operation::sub, calc.getOperation());

    calc.input(Button::d3);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(9, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::sub, calc.getOperation());

    calc.input(Button::plus);
    ASSERT_EQ(6, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    ASSERT_EQ(Operation::add, calc.getOperation());

    calc.input(Button::d1);
    ASSERT_EQ(1, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(6, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::add, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(7, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(1, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::add, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(8, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(1, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::add, calc.getOperation());
}

// Input: 9-2=3==
TEST(TestAddSub, ExtraTest1) {
    Calculator calc(Config::DEFAULT_SIZE);
    Register& x = calc.getX();
    Register& y = calc.getY();

    calc.input(Button::d9);
    calc.input(Button::minus);
    calc.input(Button::d2);
    calc.input(Button::equals);
    ASSERT_EQ(7, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::sub, calc.getOperation());

    calc.input(Button::d3);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::sub, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(1, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::sub, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(-1, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::sub, calc.getOperation());
}

// Input: 8-1=-===
TEST(TestAddSub, ExtraTest2) {
    Calculator calc(Config::DEFAULT_SIZE);
    Register& x = calc.getX();
    Register& y = calc.getY();

    calc.input(Button::d8);
    calc.input(Button::minus);
    calc.input(Button::d1);
    calc.input(Button::equals);
    ASSERT_EQ(7, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(1, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::sub, calc.getOperation());

    calc.input(Button::minus);
    ASSERT_EQ(7, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(1, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::sub, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(-6, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(7, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::sub, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(-13, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(7, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::sub, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(-20, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(7, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::sub, calc.getOperation());
}

// Input: 2+7-===
TEST(TestAddSub, ExtraTest3) {
    Calculator calc(Config::DEFAULT_SIZE);
    Register& x = calc.getX();
    Register& y = calc.getY();

    calc.input(Button::d2);
    calc.input(Button::plus);
    calc.input(Button::d7);
    calc.input(Button::minus);
    ASSERT_EQ(9, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    ASSERT_EQ(Operation::sub, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(-9, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(9, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::sub, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(-18, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(9, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::sub, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(-27, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(9, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::sub, calc.getOperation());
}
