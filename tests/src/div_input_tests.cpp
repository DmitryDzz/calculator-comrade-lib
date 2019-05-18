//
// Created by dmitrydzz on 07.01.19.
//

#include <gmock/gmock.h>

#include "calculator/calculator.h"
#include "calculator/config.h"
#include "calc_helper.h"

using calculatorcomrade::Calculator;
using calculatorcomrade::Button;
using calculatorcomrade::Register;
using calculatorcomrade::Operation;

// Input: 10/==
TEST(TestDiv, Div1) {
    Calculator calc(Config::DEFAULT_SIZE);
    Register& x = calc.getX();
    Register& y = calc.getY();

    calc.input(Button::d1);
    calc.input(Button::d0);
    ASSERT_EQ(10, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    ASSERT_EQ(Operation::add, calc.getOperation());

    calc.input(Button::div);
    ASSERT_EQ(10, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(1, getIntValue(x));
    ASSERT_EQ(1, x.getPointPos()); // 0.1
    ASSERT_EQ(10, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(1, getIntValue(x));
    ASSERT_EQ(2, x.getPointPos()); // 0.01
    ASSERT_EQ(10, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());
}

// Input: 24/2===
TEST(TestDiv, Div2) {
    Calculator calc(Config::DEFAULT_SIZE);
    Register& x = calc.getX();
    Register& y = calc.getY();

    calc.input(Button::d2);
    calc.input(Button::d4);
    ASSERT_EQ(24, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    ASSERT_EQ(Operation::add, calc.getOperation());

    calc.input(Button::div);
    ASSERT_EQ(24, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::d2);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(24, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(12, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(6, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());
}

// Input: 27/3=12/2==
TEST(TestDiv, Div3) {
    Calculator calc(Config::DEFAULT_SIZE);
    Register& x = calc.getX();
    Register& y = calc.getY();

    calc.input(Button::d2);
    calc.input(Button::d7);

    calc.input(Button::div);

    calc.input(Button::d3);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(27, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(9, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(3, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::d1);
    calc.input(Button::d2);
    ASSERT_EQ(12, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(3, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::div);
    ASSERT_EQ(12, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(3, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::d2);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(12, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(6, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());
}

// Input: 120/5/3/2===
TEST(TestDiv, Div4) {
    Calculator calc(Config::DEFAULT_SIZE);
    Register& x = calc.getX();
    Register& y = calc.getY();

    calc.input(Button::d1);
    calc.input(Button::d2);
    calc.input(Button::d0);

    calc.input(Button::div);

    calc.input(Button::d5);
    ASSERT_EQ(5, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(120, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::div);
    ASSERT_EQ(24, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(5, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::d3);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(24, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::div);
    ASSERT_EQ(8, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(3, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::d2);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(8, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(4, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(1, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());
}

// Input: 12/2=8==
TEST(TestDiv, Div5) {
    Calculator calc(Config::DEFAULT_SIZE);
    Register& x = calc.getX();
    Register& y = calc.getY();

    calc.input(Button::d1);
    calc.input(Button::d2);

    calc.input(Button::div);

    calc.input(Button::d2);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(12, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(6, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::d8);
    ASSERT_EQ(8, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(4, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());
}

// Input: 40/4=/==
TEST(TestDiv, Div6) {
    Calculator calc(Config::DEFAULT_SIZE);
    Register& x = calc.getX();
    Register& y = calc.getY();

    calc.input(Button::d4);
    calc.input(Button::d0);

    calc.input(Button::div);

    calc.input(Button::d4);
    ASSERT_EQ(4, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(40, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(10, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(4, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::div);
    ASSERT_EQ(10, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(4, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(1, getIntValue(x));
    ASSERT_EQ(1, x.getPointPos()); // 0.1
    ASSERT_EQ(10, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(1, getIntValue(x));
    ASSERT_EQ(2, x.getPointPos()); // 0.01
    ASSERT_EQ(10, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());
}

// Input: 40/4/==
TEST(TestDiv, Div7) {
    Calculator calc(Config::DEFAULT_SIZE);
    Register& x = calc.getX();
    Register& y = calc.getY();

    calc.input(Button::d4);
    calc.input(Button::d0);

    calc.input(Button::div);

    calc.input(Button::d4);
    ASSERT_EQ(4, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(40, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::div);
    ASSERT_EQ(10, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(4, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(1, getIntValue(x));
    ASSERT_EQ(1, x.getPointPos()); // 0.1
    ASSERT_EQ(10, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(1, getIntValue(x));
    ASSERT_EQ(2, x.getPointPos()); // 0.01
    ASSERT_EQ(10, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, calc.getOperation());
}
