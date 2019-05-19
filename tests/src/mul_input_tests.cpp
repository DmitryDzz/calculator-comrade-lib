//
// Created by dmitrydzz on 07.01.19.
//

#include <gmock/gmock.h>

#include "calculator/calculator.h"
#include "calculator/register.h"
#include "calculator/config.h"
#include "calc_helper.h"

using calculatorcomrade::Calculator;
using calculatorcomrade::Config;
using calculatorcomrade::Register;
using calculatorcomrade::Button;
using calculatorcomrade::Operation;

// Input: 2*==
TEST(TestMul, Mul1) {
    Calculator calc(Config::DEFAULT_SIZE);
    Register& x = calc.getX();
    Register& y = calc.getY();

    calc.input(Button::d2);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    ASSERT_EQ(Operation::add, calc.getOperation());

    calc.input(Button::mul);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    ASSERT_EQ(Operation::mul, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(4, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(8, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, calc.getOperation());
}

// Input: 2*3===
TEST(TestMul, Mul2) {
    Calculator calc(Config::DEFAULT_SIZE);
    Register& x = calc.getX();
    Register& y = calc.getY();

    calc.input(Button::d2);
    calc.input(Button::mul);
    calc.input(Button::d3);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(6, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(12, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(24, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, calc.getOperation());
}

// Input: 2*3=4*5==
TEST(TestMul, Mul3) {
    Calculator calc(Config::DEFAULT_SIZE);
    Register& x = calc.getX();
    Register& y = calc.getY();

    calc.input(Button::d2);
    calc.input(Button::mul);
    calc.input(Button::d3);
    calc.input(Button::equals);
    calc.input(Button::d4);
    ASSERT_EQ(4, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, calc.getOperation());

    calc.input(Button::mul);
    ASSERT_EQ(4, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, calc.getOperation());

    calc.input(Button::d5);
    ASSERT_EQ(5, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(4, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(20, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(4, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(80, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(4, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, calc.getOperation());
}

// Input: 2*3*4*5===
TEST(TestMul, Mul4) {
    Calculator calc(Config::DEFAULT_SIZE);
    Register& x = calc.getX();
    Register& y = calc.getY();

    calc.input(Button::d2);
    calc.input(Button::mul);
    calc.input(Button::d3);
    calc.input(Button::mul);
    ASSERT_EQ(6, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, calc.getOperation());

    calc.input(Button::d4);
    ASSERT_EQ(4, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(6, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, calc.getOperation());

    calc.input(Button::mul);
    ASSERT_EQ(24, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(6, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, calc.getOperation());

    calc.input(Button::d5);
    ASSERT_EQ(5, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(24, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(120, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(24, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(2880, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(24, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(69120, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(24, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, calc.getOperation());
}

// Input: 2*3=4==
TEST(TestMul, Mul5) {
    Calculator calc(Config::DEFAULT_SIZE);
    Register& x = calc.getX();
    Register& y = calc.getY();

    calc.input(Button::d2);
    calc.input(Button::mul);
    calc.input(Button::d3);
    calc.input(Button::equals);
    calc.input(Button::d4);
    ASSERT_EQ(4, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(8, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(16, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, calc.getOperation());
}

// Input: 2*3=*==
TEST(TestMul, Mul6) {
    Calculator calc(Config::DEFAULT_SIZE);
    Register& x = calc.getX();
    Register& y = calc.getY();

    calc.input(Button::d2);
    calc.input(Button::mul);
    calc.input(Button::d3);
    calc.input(Button::equals);
    calc.input(Button::mul);
    ASSERT_EQ(6, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(36, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(6, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(216, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(6, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, calc.getOperation());
}

// Input: 2*3*==
TEST(TestMul, Mul7) {
    Calculator calc(Config::DEFAULT_SIZE);
    Register& x = calc.getX();
    Register& y = calc.getY();

    calc.input(Button::d2);
    calc.input(Button::mul);
    calc.input(Button::d3);
    calc.input(Button::mul);
    ASSERT_EQ(6, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(36, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(6, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, calc.getOperation());

    calc.input(Button::equals);
    ASSERT_EQ(216, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(6, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, calc.getOperation());
}
