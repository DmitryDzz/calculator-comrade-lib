//
// Created by dmitrydzz on 07.01.19.
//

#include <gmock/gmock.h>

#include "calculator/state.h"
#include "calculator/register.h"
#include "calc_helper.h"

using calculatorcomrade::State;
using calculatorcomrade::Register;

TEST(TestState, ExchangeXY) {
    State state(8);
    setValue(state.x, -1234567890);
    setValue(state.y, 1974);
    state.exchangeXY();

    ASSERT_EQ(1974, getAbsIntValue(state.x));
    ASSERT_EQ(0, state.x.getPointPos());
    ASSERT_EQ(false, state.x.getNegative());
    ASSERT_EQ(false, state.x.getOverflow());

    ASSERT_EQ(12345678, getAbsIntValue(state.y));
    ASSERT_EQ(6, state.y.getPointPos());
    ASSERT_EQ(true, state.y.getNegative());
    ASSERT_EQ(true, state.y.getOverflow());
}
