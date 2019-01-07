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

// Input: 2==
TEST(TestAddSub, NoOperations) {
    State expectedState(Config::DEFAULT_DIGITS);

    Calculator calc(Config::DEFAULT_DIGITS);
    calc.input(Button::d2);
    expectedState.x.setValue(2);
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 2+==
TEST(TestAddSub, IncCounter) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d2);
    expectedState.x.setValue(2);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::plus);
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(2);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(4);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 2-==
TEST(TestAddSub, DecCounter) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d2);
    expectedState.x.setValue(2);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::minus);
    expectedState.x.setValue(2);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(-2);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(-4);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 8-1===
TEST(TestAddSub, Subtraction) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d8);
    expectedState.x.setValue(8);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::minus);
    expectedState.x.setValue(8);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d1);
    expectedState.x.setValue(1);
    expectedState.y.setValue(8);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(7);
    expectedState.y.setValue(1);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(6);
    expectedState.y.setValue(1);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(5);
    expectedState.y.setValue(1);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: -3+2===
TEST(TestAddSub, InvertedSubtraction) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::minus);
    expectedState.x.setValue(0);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d3);
    expectedState.x.setValue(3);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::plus);
    expectedState.x.setValue(-3);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d2);
    expectedState.x.setValue(2);
    expectedState.y.setValue(-3);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(-1);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(1);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(3);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 2+3=8-1==
TEST(TestAddSub, TwoSeparateCalculationsInARow) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d2);
    expectedState.x.setValue(2);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::plus);
    expectedState.x.setValue(2);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d3);
    expectedState.x.setValue(3);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(5);
    expectedState.y.setValue(3);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d8);
    expectedState.x.setValue(8);
    expectedState.y.setValue(3);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::minus);
    expectedState.x.setValue(8);
    expectedState.y.setValue(3);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d1);
    expectedState.x.setValue(1);
    expectedState.y.setValue(8);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(7);
    expectedState.y.setValue(1);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(6);
    expectedState.y.setValue(1);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 2+7-3+1==
TEST(TestAddSub, FourCalculationsInARow) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d2);
    expectedState.x.setValue(2);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::plus);
    expectedState.x.setValue(2);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d7);
    expectedState.x.setValue(7);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::minus);
    expectedState.x.setValue(9);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d3);
    expectedState.x.setValue(3);
    expectedState.y.setValue(9);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::plus);
    expectedState.x.setValue(6);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d1);
    expectedState.x.setValue(1);
    expectedState.y.setValue(6);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(7);
    expectedState.y.setValue(1);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(8);
    expectedState.y.setValue(1);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 9-2=3==
TEST(TestAddSub, ExtraTest1) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d9);
    expectedState.x.setValue(9);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::minus);
    expectedState.x.setValue(9);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d2);
    expectedState.x.setValue(2);
    expectedState.y.setValue(9);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(7);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d3);
    expectedState.x.setValue(3);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(1);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(-1);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 8-1=-===
TEST(TestAddSub, ExtraTest2) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d8);
    expectedState.x.setValue(8);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::minus);
    expectedState.x.setValue(8);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d1);
    expectedState.x.setValue(1);
    expectedState.y.setValue(8);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(7);
    expectedState.y.setValue(1);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::minus);
    expectedState.x.setValue(7);
    expectedState.y.setValue(1);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(-6);
    expectedState.y.setValue(7);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(-13);
    expectedState.y.setValue(7);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(-20);
    expectedState.y.setValue(7);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 2+7-===
TEST(TestAddSub, ExtraTest3) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d2);
    expectedState.x.setValue(2);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::plus);
    expectedState.x.setValue(2);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d7);
    expectedState.x.setValue(7);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::minus);
    expectedState.x.setValue(9);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(-9);
    expectedState.y.setValue(9);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(-18);
    expectedState.y.setValue(9);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(-27);
    expectedState.y.setValue(9);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());
}
