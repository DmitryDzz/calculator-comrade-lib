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
    Register &x = c.getX();
    Register &m = c.getM();

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
//TODO DZZ Check it on hardware.
TEST_MEM(MemClear) {
    Calculator c;
    Register &x = c.getX();
    Register &m = c.getM();

    ASSERT_FALSE(c.memHasValue());
    c.input(Button::d2);
    c.input(Button::memPlus);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(2, getIntValue(m));
    ASSERT_TRUE(c.memHasValue());
    c.input(Button::d3);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(2, getIntValue(m));
    ASSERT_TRUE(c.memHasValue());
    c.input(Button::memR);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(2, getIntValue(m));
    ASSERT_TRUE(c.memHasValue());
    c.input(Button::memC);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(0, getIntValue(m));
    ASSERT_FALSE(c.memHasValue());
    c.input(Button::memC);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(0, getIntValue(m));
    ASSERT_FALSE(c.memHasValue());
}

//2 m+ => mem 2
//3 => mem 3
//mrc => mem 2
//mrc => 2
//mrc => 2
TEST_MEM(MemRC) {
    Calculator c;
    Register &x = c.getX();
    Register &m = c.getM();

    ASSERT_FALSE(c.memHasValue());
    c.input(Button::d2);
    c.input(Button::memPlus);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(2, getIntValue(m));
    ASSERT_TRUE(c.memHasValue());
    c.input(Button::d3);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(2, getIntValue(m));
    ASSERT_TRUE(c.memHasValue());
    c.input(Button::memRC);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(2, getIntValue(m));
    ASSERT_TRUE(c.memHasValue());
    c.input(Button::memRC);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(0, getIntValue(m));
    ASSERT_FALSE(c.memHasValue());
    c.input(Button::memRC);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(0, getIntValue(m));
    ASSERT_FALSE(c.memHasValue());
}

// 2 m+ 3 m+ 5 m- => hasMemory == false
TEST_MEM(MemClearHack) {
    Calculator c;
    Register &x = c.getX();
    Register &m = c.getM();

    ASSERT_FALSE(c.memHasValue());
    c.input(Button::d2);
    c.input(Button::memPlus);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(2, getIntValue(m));
    ASSERT_TRUE(c.memHasValue());
    c.input(Button::d3);
    c.input(Button::memPlus);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(5, getIntValue(m));
    ASSERT_TRUE(c.memHasValue());
    c.input(Button::d5);
    c.input(Button::memMinus);
    ASSERT_EQ(5, getIntValue(x));
    ASSERT_EQ(0, getIntValue(m));
    ASSERT_FALSE(c.memHasValue());
}

//2 m+ 3 mr = => 2
//= => 2
TEST_MEM(MemAndRegisterY) {
    Calculator c(8);
    Register &x = c.getX();
    Register &m = c.getM();

    c.input(Button::d2);
    c.input(Button::memPlus);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(2, getIntValue(m));
    ASSERT_TRUE(c.memHasValue());
    c.input(Button::d3);
    c.input(Button::memR);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(2, getIntValue(m));
    ASSERT_TRUE(c.memHasValue());
    c.input(Button::equals);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(2, getIntValue(m));
    ASSERT_TRUE(c.memHasValue());
    c.input(Button::equals);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(2, getIntValue(m));
    ASSERT_TRUE(c.memHasValue());
}

TEST_MEM(MemPlusSpecial1) {
    Calculator c;
    Register &x = c.getX();
    Register &y = c.getY();
    Register &m = c.getM();

    c.input(Button::d2);
    c.input(Button::plus);
    c.input(Button::d3);
    c.input(Button::memPlus);
    ASSERT_EQ(5, getIntValue(x));
    ASSERT_EQ(0, getIntValue(y));
    ASSERT_EQ(Operation::add, c.getOperation());
    ASSERT_EQ(5, getIntValue(m));
    c.input(Button::equals);
    ASSERT_EQ(5, getIntValue(x));
    ASSERT_EQ(0, getIntValue(y));
    ASSERT_EQ(Operation::add, c.getOperation());
    ASSERT_EQ(5, getIntValue(m));
}

