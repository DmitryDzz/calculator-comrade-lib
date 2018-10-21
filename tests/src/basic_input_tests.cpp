#include <gmock/gmock.h>

#include "calculator/calculator.h"
#include "calculator/state.h"
#include "calculator/button.h"
#include "calculator/operation.h"

using calculatorcomrade::Calculator;
using calculatorcomrade::State;
using calculatorcomrade::Button;
using calculatorcomrade::Operation;

#define TEST_CALCULATOR_INPUT(test_name) TEST(CalculatorInput, test_name)

TEST_CALCULATOR_INPUT(ClearAll) {
    Calculator calc;
    State defaultState;
    State state = calc.getState();
    ASSERT_EQ(defaultState, state);
    calc.input(Button::d1);
    state = calc.getState();
    ASSERT_NE(defaultState, state);
    calc.input(Button::ca);
    state = calc.getState();
    ASSERT_EQ(defaultState, state);
}

TEST_CALCULATOR_INPUT(ZeroTyping) {
    Calculator c(4);
    State defaultState(4);
    for (int i = 0; i < 10; i++) {
        c.input(Button::d0);
        ASSERT_EQ(defaultState, c.getState());
    }
}

TEST_CALCULATOR_INPUT(PositiveInt) {
    Calculator c(4);
    State expected(4);

    c.input(Button::d1);
    expected.x[0] = 1;
    ASSERT_EQ(expected, c.getState());

    c.input(Button::d2);
    expected.x[0] = 2;
    expected.x[1] = 1;
    ASSERT_EQ(expected, c.getState());

    c.input(Button::d3);
    expected.x[0] = 3;
    expected.x[1] = 2;
    expected.x[2] = 1;
    ASSERT_EQ(expected, c.getState());

    c.input(Button::d4);
    expected.x[0] = 4;
    expected.x[1] = 3;
    expected.x[2] = 2;
    expected.x[3] = 1;
    ASSERT_EQ(expected, c.getState());

    c.input(Button::d5);
    expected.x[0] = 4;
    expected.x[1] = 3;
    expected.x[2] = 2;
    expected.x[3] = 1;
    ASSERT_EQ(expected, c.getState());
}


TEST_CALCULATOR_INPUT(NegativeInt) {
    Calculator c(4);
    State expected(4);

    c.input(Button::minus);
    expected.operation = Operation::sub;
    ASSERT_EQ(expected, c.getState());

    c.input(Button::d1);
    expected.x[0] = 1;
    ASSERT_EQ(expected, c.getState());

    c.input(Button::d2);
    expected.x[0] = 2;
    expected.x[1] = 1;
    ASSERT_EQ(expected, c.getState());

    c.input(Button::d3);
    expected.x[0] = 3;
    expected.x[1] = 2;
    expected.x[2] = 1;
    ASSERT_EQ(expected, c.getState());

    c.input(Button::d4);
    expected.x[0] = 4;
    expected.x[1] = 3;
    expected.x[2] = 2;
    expected.x[3] = 1;
    ASSERT_EQ(expected, c.getState());

    c.input(Button::d5);
    expected.x[0] = 4;
    expected.x[1] = 3;
    expected.x[2] = 2;
    expected.x[3] = 1;
    ASSERT_EQ(expected, c.getState());
}

TEST_CALCULATOR_INPUT(PositiveReal) {
    Calculator c(4);
    State expected(4);

    c.input(Button::d1);
    expected.x[0] = 1;
    ASSERT_EQ(expected, c.getState());

    c.input(Button::point);
    expected.x.pointPos = 0;
    ASSERT_EQ(expected, c.getState());

    c.input(Button::d2);
    expected.x[0] = 2;
    expected.x[1] = 1;
    expected.x.pointPos = 1;
    ASSERT_EQ(expected, c.getState());

    c.input(Button::d3);
    expected.x[0] = 3;
    expected.x[1] = 2;
    expected.x[2] = 1;
    expected.x.pointPos = 2;
    ASSERT_EQ(expected, c.getState());

    c.input(Button::d4);
    expected.x[0] = 4;
    expected.x[1] = 3;
    expected.x[2] = 2;
    expected.x[3] = 1;
    expected.x.pointPos = 3;
    ASSERT_EQ(expected, c.getState());

    c.input(Button::d5);
    expected.x[0] = 4;
    expected.x[1] = 3;
    expected.x[2] = 2;
    expected.x[3] = 1;
    ASSERT_EQ(expected, c.getState());
}
