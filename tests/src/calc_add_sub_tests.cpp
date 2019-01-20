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

// Input: 2==
TEST(TestAddSub, NoOperations) {
    State expectedState(Config::DEFAULT_SIZE);
    Calculator calc(Config::DEFAULT_SIZE);

    calc.input(Button::d2);
    setValue(expectedState.x, 2);
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 2+==
TEST(TestAddSub, IncCounter) {
    State expectedState(Config::DEFAULT_SIZE);
    Calculator calc(Config::DEFAULT_SIZE);

    calc.input(Button::d2);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::plus);
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 4);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 2-==
TEST(TestAddSub, DecCounter) {
    State expectedState(Config::DEFAULT_SIZE);
    Calculator calc(Config::DEFAULT_SIZE);

    calc.input(Button::d2);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::minus);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, -2);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, -4);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 8-1===
TEST(TestAddSub, Subtraction) {
    State expectedState(Config::DEFAULT_SIZE);
    Calculator calc(Config::DEFAULT_SIZE);

    calc.input(Button::d8);
    setValue(expectedState.x, 8);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::minus);
    setValue(expectedState.x, 8);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d1);
    setValue(expectedState.x, 1);
    setValue(expectedState.y, 8);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 7);
    setValue(expectedState.y, 1);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 6);
    setValue(expectedState.y, 1);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 5);
    setValue(expectedState.y, 1);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: -3+2===
TEST(TestAddSub, InvertedSubtraction) {
    State expectedState(Config::DEFAULT_SIZE);
    Calculator calc(Config::DEFAULT_SIZE);

    calc.input(Button::minus);
    setValue(expectedState.x, 0);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d3);
    setValue(expectedState.x, 3);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::plus);
    setValue(expectedState.x, -3);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d2);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, -3);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, -1);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 1);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 3);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 2+3=8-1==
TEST(TestAddSub, TwoSeparateCalculationsInARow) {
    State expectedState(Config::DEFAULT_SIZE);
    Calculator calc(Config::DEFAULT_SIZE);

    calc.input(Button::d2);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::plus);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d3);
    setValue(expectedState.x, 3);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 5);
    setValue(expectedState.y, 3);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d8);
    setValue(expectedState.x, 8);
    setValue(expectedState.y, 3);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::minus);
    setValue(expectedState.x, 8);
    setValue(expectedState.y, 3);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d1);
    setValue(expectedState.x, 1);
    setValue(expectedState.y, 8);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 7);
    setValue(expectedState.y, 1);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 6);
    setValue(expectedState.y, 1);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 2+7-3+1==
TEST(TestAddSub, FourCalculationsInARow) {
    State expectedState(Config::DEFAULT_SIZE);
    Calculator calc(Config::DEFAULT_SIZE);

    calc.input(Button::d2);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::plus);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d7);
    setValue(expectedState.x, 7);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::minus);
    setValue(expectedState.x, 9);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d3);
    setValue(expectedState.x, 3);
    setValue(expectedState.y, 9);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::plus);
    setValue(expectedState.x, 6);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d1);
    setValue(expectedState.x, 1);
    setValue(expectedState.y, 6);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 7);
    setValue(expectedState.y, 1);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 8);
    setValue(expectedState.y, 1);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 9-2=3==
TEST(TestAddSub, ExtraTest1) {
    State expectedState(Config::DEFAULT_SIZE);
    Calculator calc(Config::DEFAULT_SIZE);

    calc.input(Button::d9);
    setValue(expectedState.x, 9);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::minus);
    setValue(expectedState.x, 9);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d2);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 9);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 7);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d3);
    setValue(expectedState.x, 3);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 1);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, -1);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 8-1=-===
TEST(TestAddSub, ExtraTest2) {
    State expectedState(Config::DEFAULT_SIZE);
    Calculator calc(Config::DEFAULT_SIZE);

    calc.input(Button::d8);
    setValue(expectedState.x, 8);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::minus);
    setValue(expectedState.x, 8);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d1);
    setValue(expectedState.x, 1);
    setValue(expectedState.y, 8);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, 7);
    setValue(expectedState.y, 1);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::minus);
    setValue(expectedState.x, 7);
    setValue(expectedState.y, 1);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, -6);
    setValue(expectedState.y, 7);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, -13);
    setValue(expectedState.y, 7);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, -20);
    setValue(expectedState.y, 7);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());
}

// Input: 2+7-===
TEST(TestAddSub, ExtraTest3) {
    State expectedState(Config::DEFAULT_SIZE);
    Calculator calc(Config::DEFAULT_SIZE);

    calc.input(Button::d2);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::plus);
    setValue(expectedState.x, 2);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::d7);
    setValue(expectedState.x, 7);
    setValue(expectedState.y, 2);
    expectedState.operation = Operation::add;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::minus);
    setValue(expectedState.x, 9);
    setValue(expectedState.y, 0);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, -9);
    setValue(expectedState.y, 9);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, -18);
    setValue(expectedState.y, 9);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());

    calc.input(Button::equals);
    setValue(expectedState.x, -27);
    setValue(expectedState.y, 9);
    expectedState.operation = Operation::sub;
    ASSERT_EQ(expectedState, calc.getState());
}