TEST_MEM(MemPlusSpecial2) {
    Calculator c;
    Register &x = c.getX();
    Register &y = c.getY();
    Register &m = c.getM();

    c.input(Button::d2);
    c.input(Button::mul);
    c.input(Button::d3);
    c.input(Button::memPlus);
    ASSERT_EQ(6, getIntValue(x));
    ASSERT_EQ(0, getIntValue(y));
    ASSERT_EQ(Operation::add, c.getOperation());
    ASSERT_EQ(6, getIntValue(m));
    c.input(Button::equals);
    ASSERT_EQ(6, getIntValue(x));
    ASSERT_EQ(0, getIntValue(y));
    ASSERT_EQ(Operation::add, c.getOperation());
    ASSERT_EQ(6, getIntValue(m));
}

TEST_MEM(MemPlusSpecial3) {
    Calculator c;
    Register &x = c.getX();
    Register &y = c.getY();
    Register &m = c.getM();

    c.input(Button::d2);
    c.input(Button::plus);
    c.input(Button::memPlus);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(0, getIntValue(y));
    ASSERT_EQ(Operation::add, c.getOperation());
    ASSERT_EQ(2, getIntValue(m));
    c.input(Button::equals);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(0, getIntValue(y));
    ASSERT_EQ(Operation::add, c.getOperation());
    ASSERT_EQ(2, getIntValue(m));
}

TEST_MEM(MemPlusSpecial4) {
    Calculator c;
    Register &x = c.getX();
    Register &y = c.getY();
    Register &m = c.getM();

    c.input(Button::d3);
    c.input(Button::mul);
    c.input(Button::memPlus);
    ASSERT_EQ(9, getIntValue(x));
    ASSERT_EQ(0, getIntValue(y));
    ASSERT_EQ(Operation::add, c.getOperation());
    ASSERT_EQ(9, getIntValue(m));
    c.input(Button::equals);
    ASSERT_EQ(9, getIntValue(x));
    ASSERT_EQ(0, getIntValue(y));
    ASSERT_EQ(Operation::add, c.getOperation());
    ASSERT_EQ(9, getIntValue(m));
}

TEST_MEM(MemPlusSpecial5) {
    Calculator c;
    Register &x = c.getX();
    Register &y = c.getY();
    Register &m = c.getM();

    c.input(Button::d2);
    c.input(Button::plus);
    c.input(Button::d3);
    c.input(Button::equals);
    ASSERT_EQ(5, getIntValue(x));
    ASSERT_EQ(3, getIntValue(y));
    ASSERT_EQ(Operation::add, c.getOperation());
    ASSERT_EQ(0, getIntValue(m));
    c.input(Button::memPlus);
    ASSERT_EQ(5, getIntValue(x));
    ASSERT_EQ(3, getIntValue(y));
    ASSERT_EQ(Operation::add, c.getOperation());
    ASSERT_EQ(5, getIntValue(m));
    c.input(Button::equals);
    ASSERT_EQ(8, getIntValue(x));
    ASSERT_EQ(3, getIntValue(y));
    ASSERT_EQ(Operation::add, c.getOperation());
    ASSERT_EQ(5, getIntValue(m));
}

TEST_MEM(MemPlusSpecial6) {
    Calculator c;
    Register &x = c.getX();
    Register &y = c.getY();
    Register &m = c.getM();

    c.input(Button::d2);
    c.input(Button::mul);
    c.input(Button::d3);
    c.input(Button::equals);
    ASSERT_EQ(6, getIntValue(x));
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(Operation::mul, c.getOperation());
    ASSERT_EQ(0, getIntValue(m));
    c.input(Button::memPlus);
    ASSERT_EQ(6, getIntValue(x));
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(Operation::mul, c.getOperation());
    ASSERT_EQ(6, getIntValue(m));
    c.input(Button::equals);
    ASSERT_EQ(12, getIntValue(x));
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(Operation::mul, c.getOperation());
    ASSERT_EQ(6, getIntValue(m));
}

