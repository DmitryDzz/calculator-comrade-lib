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

// Input: 10/==
TEST(TestDiv, Div1) {
    State expectedState(Config::DEFAULT_SIZE);
    Calculator calc(Config::DEFAULT_SIZE);

    calc.input(Button::d1);
    calc.input(Button::d0);
    setValue(expectedState.x, 10);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::div);
    setValue(expectedState.x, 10);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 1, 1); // 0.1
    setValue(expectedState.y, 10);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 1, 2); // 0.01
    setValue(expectedState.y, 10);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 24/2===
TEST(TestDiv, Div2) {
    State expectedState(Config::DEFAULT_SIZE);
    Calculator calc(Config::DEFAULT_SIZE);

    calc.input(Button::d2);
    calc.input(Button::d4);
    setValue(expectedState.x, 24);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::div);
    setValue(expectedState.x, 24);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d2);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 24);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 12);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 6);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 3);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 27/3=12/2==
TEST(TestDiv, Div3) {
    State expectedState(Config::DEFAULT_SIZE);
    Calculator calc(Config::DEFAULT_SIZE);

    calc.input(Button::d2);
    calc.input(Button::d7);
    setValue(expectedState.x, 27);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::div);
    setValue(expectedState.x, 27);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d3);
    setValue(expectedState.x, 3);
    setValue(expectedState.y, 27);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 9);
    setValue(expectedState.y, 3);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d1);
    calc.input(Button::d2);
    setValue(expectedState.x, 12);
    setValue(expectedState.y, 3);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::div);
    setValue(expectedState.x, 12);
    setValue(expectedState.y, 3);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d2);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 12);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 6);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 3);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 120/5/3/2===
TEST(TestDiv, Div4) {
    State expectedState(Config::DEFAULT_SIZE);
    Calculator calc(Config::DEFAULT_SIZE);

    calc.input(Button::d1);
    calc.input(Button::d2);
    calc.input(Button::d0);
    setValue(expectedState.x, 120);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::div);
    setValue(expectedState.x, 120);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d5);
    setValue(expectedState.x, 5);
    setValue(expectedState.y, 120);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::div);
    setValue(expectedState.x, 24);
    setValue(expectedState.y, 5);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d3);
    setValue(expectedState.x, 3);
    setValue(expectedState.y, 24);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::div);
    setValue(expectedState.x, 8);
    setValue(expectedState.y, 3);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d2);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 8);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 4);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 1);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 12/2=8==
TEST(TestDiv, Div5) {
    State expectedState(Config::DEFAULT_SIZE);
    Calculator calc(Config::DEFAULT_SIZE);

    calc.input(Button::d1);
    calc.input(Button::d2);
    setValue(expectedState.x, 12);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::div);
    setValue(expectedState.x, 12);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d2);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 12);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 6);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d8);
    setValue(expectedState.x, 8);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 4);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 40/4=/==
TEST(TestDiv, Div6) {
    State expectedState(Config::DEFAULT_SIZE);
    Calculator calc(Config::DEFAULT_SIZE);

    calc.input(Button::d4);
    calc.input(Button::d0);
    setValue(expectedState.x, 40);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::div);
    setValue(expectedState.x, 40);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d4);
    setValue(expectedState.x, 4);
    setValue(expectedState.y, 40);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 10);
    setValue(expectedState.y, 4);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::div);
    setValue(expectedState.x, 10);
    setValue(expectedState.y, 4);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 1, 1); // 0.1
    setValue(expectedState.y, 10);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 1, 2); // 0.01
    setValue(expectedState.y, 10);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 40/4/==
TEST(TestDiv, Div7) {
    State expectedState(Config::DEFAULT_SIZE);
    Calculator calc(Config::DEFAULT_SIZE);

    calc.input(Button::d4);
    calc.input(Button::d0);
    setValue(expectedState.x, 40);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::div);
    setValue(expectedState.x, 40);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d4);
    setValue(expectedState.x, 4);
    setValue(expectedState.y, 40);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::div);
    setValue(expectedState.x, 10);
    setValue(expectedState.y, 4);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 1, 1);
    setValue(expectedState.y, 10);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 1, 2);
    setValue(expectedState.y, 10);
    expectedState.operation = Operation::div;
    ASSERT_EQ(expectedState, calc.getState());
}
