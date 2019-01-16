//
// Created by dmitrydzz on 12.01.19.
//

#include <gmock/gmock.h>
#include <calculator/calculator.h>

#include "calculator/state.h"
#include "calculator/register.h"
#include "calc_helper.h"

using calculatorcomrade::Calculator;
using calculatorcomrade::Button;
using calculatorcomrade::State;
using calculatorcomrade::Register;
using calculatorcomrade::Math;
using calculatorcomrade::Operation;

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
TEST(TestSpecial, RegisterYChanged) {
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

    ASSERT_EQ(11344444, getAbsIntValue(calc.getState().x));
    ASSERT_EQ(4, calc.getState().x.getPointPos());

    ASSERT_EQ(1001234, getAbsIntValue(calc.getState().y));
    ASSERT_EQ(4, calc.getState().y.getPointPos());

    calc.input(Button::equals);

    ASSERT_EQ(1034321, getAbsIntValue(calc.getState().x));
    ASSERT_EQ(3, calc.getState().x.getPointPos());

    ASSERT_EQ(1001234, getAbsIntValue(calc.getState().y));
    ASSERT_EQ(4, calc.getState().y.getPointPos());

    calc.input(Button::equals);

    ASSERT_EQ(9341976, getAbsIntValue(calc.getState().x));
    ASSERT_EQ(4, calc.getState().x.getPointPos());

    ASSERT_EQ(1001234, getAbsIntValue(calc.getState().y));
    ASSERT_EQ(4, calc.getState().y.getPointPos());
}