TEST_MEM(MemMinusSpecial1) {
    Calculator c;
    Register &x = c.getX();
    Register &y = c.getY();
    Register &m = c.getM();

    c.input(Button::d2);
    c.input(Button::plus);
    c.input(Button::d3);
    c.input(Button::memMinus);
    ASSERT_EQ(5, getIntValue(x));
    ASSERT_EQ(0, getIntValue(y));
    ASSERT_EQ(Operation::add, c.getOperation());
    ASSERT_EQ(-5, getIntValue(m));
    c.input(Button::equals);
    ASSERT_EQ(5, getIntValue(x));
    ASSERT_EQ(0, getIntValue(y));
    ASSERT_EQ(Operation::add, c.getOperation());
    ASSERT_EQ(-5, getIntValue(m));
}

TEST_MEM(MemMinusSpecial2) {
    Calculator c;
    Register &x = c.getX();
    Register &y = c.getY();
    Register &m = c.getM();

    c.input(Button::d2);
    c.input(Button::mul);
    c.input(Button::d3);
    c.input(Button::memMinus);
    ASSERT_EQ(6, getIntValue(x));
    ASSERT_EQ(0, getIntValue(y));
    ASSERT_EQ(Operation::add, c.getOperation());
    ASSERT_EQ(-6, getIntValue(m));
    c.input(Button::equals);
    ASSERT_EQ(6, getIntValue(x));
    ASSERT_EQ(0, getIntValue(y));
    ASSERT_EQ(Operation::add, c.getOperation());
    ASSERT_EQ(-6, getIntValue(m));
}

TEST_MEM(MemMinusSpecial3) {
    Calculator c;
    Register &x = c.getX();
    Register &y = c.getY();
    Register &m = c.getM();

    c.input(Button::d2);
    c.input(Button::plus);
    c.input(Button::memMinus);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(0, getIntValue(y));
    ASSERT_EQ(Operation::add, c.getOperation());
    ASSERT_EQ(-2, getIntValue(m));
    c.input(Button::equals);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(0, getIntValue(y));
    ASSERT_EQ(Operation::add, c.getOperation());
    ASSERT_EQ(-2, getIntValue(m));
}

TEST_MEM(MemMinusSpecial4) {
    Calculator c;
    Register &x = c.getX();
    Register &y = c.getY();
    Register &m = c.getM();

    c.input(Button::d3);
    c.input(Button::mul);
    c.input(Button::memMinus);
    ASSERT_EQ(9, getIntValue(x));
    ASSERT_EQ(0, getIntValue(y));
    ASSERT_EQ(Operation::add, c.getOperation());
    ASSERT_EQ(-9, getIntValue(m));
    c.input(Button::equals);
    ASSERT_EQ(9, getIntValue(x));
    ASSERT_EQ(0, getIntValue(y));
    ASSERT_EQ(Operation::add, c.getOperation());
    ASSERT_EQ(-9, getIntValue(m));
}

TEST_MEM(MemMinusSpecial5) {
    Calculator c;
    Register &x = c.getX();
    Register &y = c.getY();
    Register &m = c.getM();

    c.input(Button::d2);
    c.input(Button::plus);
    c.input(Button::d3);
    c.input(Button::equals);
    ASSERT_EQ(5, getIntValue(x));
    ASSERT_EQ(3, getIntValue(y));
    ASSERT_EQ(Operation::add, c.getOperation());
    ASSERT_EQ(0, getIntValue(m));
    c.input(Button::memMinus);
    ASSERT_EQ(5, getIntValue(x));
    ASSERT_EQ(3, getIntValue(y));
    ASSERT_EQ(Operation::add, c.getOperation());
    ASSERT_EQ(-5, getIntValue(m));
    c.input(Button::equals);
    ASSERT_EQ(8, getIntValue(x));
    ASSERT_EQ(3, getIntValue(y));
    ASSERT_EQ(Operation::add, c.getOperation());
    ASSERT_EQ(-5, getIntValue(m));
}

