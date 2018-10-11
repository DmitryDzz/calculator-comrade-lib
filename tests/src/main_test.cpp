#include <gmock/gmock.h>

#include <calculator/main.h>
#include <calculator/calculator.h>
#include "calculator/state.h"
#include "calculator/button.h"

using calculatorcomrade::Calculator;
using calculatorcomrade::State;
using calculatorcomrade::Button;

TEST(CalculatorInput, CheckClearAll) {
    Calculator calc;
    State defaultState;
    State state = calc.getState();
    EXPECT_EQ(defaultState, state);
    calc.input(Button::d1);
    EXPECT_NE(defaultState, calc.getState());
    calc.input(Button::ca);
    state = calc.getState();
    EXPECT_EQ(defaultState, state);
}
