//
// Created by dmitrydzz on 05.02.19.
//

#include <gmock/gmock.h>

#include "calculator/calculator.h"
#include "calc_helper.h"

using namespace calculatorcomrade;

#define TEST_MEM(test_name) TEST(TestMem, test_name)

TEST_MEM(Plus) {
    Calculator c(8);
    Register &x = c.getState().x;
    Register &m = c.getState().m;

    c.input(Button::d2);
    c.input(Button::memPlus);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(2, getIntValue(m));
    c.input(Button::d3);
    c.input(Button::memPlus);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(5, getIntValue(m));
}

TEST_MEM(PlusInput) {
    Calculator c(8);
    Register &x = c.getState().x;
    Register &m = c.getState().m;

    c.input(Button::d2);
    c.input(Button::memPlus);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(2, getIntValue(m));
    c.input(Button::d3);
    c.input(Button::memPlus);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(5, getIntValue(m));
}