TEST_MEM(MemMinusSpecial6) {
    Calculator c;
    Register &x = c.getX();
    Register &y = c.getY();
    Register &m = c.getM();

    c.input(Button::d2);
    c.input(Button::mul);
    c.input(Button::d3);
    c.input(Button::equals);
    ASSERT_EQ(6, getIntValue(x));
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(Operation::mul, c.getOperation());
    ASSERT_EQ(0, getIntValue(m));
    c.input(Button::memMinus);
    ASSERT_EQ(6, getIntValue(x));
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(Operation::mul, c.getOperation());
    ASSERT_EQ(-6, getIntValue(m));
    c.input(Button::equals);
    ASSERT_EQ(12, getIntValue(x));
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(Operation::mul, c.getOperation());
    ASSERT_EQ(-6, getIntValue(m));
}

//99 * 99999999 m+ => err 98.999999
TEST_MEM(NoMemOnOverflow) {
    Calculator c(8);
    Register &x = c.getX();
    Register &y = c.getY();

    ASSERT_FALSE(c.memHasValue());
    c.input(Button::d9);
    c.input(Button::d9);
    c.input(Button::mul);
    for (int8_t i = 0; i < 8; i++)
        c.input(Button::d9);
    c.input(Button::memPlus);
    ASSERT_EQ(98999999, getIntValue(x));
    ASSERT_EQ(6, x.getPointPos());
    ASSERT_TRUE(x.hasError());
    ASSERT_TRUE(y.isZero());
    ASSERT_FALSE(c.memHasValue());
    c.input(Button::ce);
    c.input(Button::equals);
    ASSERT_EQ(98999999, getIntValue(x));
    ASSERT_EQ(6, x.getPointPos());
    ASSERT_FALSE(x.hasError());
    ASSERT_TRUE(y.isZero());
    ASSERT_FALSE(c.memHasValue());
}

//99999999 m+ 9 m+ => err mem 0
//mr, mc, 1 => err mem 0
//ce => mem 0
//mr => mem 99999999
TEST_MEM(MemOverflow) {
    Calculator c(8);
    Register &x = c.getX();
    Register &y = c.getY();
    Register &m = c.getM();

    for (int8_t i = 0; i < 8; i++)
        c.input(Button::d9);
    c.input(Button::memPlus);
    ASSERT_EQ(99999999, getIntValue(x));
    ASSERT_EQ(99999999, getIntValue(m));
    ASSERT_TRUE(c.memHasValue());
    c.input(Button::d9);
    c.input(Button::memPlus);
    ASSERT_TRUE(x.isZero());
    ASSERT_TRUE(x.hasError());
    ASSERT_TRUE(c.memHasValue());
    c.input(Button::memR);
    c.input(Button::memC);
    c.input(Button::d1);
    ASSERT_TRUE(x.isZero());
    ASSERT_TRUE(x.hasError());
    ASSERT_TRUE(c.memHasValue());
    c.input(Button::ce);
    ASSERT_TRUE(x.isZero());
    ASSERT_TRUE(x.hasError()); // ce doesn't clear the error
    ASSERT_TRUE(c.memHasValue());
    c.input(Button::ceca);
    ASSERT_TRUE(x.isZero());
    ASSERT_FALSE(x.hasError()); // ceca and ca clear the error
    ASSERT_TRUE(c.memHasValue());
    c.input(Button::memR);
    ASSERT_EQ(99999999, getIntValue(x));
    ASSERT_EQ(99999999, getIntValue(m));
    ASSERT_FALSE(x.hasError());
    ASSERT_TRUE(c.memHasValue());
}

