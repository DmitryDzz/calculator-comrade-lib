//
// Created by dmitrydzz on 07.01.19.
//

#include <gmock/gmock.h>

#include "calculator/calculator.h"
#include "calculator/config.h"

using calculatorcomrade::Calculator;
using calculatorcomrade::Button;
using calculatorcomrade::State;
using calculatorcomrade::Operation;

// Input: 2*==
TEST(TestMul, Mul1) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d2);
    expectedState.x.setValue(2);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::mul);
    expectedState.x.setValue(2);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(4);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(8);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 2*3===
TEST(TestMul, Mul2) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d2);
    expectedState.x.setValue(2);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::mul);
    expectedState.x.setValue(2);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d3);
    expectedState.x.setValue(3);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(6);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(12);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(24);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 2*3=4*5==
TEST(TestMul, Mul3) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d2);
    expectedState.x.setValue(2);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::mul);
    expectedState.x.setValue(2);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d3);
    expectedState.x.setValue(3);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(6);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d4);
    expectedState.x.setValue(4);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::mul);
    expectedState.x.setValue(4);
    expectedState.y.setValue(4);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d5);
    expectedState.x.setValue(5);
    expectedState.y.setValue(4);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(20);
    expectedState.y.setValue(4);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(80);
    expectedState.y.setValue(4);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 2*3*4*5===
TEST(TestMul, Mul4) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d2);
    expectedState.x.setValue(2);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::mul);
    expectedState.x.setValue(2);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d3);
    expectedState.x.setValue(3);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::mul);
    expectedState.x.setValue(6);
    expectedState.y.setValue(6);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d4);
    expectedState.x.setValue(4);
    expectedState.y.setValue(6);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::mul);
    expectedState.x.setValue(24);
    expectedState.y.setValue(24);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d5);
    expectedState.x.setValue(5);
    expectedState.y.setValue(24);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(120);
    expectedState.y.setValue(24);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(2880);
    expectedState.y.setValue(24);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(69120);
    expectedState.y.setValue(24);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 2*3=4==
TEST(TestMul, Mul5) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d2);
    expectedState.x.setValue(2);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::mul);
    expectedState.x.setValue(2);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d3);
    expectedState.x.setValue(3);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(6);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d4);
    expectedState.x.setValue(4);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(8);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(16);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 2*3=*==
TEST(TestMul, Mul6) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d2);
    expectedState.x.setValue(2);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::mul);
    expectedState.x.setValue(2);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d3);
    expectedState.x.setValue(3);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(6);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::mul);
    expectedState.x.setValue(6);
    expectedState.y.setValue(6);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(36);
    expectedState.y.setValue(6);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(216);
    expectedState.y.setValue(6);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 2*3*==
TEST(TestMul, Mul7) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d2);
    expectedState.x.setValue(2);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::mul);
    expectedState.x.setValue(2);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d3);
    expectedState.x.setValue(3);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::mul);
    expectedState.x.setValue(6);
    expectedState.y.setValue(6);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(36);
    expectedState.y.setValue(6);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(216);
    expectedState.y.setValue(6);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());
}
