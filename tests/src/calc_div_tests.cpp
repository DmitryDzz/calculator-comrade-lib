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

// Input: 10/==
TEST(TestDiv, Div1) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d1);
    calc.input(Button::d0);
    expectedState.x.setValue(10);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::div);
    expectedState.x.setValue(10);
    expectedState.y.setValue(1);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(1, 1); // 0.1
    expectedState.y.setValue(10);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(1, 2); // 0.01
    expectedState.y.setValue(10);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 24/2===
TEST(TestDiv, Div2) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d2);
    calc.input(Button::d4);
    expectedState.x.setValue(24);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::div);
    expectedState.x.setValue(24);
    expectedState.y.setValue(1);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d2);
    expectedState.x.setValue(2);
    expectedState.y.setValue(24);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(12);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(6);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(3);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 27/3=12/2==
TEST(TestDiv, Div3) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d2);
    calc.input(Button::d7);
    expectedState.x.setValue(27);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::div);
    expectedState.x.setValue(27);
    expectedState.y.setValue(1);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d3);
    expectedState.x.setValue(3);
    expectedState.y.setValue(27);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(9);
    expectedState.y.setValue(3);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d1);
    calc.input(Button::d2);
    expectedState.x.setValue(12);
    expectedState.y.setValue(3);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::div);
    expectedState.x.setValue(12);
    expectedState.y.setValue(1);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d2);
    expectedState.x.setValue(2);
    expectedState.y.setValue(12);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(6);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(3);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 120/5/3/2===
TEST(TestDiv, Div4) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d1);
    calc.input(Button::d2);
    calc.input(Button::d0);
    expectedState.x.setValue(120);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::div);
    expectedState.x.setValue(120);
    expectedState.y.setValue(1);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d5);
    expectedState.x.setValue(5);
    expectedState.y.setValue(120);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::div);
    expectedState.x.setValue(24);
    expectedState.y.setValue(1);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d3);
    expectedState.x.setValue(3);
    expectedState.y.setValue(24);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::div);
    expectedState.x.setValue(8);
    expectedState.y.setValue(1);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d2);
    expectedState.x.setValue(2);
    expectedState.y.setValue(8);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(4);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(2);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(1);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 12/2=8==
TEST(TestDiv, Div5) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d1);
    calc.input(Button::d2);
    expectedState.x.setValue(12);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::div);
    expectedState.x.setValue(12);
    expectedState.y.setValue(1);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d2);
    expectedState.x.setValue(2);
    expectedState.y.setValue(12);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(6);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d8);
    expectedState.x.setValue(8);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(4);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(2);
    expectedState.y.setValue(2);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 40/4=/==
TEST(TestDiv, Div6) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d4);
    calc.input(Button::d0);
    expectedState.x.setValue(40);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::div);
    expectedState.x.setValue(40);
    expectedState.y.setValue(1);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d4);
    expectedState.x.setValue(4);
    expectedState.y.setValue(40);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(10);
    expectedState.y.setValue(4);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::div);
    expectedState.x.setValue(10);
    expectedState.y.setValue(1);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(1, 1); // 0.1
    expectedState.y.setValue(10);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(1, 2); // 0.01
    expectedState.y.setValue(10);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 40/4/==
TEST(TestDiv, Div7) {
    State expectedState(Config::DEFAULT_DIGITS);
    Calculator calc(Config::DEFAULT_DIGITS);

    calc.input(Button::d4);
    calc.input(Button::d0);
    expectedState.x.setValue(40);
    expectedState.y.setValue(0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::div);
    expectedState.x.setValue(40);
    expectedState.y.setValue(1);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d4);
    expectedState.x.setValue(4);
    expectedState.y.setValue(40);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::div);
    expectedState.x.setValue(10);
    expectedState.y.setValue(1);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(1, 1);
    expectedState.y.setValue(10);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    expectedState.x.setValue(1, 2);
    expectedState.y.setValue(10);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());
}
