#include <gmock/gmock.h>

#include "calculator/calculator.h"
#include "calculator/state.h"
#include "calculator/button.h"
#include "calculator/operation.h"

using calculatorcomrade::Calculator;
using calculatorcomrade::State;
using calculatorcomrade::Button;
using calculatorcomrade::Operation;
using calculatorcomrade::Register;

#define TEST_CALCULATOR_INPUT(test_name) TEST(CalculatorInput, test_name)

TEST_CALCULATOR_INPUT(ClearEntry) {
    Calculator calc;
    State defaultState;
    State state = calc.getState();
    ASSERT_EQ(defaultState, state);
    calc.input(Button::d1);
    state = calc.getState();
    ASSERT_NE(defaultState, state);
    calc.input(Button::ce);
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
    expected.x.setDigit(0, 1);
    ASSERT_EQ(expected, c.getState());

    c.input(Button::d2);
    expected.x.setDigit(0, 2);
    expected.x.setDigit(1, 1);
    ASSERT_EQ(expected, c.getState());

    c.input(Button::d3);
    expected.x.setDigit(0, 3);
    expected.x.setDigit(1, 2);
    expected.x.setDigit(2, 1);
    ASSERT_EQ(expected, c.getState());

    c.input(Button::d4);
    expected.x.setDigit(0, 4);
    expected.x.setDigit(1, 3);
    expected.x.setDigit(2, 2);
    expected.x.setDigit(3, 1);
    ASSERT_EQ(expected, c.getState());

    c.input(Button::d5);
    expected.x.setDigit(0, 4);
    expected.x.setDigit(1, 3);
    expected.x.setDigit(2, 2);
    expected.x.setDigit(3, 1);
    ASSERT_EQ(expected, c.getState());
}


TEST_CALCULATOR_INPUT(NegativeInt) {
    Calculator c(4);
    State expected(4);

    c.input(Button::minus);
    expected.operation = Operation::sub;
    ASSERT_EQ(expected, c.getState());

    c.input(Button::d1);
    expected.x.setDigit(0, 1);
    ASSERT_EQ(expected, c.getState());

    c.input(Button::d2);
    expected.x.setDigit(0, 2);
    expected.x.setDigit(1, 1);
    ASSERT_EQ(expected, c.getState());

    c.input(Button::d3);
    expected.x.setDigit(0, 3);
    expected.x.setDigit(1, 2);
    expected.x.setDigit(2, 1);
    ASSERT_EQ(expected, c.getState());

    c.input(Button::d4);
    expected.x.setDigit(0, 4);
    expected.x.setDigit(1, 3);
    expected.x.setDigit(2, 2);
    expected.x.setDigit(3, 1);
    ASSERT_EQ(expected, c.getState());

    c.input(Button::d5);
    expected.x.setDigit(0, 4);
    expected.x.setDigit(1, 3);
    expected.x.setDigit(2, 2);
    expected.x.setDigit(3, 1);
    ASSERT_EQ(expected, c.getState());
}

TEST_CALCULATOR_INPUT(PositiveReal) {
    Calculator c(4);
    State expected(4);

    c.input(Button::d1);
    expected.x.setDigit(0, 1);
    expected.x.setPointPos(0);
    ASSERT_EQ(expected, c.getState());

    c.input(Button::point);
    expected.x.setPointPos(0);
    ASSERT_EQ(expected, c.getState());

    c.input(Button::d2);
    expected.x.setDigit(0, 2);
    expected.x.setDigit(1, 1);
    expected.x.setPointPos(1);
    ASSERT_EQ(expected, c.getState());

    c.input(Button::d3);
    expected.x.setDigit(0, 3);
    expected.x.setDigit(1, 2);
    expected.x.setDigit(2, 1);
    expected.x.setPointPos(2);
    ASSERT_EQ(expected, c.getState());

    c.input(Button::point); // should ignore this input
    ASSERT_EQ(expected, c.getState());

    c.input(Button::d4);
    expected.x.setDigit(0, 4);
    expected.x.setDigit(1, 3);
    expected.x.setDigit(2, 2);
    expected.x.setDigit(3, 1);
    expected.x.setPointPos(3);
    ASSERT_EQ(expected, c.getState());

    c.input(Button::d5);
    ASSERT_EQ(expected, c.getState());
}

TEST_CALCULATOR_INPUT(ZeroInHighDigit) {
    Calculator c(4);

    // ".1234" input should be "0.123" on display
    c.input(Button::point);
    c.input(Button::d1);
    c.input(Button::d2);
    c.input(Button::d3);
    c.input(Button::d4);

    Register &x = c.getState().x;
    ASSERT_EQ(0, x.getDigit(3));
    ASSERT_EQ(1, x.getDigit(2));
    ASSERT_EQ(2, x.getDigit(1));
    ASSERT_EQ(3, x.getDigit(0));
    ASSERT_EQ(3, x.getPointPos());
}
