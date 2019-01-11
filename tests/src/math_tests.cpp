//
// Created by dmitrydzz on 10.01.19.
//

#include <gmock/gmock.h>

#include "calculator/math.h"

using calculatorcomrade::Register;
using calculatorcomrade::Math;
using calculatorcomrade::Operation;

TEST(TestMath, AddInt) {
    Register r1(8);
    Register r2(8);

    r1.setValue(123);
    r2.setValue(456);
    Math::calculate(r1, r2, Operation::add);
    ASSERT_EQ(579, r1.getAbsIntValue());
    ASSERT_EQ(Register::NO_POINT, r1.pointPos);
    ASSERT_EQ(false, r1.negative);
    ASSERT_EQ(false, r1.overflow);

    r1.setValue(-123);
    r2.setValue(-456);
    Math::calculate(r1, r2, Operation::add);
    ASSERT_EQ(579, r1.getAbsIntValue());
    ASSERT_EQ(Register::NO_POINT, r1.pointPos);
    ASSERT_EQ(true, r1.negative);
    ASSERT_EQ(false, r1.overflow);

    r1.setValue(-123);
    r2.setValue(456);
    Math::calculate(r1, r2, Operation::add);
    ASSERT_EQ(333, r1.getAbsIntValue());
    ASSERT_EQ(Register::NO_POINT, r1.pointPos);
    ASSERT_EQ(false, r1.negative);
    ASSERT_EQ(false, r1.overflow);

    r1.setValue(123);
    r2.setValue(-456);
    Math::calculate(r1, r2, Operation::add);
    ASSERT_EQ(333, r1.getAbsIntValue());
    ASSERT_EQ(Register::NO_POINT, r1.pointPos);
    ASSERT_EQ(true, r1.negative);
    ASSERT_EQ(false, r1.overflow);
}

TEST(TestMath, AddOverflow) {
    Register r1(8);
    Register r2(8);

    r1.setValue(99999999);
    r2.setValue(1);
    Math::calculate(r1, r2, Operation::add);
    ASSERT_EQ(1, r1.getAbsIntValue());
    ASSERT_EQ(1, r1[0]);
    ASSERT_EQ(Register::NO_POINT, r1.pointPos);
    ASSERT_EQ(false, r1.negative);
    ASSERT_EQ(true, r1.overflow);

    r1.setValue(-99999999);
    r2.setValue(-1);
    Math::calculate(r1, r2, Operation::add);
    ASSERT_EQ(1, r1.getAbsIntValue());
    ASSERT_EQ(1, r1[0]);
    ASSERT_EQ(Register::NO_POINT, r1.pointPos);
    ASSERT_EQ(true, r1.negative);
    ASSERT_EQ(true, r1.overflow);
}

TEST(TestMath, AddReal) {
    Register r1(8);
    Register r2(8);

    r1.setValue(123456, 3); // 123.456
    r2.setValue(123, 2);    //   1.23
    Math::calculate(r1, r2, Operation::add);
    ASSERT_EQ(124686, r1.getAbsIntValue());
    ASSERT_EQ(3, r1.pointPos);
    ASSERT_EQ(false, r1.negative);
    ASSERT_EQ(false, r1.overflow);
    ASSERT_EQ(123, r2.getAbsIntValue());
    ASSERT_EQ(2, r1.pointPos);

    //TODO Some special test
    /*
     * WARNING!
     *     1234.5678 (r1)
     *    -100.12345 (r2)
     *    ----------
     *     1134.4444
     *     ---------
     *      1034.321
     *
     * That means that in the second subtraction r2 equals to 100.1234.
     * The lowest digit was lost in case of pointPos's normalization during the first subtraction.
     */
}
