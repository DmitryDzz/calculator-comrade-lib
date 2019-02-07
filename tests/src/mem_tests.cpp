//
// Created by dmitrydzz on 05.02.19.
//

#include <gmock/gmock.h>

#include "calculator/calculator.h"
#include "calc_helper.h"

using namespace calculatorcomrade;

#define TEST_MEM(test_name) TEST(TestMem, test_name)

TEST_MEM(Plus) {
    Calculator c;
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
    Calculator c;
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

//2 m+ => mem 2
//3 => mem 3
//mr => mem 2
//mc => 2
//mc => 2
TEST_MEM(MemClear) {
    Calculator c;
    State &s = c.getState();

    ASSERT_FALSE(s.memHasValue());
    c.input(Button::d2);
    c.input(Button::memPlus);
    ASSERT_EQ(2, getIntValue(s.x));
    ASSERT_EQ(2, getIntValue(s.m));
    ASSERT_TRUE(s.memHasValue());
    c.input(Button::d3);
    ASSERT_EQ(3, getIntValue(s.x));
    ASSERT_EQ(2, getIntValue(s.m));
    ASSERT_TRUE(s.memHasValue());
    c.input(Button::memR);
    ASSERT_EQ(2, getIntValue(s.x));
    ASSERT_EQ(2, getIntValue(s.m));
    ASSERT_TRUE(s.memHasValue());
    c.input(Button::memC);
    ASSERT_EQ(2, getIntValue(s.x));
    ASSERT_EQ(0, getIntValue(s.m));
    ASSERT_FALSE(s.memHasValue());
    c.input(Button::memC);
    ASSERT_EQ(2, getIntValue(s.x));
    ASSERT_EQ(0, getIntValue(s.m));
    ASSERT_FALSE(s.memHasValue());
}

// 2 m+ 3 m+ 5 m- => hasMemory == false
TEST_MEM(MemClearHack) {
    Calculator c;
    State &s = c.getState();

    ASSERT_FALSE(s.memHasValue());
    c.input(Button::d2);
    c.input(Button::memPlus);
    ASSERT_EQ(2, getIntValue(s.x));
    ASSERT_EQ(2, getIntValue(s.m));
    ASSERT_TRUE(s.memHasValue());
    c.input(Button::d3);
    c.input(Button::memPlus);
    ASSERT_EQ(3, getIntValue(s.x));
    ASSERT_EQ(5, getIntValue(s.m));
    ASSERT_TRUE(s.memHasValue());
    c.input(Button::d5);
    c.input(Button::memMinus);
    ASSERT_EQ(5, getIntValue(s.x));
    ASSERT_EQ(0, getIntValue(s.m));
    ASSERT_FALSE(s.memHasValue());
}

//2 m+ 3 mr = => 2
//= => 2
TEST_MEM(MemAndRegisterY) {
    Calculator c(8);
    State &s = c.getState();

    c.input(Button::d2);
    c.input(Button::memPlus);
    ASSERT_EQ(2, getIntValue(s.x));
    ASSERT_EQ(2, getIntValue(s.m));
    ASSERT_TRUE(s.memHasValue());
    c.input(Button::d3);
    c.input(Button::memR);
    ASSERT_EQ(2, getIntValue(s.x));
    ASSERT_EQ(2, getIntValue(s.m));
    ASSERT_TRUE(s.memHasValue());
    c.input(Button::equals);
    ASSERT_EQ(2, getIntValue(s.x));
    ASSERT_EQ(2, getIntValue(s.m));
    ASSERT_TRUE(s.memHasValue());
    c.input(Button::equals);
    ASSERT_EQ(2, getIntValue(s.x));
    ASSERT_EQ(2, getIntValue(s.m));
    ASSERT_TRUE(s.memHasValue());
}

//99999999 m+ 9 m+ => err mem 0
//mr, mc, 1 => err mem 0
//ce => mem 0
//mr => mem 99999999
TEST_MEM(MemOverflow) {
    Calculator c(8);
    State &s = c.getState();

    for (int8_t i = 0; i < 8; i++)
        c.input(Button::d9);
    c.input(Button::memPlus);
    ASSERT_EQ(99999999, getIntValue(s.x));
    ASSERT_EQ(99999999, getIntValue(s.m));
    ASSERT_TRUE(s.memHasValue());
    c.input(Button::d9);
    c.input(Button::memPlus);
    ASSERT_TRUE(s.x.isZero());
    ASSERT_TRUE(s.x.hasError());
    ASSERT_TRUE(s.memHasValue());
    c.input(Button::memR);
    c.input(Button::memC);
    c.input(Button::d1);
    ASSERT_TRUE(s.x.isZero());
    ASSERT_TRUE(s.x.hasError());
    ASSERT_TRUE(s.memHasValue());
    c.input(Button::ce);
    ASSERT_TRUE(s.x.isZero());
    ASSERT_FALSE(s.x.hasError());
    ASSERT_TRUE(s.memHasValue());
    c.input(Button::memR);
    ASSERT_EQ(99999999, getIntValue(s.x));
    ASSERT_EQ(99999999, getIntValue(s.m));
    ASSERT_FALSE(s.x.hasError());
    ASSERT_TRUE(s.memHasValue());
}

void TestMemTrunc(Calculator &c) {
    State &s = c.getState();

    for (int8_t i = 0; i < 8; i++)
        c.input(Button::d9);
    c.input(Button::memPlus);
    ASSERT_EQ(99999999, getIntValue(s.x));
    ASSERT_EQ(99999999, getIntValue(s.m));
    ASSERT_TRUE(s.memHasValue());
    c.input(Button::point);
    c.input(Button::d1);
    c.input(Button::memPlus);
    ASSERT_FALSE(s.x.hasError());

    uint8_t options = c.getOptions();
    if (options & Config::OPTION_CITIZEN_MEM_TRUNK) {
        ASSERT_TRUE(s.x.isZero());
    } else {
        ASSERT_EQ(1, getIntValue(s.x));
        ASSERT_EQ(1, s.x.getPointPos());
    }

    ASSERT_EQ(99999999, getIntValue(s.m));
    ASSERT_TRUE(s.memHasValue());
    c.input(Button::memR);
    ASSERT_FALSE(s.x.hasError());
    ASSERT_EQ(99999999, getIntValue(s.x));
    ASSERT_EQ(99999999, getIntValue(s.m));
    ASSERT_TRUE(s.memHasValue());
}

//99999999 m+ 0.1 m+ => mem 0.0000001
//mr => mem 99999999
TEST_MEM(MemTruncCommon) {
    Calculator c(8, 0);
    TestMemTrunc(c);
}

//99999999 m+ 0.1 m+ => mem 0
//mr => mem 99999999
TEST_MEM(MemTruncCitizen) {
    Calculator c(8, Config::OPTION_CITIZEN_MEM_TRUNK);
    TestMemTrunc(c);
}
