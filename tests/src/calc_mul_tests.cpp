//
// Created by dmitrydzz on 07.01.19.
//

#include <gmock/gmock.h>

#include "calculator/calculator.h"
#include "calculator/config.h"
#include "calc_helper.h"

using calculatorcomrade::Calculator;
using calculatorcomrade::Button;
using calculatorcomrade::State;
using calculatorcomrade::Operation;

// Input: 2*==
TEST(TestMul, Mul1) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d2);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::mul);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 4);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 8);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 2*3===
TEST(TestMul, Mul2) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d2);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::mul);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d3);
    setValue(expectedState.x, 3);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 6);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 12);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 24);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 2*3=4*5==
TEST(TestMul, Mul3) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d2);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::mul);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d3);
    setValue(expectedState.x, 3);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 6);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d4);
    setValue(expectedState.x, 4);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::mul);
    setValue(expectedState.x, 4);
    setValue(expectedState.y, 4);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d5);
    setValue(expectedState.x, 5);
    setValue(expectedState.y, 4);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 20);
    setValue(expectedState.y, 4);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 80);
    setValue(expectedState.y, 4);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 2*3*4*5===
TEST(TestMul, Mul4) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d2);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::mul);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d3);
    setValue(expectedState.x, 3);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::mul);
    setValue(expectedState.x, 6);
    setValue(expectedState.y, 6);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d4);
    setValue(expectedState.x, 4);
    setValue(expectedState.y, 6);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::mul);
    setValue(expectedState.x, 24);
    setValue(expectedState.y, 24);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d5);
    setValue(expectedState.x, 5);
    setValue(expectedState.y, 24);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 120);
    setValue(expectedState.y, 24);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 2880);
    setValue(expectedState.y, 24);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 69120);
    setValue(expectedState.y, 24);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 2*3=4==
TEST(TestMul, Mul5) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d2);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::mul);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d3);
    setValue(expectedState.x, 3);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 6);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d4);
    setValue(expectedState.x, 4);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 8);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 16);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 2*3=*==
TEST(TestMul, Mul6) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d2);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::mul);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d3);
    setValue(expectedState.x, 3);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 6);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::mul);
    setValue(expectedState.x, 6);
    setValue(expectedState.y, 6);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 36);
    setValue(expectedState.y, 6);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 216);
    setValue(expectedState.y, 6);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 2*3*==
TEST(TestMul, Mul7) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d2);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::mul);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d3);
    setValue(expectedState.x, 3);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::mul);
    setValue(expectedState.x, 6);
    setValue(expectedState.y, 6);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 36);
    setValue(expectedState.y, 6);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 216);
    setValue(expectedState.y, 6);
    expectedState.operation = Operation::mul;
    ASSERT_EQ(expectedState, calc.getState());
}
