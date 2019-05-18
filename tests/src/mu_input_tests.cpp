//
// Created by dmitrydzz on 16.02.2019.
//

#include <gmock/gmock.h>

#include "calculator/calculator.h"
#include "calculator/config.h"
#include "calc_helper.h"

using namespace calculatorcomrade;

#define TEST_MU(test_name) TEST(TestMu, test_name)

TEST_MU(MuRegularOperations) {
    Calculator c(8);
    Register &x = c.getX();
    Register &y = c.getY();

    // 200 mu 60 % => 500
    // % => 500
    c.input(Button::ca);
    c.input(Button::d2);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::mu);
    c.input(Button::d6);
    c.input(Button::d0);
    c.input(Button::percent);
    ASSERT_EQ(500, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(6, getIntValue(y));
    ASSERT_EQ(1, y.getPointPos());
    ASSERT_EQ(Operation::mu, c.getOperation());
    c.input(Button::percent);
    ASSERT_EQ(500, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(6, getIntValue(y));
    ASSERT_EQ(1, y.getPointPos());
    ASSERT_EQ(Operation::mu, c.getOperation());

    // 200 mu 60 = => 60
    // = => 60
    c.input(Button::ca);
    c.input(Button::d2);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::mu);
    c.input(Button::d6);
    c.input(Button::d0);
    c.input(Button::equals);
    ASSERT_EQ(60, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    ASSERT_EQ(Operation::add, c.getOperation());
    c.input(Button::equals);
    ASSERT_EQ(60, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    ASSERT_EQ(Operation::add, c.getOperation());
}

TEST_MU(MuArithmeticOperationAfterMuPercent) {
    Calculator c(8, Config::OPTION_TRUNC_ZEROS_ON_OVERFLOW);
    Register &x = c.getX();
    Register &y = c.getY();

    // 200 mu 60 % => 500
    // + => 500
    // = => 500.6
    // = => 1000.6
    c.input(Button::ca);
    c.input(Button::d2);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::mu);
    c.input(Button::d6);
    c.input(Button::d0);
    c.input(Button::percent);
    ASSERT_EQ(500, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(6, getIntValue(y));
    ASSERT_EQ(1, y.getPointPos());
    ASSERT_EQ(Operation::mu, c.getOperation());
    c.input(Button::plus);
    c.input(Button::equals);
    ASSERT_EQ(5006, getIntValue(x));
    ASSERT_EQ(1, x.getPointPos());
    ASSERT_EQ(500, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::add, c.getOperation());
    c.input(Button::equals);
    ASSERT_EQ(10006, getIntValue(x));
    ASSERT_EQ(1, x.getPointPos());

    // 200 mu 60 % => 500
    // * => 500
    // = => 250000
    // = => [err] 1.25
    c.input(Button::ca);
    c.input(Button::d2);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::mu);
    c.input(Button::d6);
    c.input(Button::d0);
    c.input(Button::percent);
    ASSERT_EQ(500, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(6, getIntValue(y));
    ASSERT_EQ(1, y.getPointPos());
    ASSERT_EQ(Operation::mu, c.getOperation());
    c.input(Button::mul);
    c.input(Button::equals);
    ASSERT_EQ(250000, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(500, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::mul, c.getOperation());
    c.input(Button::equals);
    ASSERT_EQ(125, getIntValue(x));
    ASSERT_EQ(2, x.getPointPos());
    ASSERT_TRUE(x.hasError());
    ASSERT_TRUE(x.hasOverflow());

    // 200 mu 60 % => 500
    // / => 500
    // = => 0.002
    // = => 0.000004
    c.input(Button::ca);
    c.input(Button::d2);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::mu);
    c.input(Button::d6);
    c.input(Button::d0);
    c.input(Button::percent);
    ASSERT_EQ(500, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(6, getIntValue(y));
    ASSERT_EQ(1, y.getPointPos());
    ASSERT_EQ(Operation::mu, c.getOperation());
    c.input(Button::div);
    c.input(Button::equals);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(3, x.getPointPos());
    ASSERT_EQ(500, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::div, c.getOperation());
    c.input(Button::equals);
    ASSERT_EQ(4, getIntValue(x));
    ASSERT_EQ(6, x.getPointPos());
}

TEST_MU(MuArithmeticOperationBeforePercent) {
    Calculator c(8);
    Register &x = c.getX();
    Register &y = c.getY();

    // 200 mu 60 + => 60
    // % => 320
    // = => 520
    c.input(Button::ca);
    c.input(Button::d2);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::mu);
    c.input(Button::d6);
    c.input(Button::d0);
    c.input(Button::plus);
    ASSERT_EQ(60, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(200, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::add, c.getOperation());
    c.input(Button::percent);
    ASSERT_EQ(320, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(200, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::add, c.getOperation());
    c.input(Button::equals);
    ASSERT_EQ(520, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(200, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::add, c.getOperation());

    // 200 mu 60 - => 60
    // % => 80
    // = => -120
    c.input(Button::ca);
    c.input(Button::d2);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::mu);
    c.input(Button::d6);
    c.input(Button::d0);
    c.input(Button::minus);
    ASSERT_EQ(60, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(200, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::sub, c.getOperation());
    c.input(Button::percent);
    ASSERT_EQ(80, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(200, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::sub, c.getOperation());
    c.input(Button::equals);
    ASSERT_EQ(-120, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(200, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    ASSERT_EQ(Operation::sub, c.getOperation());
}

TEST_MU(MuAfterMul) {
    Calculator c(8);
    Register &x = c.getX();
    Register &y = c.getY();

    // 200 * 60 mu => 60
    // % => 60
    // % => 60
    c.input(Button::ca);
    c.input(Button::d2);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::mul);
    c.input(Button::d6);
    c.input(Button::d0);
    c.input(Button::mu);
    ASSERT_EQ(60, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    ASSERT_EQ(Operation::add, c.getOperation());
    c.input(Button::percent);
    ASSERT_EQ(60, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    ASSERT_EQ(Operation::add, c.getOperation());
    c.input(Button::percent);
    ASSERT_EQ(60, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    ASSERT_EQ(Operation::add, c.getOperation());

    // 200 * 60 mu => 60
    // = => 60
    // = => 60
    c.input(Button::ca);
    c.input(Button::d2);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::mul);
    c.input(Button::d6);
    c.input(Button::d0);
    c.input(Button::mu);
    ASSERT_EQ(60, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    ASSERT_EQ(Operation::add, c.getOperation());
    c.input(Button::equals);
    ASSERT_EQ(60, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    ASSERT_EQ(Operation::add, c.getOperation());
    c.input(Button::equals);
    ASSERT_EQ(60, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    ASSERT_EQ(Operation::add, c.getOperation());
}

TEST_MU(EqualsAfterMuPercent) {
    Calculator c(8);
    Register &x = c.getX();
    Register &y = c.getY();

    // 200 mu 60 % => 500
    // = => 300
    // = => 300
    c.input(Button::ca);
    c.input(Button::d2);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::mu);
    c.input(Button::d6);
    c.input(Button::d0);
    c.input(Button::percent);
    ASSERT_EQ(500, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(6, getIntValue(y));
    ASSERT_EQ(1, y.getPointPos());
    ASSERT_EQ(Operation::mu, c.getOperation());
    c.input(Button::equals);
    ASSERT_EQ(300, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    ASSERT_EQ(Operation::add, c.getOperation());
    c.input(Button::equals);
    ASSERT_EQ(300, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    ASSERT_EQ(Operation::add, c.getOperation());
}