void TestMemTruncatesX(Calculator &c) {
    Register &x = c.getX();
    Register &m = c.getM();

    c.input(Button::memC);
    c.input(Button::ca);
    for (int8_t i = 0; i < 8; i++)
        c.input(Button::d9);
    c.input(Button::memPlus);
    ASSERT_EQ(99999999, getIntValue(x));
    ASSERT_EQ(99999999, getIntValue(m));
    ASSERT_TRUE(c.memHasValue());
    c.input(Button::point);
    c.input(Button::d1);
    c.input(Button::memPlus);
    ASSERT_FALSE(x.hasError());

    uint8_t options = c.getOptions();
    if (options & Config::OPTION_MEM_CAN_TRUNC_X) {
        ASSERT_TRUE(x.isZero());
    } else {
        ASSERT_EQ(1, getIntValue(x));
        ASSERT_EQ(1, x.getPointPos());
    }

    ASSERT_EQ(99999999, getIntValue(m));
    ASSERT_TRUE(c.memHasValue());
    c.input(Button::memR);
    ASSERT_FALSE(x.hasError());
    ASSERT_EQ(99999999, getIntValue(x));
    ASSERT_EQ(99999999, getIntValue(m));
    ASSERT_TRUE(c.memHasValue());
}

//  I found two types of acting for different calculators in this test:
//  Citizen calculators (I'm not sure that all of them) act this way:
//      99999999 m+ 0.1 m+ => mem 0
//      mr => mem 99999999
//  While other calculators I've tested act in the other way:
//      99999999 m+ 0.1 m+ => mem 0.0000001
//      mr => mem 99999999
TEST_MEM(MemTruncsX) {
    Calculator c(8);
    uint8_t options = c.getOptions();

    options |= Config::OPTION_MEM_CAN_TRUNC_X;
    c.setOptions(options);
    TestMemTruncatesX(c);

    options &= ~Config::OPTION_MEM_CAN_TRUNC_X;
    c.setOptions(options);
    TestMemTruncatesX(c);
}

TEST_MEM(DivMemRestore) {
    Calculator c(8);
    Register &x = c.getX();
    Register &y = c.getY();
    Register &m = c.getM();

    c.input(Button::d2);
    c.input(Button::memPlus);
    c.input(Button::d8);
    c.input(Button::div);
    ASSERT_EQ(8, getIntValue(x));
    ASSERT_EQ(0, getIntValue(y));
    ASSERT_EQ(2, getIntValue(m));
    c.input(Button::memR);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(8, getIntValue(y));
    ASSERT_EQ(2, getIntValue(m));
    c.input(Button::equals);
    ASSERT_EQ(4, getIntValue(x));
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(2, getIntValue(m));
    c.input(Button::equals);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(2, getIntValue(y));
    ASSERT_EQ(2, getIntValue(m));
}

TEST_MEM(MulMemRestore) {
    Calculator c(8);
    Register &x = c.getX();
    Register &y = c.getY();
    Register &m = c.getM();

    c.input(Button::d2);
    c.input(Button::memPlus);
    c.input(Button::d3);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, getIntValue(y));
    ASSERT_EQ(2, getIntValue(m));
    c.input(Button::mul);
    c.input(Button::memR);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(3, getIntValue(y));
    ASSERT_EQ(2, getIntValue(m));
    c.input(Button::equals);
    ASSERT_EQ(6, getIntValue(x));
    ASSERT_EQ(3, getIntValue(y));
    ASSERT_EQ(2, getIntValue(m));
    c.input(Button::equals);
    ASSERT_EQ(18, getIntValue(x));
    ASSERT_EQ(3, getIntValue(y));
    ASSERT_EQ(2, getIntValue(m));
}
