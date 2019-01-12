//
// Created by dmitrydzz on 10.01.19.
//

#include <gmock/gmock.h>

#include "calculator/math.h"
#include "calc_helper.h"

using calculatorcomrade::Register;
using calculatorcomrade::Math;
using calculatorcomrade::Operation;

#define TEST_MATH(test_name) TEST(TestMath, test_name)

TEST_MATH(AddInt) {
    Register r1(8);
    Register r2(8);

    setValue(r1, 123);
    setValue(r2, 456);
    Math::calculate(r1, r2, Operation::add);
    ASSERT_EQ(579, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.pointPos);
    ASSERT_EQ(false, r1.negative);
    ASSERT_EQ(false, r1.overflow);

    setValue(r1, -123);
    setValue(r2, -456);
    Math::calculate(r1, r2, Operation::add);
    ASSERT_EQ(579, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.pointPos);
    ASSERT_EQ(true, r1.negative);
    ASSERT_EQ(false, r1.overflow);

    setValue(r1, -123);
    setValue(r2, 456);
    Math::calculate(r1, r2, Operation::add);
    ASSERT_EQ(333, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.pointPos);
    ASSERT_EQ(false, r1.negative);
    ASSERT_EQ(false, r1.overflow);

    setValue(r1, 123);
    setValue(r2, -456);
    Math::calculate(r1, r2, Operation::add);
    ASSERT_EQ(333, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.pointPos);
    ASSERT_EQ(true, r1.negative);
    ASSERT_EQ(false, r1.overflow);
}

TEST_MATH(AddOverflow) {
    Register r1(8);
    Register r2(8);

    setValue(r1, 99999999);
    setValue(r2, 1);
    Math::calculate(r1, r2, Operation::add);
    ASSERT_EQ(1, getAbsIntValue(r1));
    ASSERT_EQ(1, r1[0]);
    ASSERT_EQ(0, r1.pointPos);
    ASSERT_EQ(false, r1.negative);
    ASSERT_EQ(true, r1.overflow);

    setValue(r1, -99999999);
    setValue(r2, -1);
    Math::calculate(r1, r2, Operation::add);
    ASSERT_EQ(1, getAbsIntValue(r1));
    ASSERT_EQ(1, r1[0]);
    ASSERT_EQ(0, r1.pointPos);
    ASSERT_EQ(true, r1.negative);
    ASSERT_EQ(true, r1.overflow);
}

TEST_MATH(AddReal) {
    Register r1(8);
    Register r2(8);

    setValue(r1, 123456, 3); // 123.456
    setValue(r2, 123, 2);    //   1.23
    Math::calculate(r1, r2, Operation::add);
    ASSERT_EQ(124686, getAbsIntValue(r1));
    ASSERT_EQ(3, r1.pointPos);
    ASSERT_EQ(false, r1.negative);
    ASSERT_EQ(false, r1.overflow);
    ASSERT_EQ(123, getAbsIntValue(r2));
    ASSERT_EQ(2, r2.pointPos);
}

TEST_MATH(SubInt) {
    Register r1(8);
    Register r2(8);

    setValue(r1, 12345);
    setValue(r2, 6789);
    Math::calculate(r1, r2, Operation::sub);
    ASSERT_EQ(5556, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.pointPos);
    ASSERT_EQ(false, r1.negative);
    ASSERT_EQ(false, r1.overflow);

    setValue(r1, -123);
    setValue(r2, -468);
    Math::calculate(r1, r2, Operation::sub);
    ASSERT_EQ(345, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.pointPos);
    ASSERT_EQ(false, r1.negative);
    ASSERT_EQ(false, r1.overflow);

    setValue(r1, -123);
    setValue(r2, 468);
    Math::calculate(r1, r2, Operation::sub);
    ASSERT_EQ(591, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.pointPos);
    ASSERT_EQ(true, r1.negative);
    ASSERT_EQ(false, r1.overflow);

    setValue(r1, 123);
    setValue(r2, -468);
    Math::calculate(r1, r2, Operation::sub);
    ASSERT_EQ(591, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.pointPos);
    ASSERT_EQ(false, r1.negative);
    ASSERT_EQ(false, r1.overflow);
}

TEST_MATH(SubOverflow) {
    Register r1(8);
    Register r2(8);

    setValue(r1, -99999999);
    setValue(r2, 1);
    Math::calculate(r1, r2, Operation::sub);
    ASSERT_EQ(1, getAbsIntValue(r1));
    ASSERT_EQ(1, r1[0]);
    ASSERT_EQ(0, r1.pointPos);
    ASSERT_EQ(true, r1.negative);
    ASSERT_EQ(true, r1.overflow);

    setValue(r1, 99999999);
    setValue(r2, -1);
    Math::calculate(r1, r2, Operation::sub);
    ASSERT_EQ(1, getAbsIntValue(r1));
    ASSERT_EQ(1, r1[0]);
    ASSERT_EQ(0, r1.pointPos);
    ASSERT_EQ(false, r1.negative);
    ASSERT_EQ(true, r1.overflow);
}

TEST_MATH(SubReal) {
    Register r1(8);
    Register r2(8);

    setValue(r1, 123456, 3); // 123.456
    setValue(r2, 123, 2);    //   1.23
    Math::calculate(r1, r2, Operation::sub);
    ASSERT_EQ(122226, getAbsIntValue(r1));
    ASSERT_EQ(3, r1.pointPos);
    ASSERT_EQ(false, r1.negative);
    ASSERT_EQ(false, r1.overflow);
    ASSERT_EQ(123, getAbsIntValue(r2));
    ASSERT_EQ(2, r2.pointPos);
}

TEST_MATH(MulInt) {
    Register r1(4);
    Register r2(4);

    setValue(r1, 12);
    setValue(r2, 34);
    Math::calculate(r1, r2, Operation::mul);
    ASSERT_EQ(408, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.pointPos);
    ASSERT_EQ(false, r1.negative);
    ASSERT_EQ(false, r1.overflow);
}