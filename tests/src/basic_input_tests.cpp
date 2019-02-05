#include <gmock/gmock.h>

#include "calculator/calculator.h"
#include "calculator/state.h"
#include "calculator/button.h"
#include "calculator/operation.h"
#include "calc_helper.h"

using namespace calculatorcomrade;

#define TEST_CALCULATOR_INPUT(test_name) TEST(CalculatorInput, test_name)

TEST_CALCULATOR_INPUT(ClearEntry1) {
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

TEST_CALCULATOR_INPUT(ClearEntry2) {
    Calculator calc;
    calc.input(Button::d1);
    calc.input(Button::plus);
    calc.input(Button::d2);
    calc.input(Button::ce);
    calc.input(Button::d3);
    calc.input(Button::equals);
    ASSERT_EQ(4, getAbsIntValue(calc.getState().x));
}

TEST_CALCULATOR_INPUT(ClearEntry3) {
    Calculator c;
    Register &x = c.getState().x;
    Register &y = c.getState().y;

    c.input(Button::d2);
    c.input(Button::plus);
    c.input(Button::equals);
    c.input(Button::equals);
    ASSERT_EQ(4, getIntValue(x));
    ASSERT_EQ(2, getIntValue(y));
    c.input(Button::ce);
    ASSERT_EQ(0, getIntValue(x));
    ASSERT_EQ(0, getIntValue(y));
}

TEST_CALCULATOR_INPUT(ClearEntryAfterOverflow) {
    Calculator c(8);
    for (int8_t i = 0; i < 8; i++)
        c.input(Button::d9);
    c.input(Button::mul);
    c.input(Button::d9);
    c.input(Button::equals);
    State &state = c.getState();
    ASSERT_EQ(89999999, getAbsIntValue(state.x)); // 8.9999999 in X
    ASSERT_EQ(7, state.x.getPointPos());
    ASSERT_EQ(99999999, getAbsIntValue(state.y)); // 99999999 in Y
    ASSERT_EQ(0, state.y.getPointPos());
    ASSERT_EQ(true, state.x.getOverflow());

    c.input(Button::ce);
    ASSERT_EQ(89999999, getAbsIntValue(state.x)); // 8.9999999 in X
    ASSERT_EQ(7, state.x.getPointPos());
    ASSERT_EQ(99999999, getAbsIntValue(state.y)); // 99999999 in Y
    ASSERT_EQ(0, state.y.getPointPos());
    ASSERT_EQ(false, state.x.getOverflow());

    c.input(Button::ce); // There's no input, so Button::ce works as Button::ca.
    ASSERT_EQ(0, getAbsIntValue(state.x)); // 0 in X
    ASSERT_EQ(0, state.x.getPointPos());
    ASSERT_EQ(0, getAbsIntValue(state.y)); // 0 in Y
    ASSERT_EQ(0, state.y.getPointPos());
    ASSERT_EQ(false, state.x.getOverflow());
}

TEST_CALCULATOR_INPUT(ClearAll) {
    Calculator c(8);
    Register &x = c.getState().x;
    Register &y = c.getState().y;


    c.input(Button::minus);
    for (int8_t i = 0; i < 8; i++)
        c.input(Button::d9);
    c.input(Button::mul);
    c.input(Button::d9);
    c.input(Button::equals);
    ASSERT_EQ(-89999999, getIntValue(x)); // 8.9999999 in X
    ASSERT_EQ(7, x.getPointPos());
    ASSERT_EQ(-99999999, getIntValue(y)); // 99999999 in Y
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(true, x.getNegative());
    ASSERT_EQ(true, x.getOverflow());

    c.input(Button::ca);
    ASSERT_EQ(0, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(0, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(false, x.getNegative());
    ASSERT_EQ(false, x.getOverflow());
}

TEST_CALCULATOR_INPUT(CeCa) {
    Calculator c(8);
    Register &x = c.getState().x;
    Register &y = c.getState().y;


    c.input(Button::minus);
    for (int8_t i = 0; i < 8; i++)
        c.input(Button::d9);
    c.input(Button::mul);
    c.input(Button::d9);
    c.input(Button::equals);
    ASSERT_EQ(-89999999, getIntValue(x)); // 8.9999999 in X
    ASSERT_EQ(7, x.getPointPos());
    ASSERT_EQ(-99999999, getIntValue(y)); // 99999999 in Y
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(true, x.getNegative());
    ASSERT_EQ(true, x.getOverflow());

    c.input(Button::ceca);
    ASSERT_EQ(-89999999, getIntValue(x)); // 8.9999999 in X
    ASSERT_EQ(7, x.getPointPos());
    ASSERT_EQ(-99999999, getIntValue(y)); // 99999999 in Y
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(true, x.getNegative());
    ASSERT_EQ(false, x.getOverflow());

    c.input(Button::ceca);
    ASSERT_EQ(0, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(0, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(false, x.getNegative());
    ASSERT_EQ(false, x.getOverflow());
}

TEST_CALCULATOR_INPUT(ZeroTyping) {
    Calculator c(4);
    State defaultState(4);
    for (int i = 0; i < 10; i++) {
        c.input(Button::d0);
        ASSERT_EQ(defaultState, c.getState());
    }
}

TEST_CALCULATOR_INPUT(ZeroTypingAfterPoint) {
    Calculator c(4);
    c.input(Button::point);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::d1);

    Register &x = c.getState().x;
    ASSERT_EQ(1, getIntValue(x));
    ASSERT_EQ(3, x.getPointPos());
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

TEST_CALCULATOR_INPUT(SerialSum) {
    Calculator c(2);
    State &state = c.getState();
    c.input(Button::d2);
    c.input(Button::plus);
    c.input(Button::d3);
    c.input(Button::equals);
    ASSERT_EQ(5, getAbsIntValue(state.x)); // 5 in X
    ASSERT_EQ(3, getAbsIntValue(state.y)); // 3 in Y
    c.input(Button::equals);
    ASSERT_EQ(8, getAbsIntValue(state.x)); // 8 in X
    ASSERT_EQ(3, getAbsIntValue(state.y)); // 3 in Y
    c.input(Button::equals);
    ASSERT_EQ(11, getAbsIntValue(state.x)); // 11 in X
    ASSERT_EQ(3, getAbsIntValue(state.y)); // 3 in Y
}

TEST_CALCULATOR_INPUT(SerialSub) {
    Calculator c(2);
    State &state = c.getState();
    c.input(Button::d8);
    c.input(Button::minus);
    c.input(Button::d2);
    c.input(Button::equals);
    ASSERT_EQ(6, getAbsIntValue(state.x)); // 6 in X
    ASSERT_EQ(2, getAbsIntValue(state.y)); // 2 in Y
    c.input(Button::equals);
    ASSERT_EQ(4, getAbsIntValue(state.x)); // 4 in X
    ASSERT_EQ(2, getAbsIntValue(state.y)); // 2 in Y
    c.input(Button::equals);
    ASSERT_EQ(2, getAbsIntValue(state.x)); // 2 in X
    ASSERT_EQ(2, getAbsIntValue(state.y)); // 2 in Y
}

TEST_CALCULATOR_INPUT(SerialMul) {
    Calculator c(2);
    State &state = c.getState();
    c.input(Button::d2);
    c.input(Button::mul);
    c.input(Button::d3);
    c.input(Button::equals);
    ASSERT_EQ(6, getAbsIntValue(state.x)); // 6 in X
    ASSERT_EQ(2, getAbsIntValue(state.y)); // 2 in Y
    c.input(Button::equals);
    ASSERT_EQ(12, getAbsIntValue(state.x)); // 12 in X
    ASSERT_EQ(2, getAbsIntValue(state.y)); // 2 in Y
    c.input(Button::equals);
    ASSERT_EQ(24, getAbsIntValue(state.x)); // 24 in X
    ASSERT_EQ(2, getAbsIntValue(state.y)); // 2 in Y
}

TEST_CALCULATOR_INPUT(SerialDiv) {
    Calculator c(4);
    State &state = c.getState();
    c.input(Button::d2);
    c.input(Button::div);
    c.input(Button::d1);
    c.input(Button::d0);
    c.input(Button::equals);               // 2 / 10 = ...
    ASSERT_EQ(2, getAbsIntValue(state.x)); // 0.2 in X
    ASSERT_EQ(1, state.x.getPointPos());
    ASSERT_EQ(10, getAbsIntValue(state.y)); // 2 in Y
    c.input(Button::equals);
    ASSERT_EQ(2, getAbsIntValue(state.x)); // 0.02 in X
    ASSERT_EQ(2, state.x.getPointPos());
    ASSERT_EQ(10, getAbsIntValue(state.y)); // 2 in Y
    c.input(Button::equals);
    ASSERT_EQ(2, getAbsIntValue(state.x)); // 0.002 in X
    ASSERT_EQ(3, state.x.getPointPos());
    ASSERT_EQ(10, getAbsIntValue(state.y)); // 2 in Y
}

TEST_CALCULATOR_INPUT(DoubleOperation) {
    Calculator c(4);
    Register &x = c.getState().x;
    c.input(Button::d8);
    c.input(Button::div);
    c.input(Button::div);
    ASSERT_EQ(8, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
}

TEST_CALCULATOR_INPUT(Sqrt) {
    Calculator c(8);
    Register &x = c.getState().x;

    c.input(Button::ca);
    c.input(Button::d9);
    c.input(Button::sqrt);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());

    c.input(Button::ca);
    c.input(Button::d2);
    c.input(Button::plus);
    c.input(Button::d9);
    c.input(Button::sqrt);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    c.input(Button::equals);
    ASSERT_EQ(5, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
}

TEST_CALCULATOR_INPUT(SqrtFakeNegative) {
    Calculator c(8);
    Register &x = c.getState().x;

    c.input(Button::minus);
    c.input(Button::d9);
    c.input(Button::sqrt);
    ASSERT_EQ(3, getIntValue(x));
    c.input(Button::equals);
    ASSERT_EQ(-3, getIntValue(x));
    c.input(Button::equals);
    ASSERT_EQ(-6, getIntValue(x));
}

TEST_CALCULATOR_INPUT(ChangeSign) {
    Calculator c(8);
    Register &x = c.getState().x;

    c.input(Button::ca);
    c.input(Button::d9);
    c.input(Button::plus);
    c.input(Button::d5);
    c.input(Button::changeSign);
    c.input(Button::equals);
    ASSERT_EQ(4, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
}
