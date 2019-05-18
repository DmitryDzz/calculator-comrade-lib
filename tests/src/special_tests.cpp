//
// Created by dmitrydzz on 12.01.19.
//

#include <gmock/gmock.h>
#include <calculator/calculator.h>

#include "calculator/math.h"
#include "calculator/register.h"
#include "calc_helper.h"

using calculatorcomrade::Calculator;
using calculatorcomrade::Button;
using calculatorcomrade::Register;
using calculatorcomrade::Math;
using calculatorcomrade::Operation;

#define TEST_SPECIAL(test_name) TEST(TestSpecial, test_name)

/*
 * WARNING!
 *     1234.5678 (r1)
 *    -100.12345 (r2)
 *    ----------
 *     1134.4444
 *     ---------
 *      1034.321
 *     ---------
 *      934.1976
 *
 * That means that in the second subtraction r2 equals to 100.1234.
 * The lowest digit was lost in case of pointPos's normalization during the first subtraction.
 */
TEST_SPECIAL(RegisterYChanged) {
    Calculator calc(8);
    calc.input(Button::d1);
    calc.input(Button::d2);
    calc.input(Button::d3);
    calc.input(Button::d4);
    calc.input(Button::point);
    calc.input(Button::d5);
    calc.input(Button::d6);
    calc.input(Button::d7);
    calc.input(Button::d8);
    calc.input(Button::minus);
    calc.input(Button::d1);
    calc.input(Button::d0);
    calc.input(Button::d0);
    calc.input(Button::point);
    calc.input(Button::d1);
    calc.input(Button::d2);
    calc.input(Button::d3);
    calc.input(Button::d4);
    calc.input(Button::d5);
    calc.input(Button::equals);

    ASSERT_EQ(11344444, getAbsIntValue(calc.getX()));
    ASSERT_EQ(4, calc.getX().getPointPos());

    ASSERT_EQ(1001234, getAbsIntValue(calc.getY()));
    ASSERT_EQ(4, calc.getY().getPointPos());

    calc.input(Button::equals);

    ASSERT_EQ(1034321, getAbsIntValue(calc.getX()));
    ASSERT_EQ(3, calc.getX().getPointPos());

    ASSERT_EQ(1001234, getAbsIntValue(calc.getY()));
    ASSERT_EQ(4, calc.getY().getPointPos());

    calc.input(Button::equals);

    ASSERT_EQ(9341976, getAbsIntValue(calc.getX()));
    ASSERT_EQ(4, calc.getX().getPointPos());

    ASSERT_EQ(1001234, getAbsIntValue(calc.getY()));
    ASSERT_EQ(4, calc.getY().getPointPos());
}

TEST_SPECIAL(CeAndCeCaCompatibility) {
    Calculator c(8);
    Register &x = c.getX();

    for (int8_t i = 0; i < 8; i++)
        c.input(Button::d9);
    c.input(Button::plus);
    c.input(Button::d1);
    c.input(Button::equals);
    ASSERT_FALSE(x.isZero());
    ASSERT_TRUE(x.hasError());
    c.input(Button::ce);
    ASSERT_FALSE(x.isZero());
    ASSERT_FALSE(x.hasError());
    c.input(Button::ceca);
    ASSERT_TRUE(x.isZero());
    ASSERT_FALSE(x.hasError());
}
