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

std::string r1_text;
std::string r2_text;
std::string rT_text;

void on_r1_changed(Register &r) {
    calculatorcomrade::evaluateText(r, &r1_text);
    r1_text = r1_text;
}

void on_r2_changed(Register &r) {
    calculatorcomrade::evaluateText(r, &r2_text);
    r2_text = r2_text;
}

void on_rt_changed(Register &r) {
    calculatorcomrade::evaluateText(r, &rT_text);
    rT_text = rT_text;
}

TEST_MATH(AddInt) {
    Register r1(8);
    Register r2(8);

    setValue(r1, 123);
    setValue(r2, 456);
    Math::calculate(r1, r2, Operation::add);
    ASSERT_EQ(579, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.getNegative());
    ASSERT_EQ(false, r1.getOverflow());

    setValue(r1, -123);
    setValue(r2, -456);
    Math::calculate(r1, r2, Operation::add);
    ASSERT_EQ(579, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(true, r1.getNegative());
    ASSERT_EQ(false, r1.getOverflow());

    setValue(r1, -123);
    setValue(r2, 456);
    Math::calculate(r1, r2, Operation::add);
    ASSERT_EQ(333, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.getNegative());
    ASSERT_EQ(false, r1.getOverflow());

    setValue(r1, 123);
    setValue(r2, -456);
    Math::calculate(r1, r2, Operation::add);
    ASSERT_EQ(333, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(true, r1.getNegative());
    ASSERT_EQ(false, r1.getOverflow());
}

TEST_MATH(AddOverflow) {
    Register r1(8);
    Register r2(8);

    setValue(r1, 99999999);
    setValue(r2, 1);
    Math::calculate(r1, r2, Operation::add);
    ASSERT_EQ(1, getAbsIntValue(r1));
    ASSERT_EQ(1, r1.getDigit(0));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.getNegative());
    ASSERT_EQ(true, r1.getOverflow());

    setValue(r1, -99999999);
    setValue(r2, -1);
    Math::calculate(r1, r2, Operation::add);
    ASSERT_EQ(1, getAbsIntValue(r1));
    ASSERT_EQ(1, r1.getDigit(0));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(true, r1.getNegative());
    ASSERT_EQ(true, r1.getOverflow());
}

TEST_MATH(AddReal) {
    Register r1(8);
    Register r2(8);

    setValue(r1, 123456, 3); // 123.456
    setValue(r2, 123, 2);    //   1.23
    Math::calculate(r1, r2, Operation::add);
    ASSERT_EQ(124686, getAbsIntValue(r1));
    ASSERT_EQ(3, r1.getPointPos());
    ASSERT_EQ(false, r1.getNegative());
    ASSERT_EQ(false, r1.getOverflow());
    ASSERT_EQ(123, getAbsIntValue(r2));
    ASSERT_EQ(2, r2.getPointPos());
}

TEST_MATH(SubInt) {
    Register r1(8);
    Register r2(8);

    setValue(r1, 12345);
    setValue(r2, 6789);
    Math::calculate(r1, r2, Operation::sub);
    ASSERT_EQ(5556, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.getNegative());
    ASSERT_EQ(false, r1.getOverflow());

    setValue(r1, -123);
    setValue(r2, -468);
    Math::calculate(r1, r2, Operation::sub);
    ASSERT_EQ(345, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.getNegative());
    ASSERT_EQ(false, r1.getOverflow());

    setValue(r1, -123);
    setValue(r2, 468);
    Math::calculate(r1, r2, Operation::sub);
    ASSERT_EQ(591, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(true, r1.getNegative());
    ASSERT_EQ(false, r1.getOverflow());

    setValue(r1, 123);
    setValue(r2, -468);
    Math::calculate(r1, r2, Operation::sub);
    ASSERT_EQ(591, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.getNegative());
    ASSERT_EQ(false, r1.getOverflow());
}

TEST_MATH(SubOverflow) {
    Register r1(8);
    Register r2(8);

    setValue(r1, -99999999);
    setValue(r2, 1);
    Math::calculate(r1, r2, Operation::sub);
    ASSERT_EQ(1, getAbsIntValue(r1));
    ASSERT_EQ(1, r1.getDigit(0));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(true, r1.getNegative());
    ASSERT_EQ(true, r1.getOverflow());

    setValue(r1, 99999999);
    setValue(r2, -1);
    Math::calculate(r1, r2, Operation::sub);
    ASSERT_EQ(1, getAbsIntValue(r1));
    ASSERT_EQ(1, r1.getDigit(0));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.getNegative());
    ASSERT_EQ(true, r1.getOverflow());
}

TEST_MATH(SubReal) {
    Register r1(8);
    Register r2(8);

    setValue(r1, 123456, 3); // 123.456
    setValue(r2, 123, 2);    //   1.23
    Math::calculate(r1, r2, Operation::sub);
    ASSERT_EQ(122226, getAbsIntValue(r1));
    ASSERT_EQ(3, r1.getPointPos());
    ASSERT_EQ(false, r1.getNegative());
    ASSERT_EQ(false, r1.getOverflow());
    ASSERT_EQ(123, getAbsIntValue(r2));
    ASSERT_EQ(2, r2.getPointPos());
}

TEST_MATH(NonNegativeZeroAfterSum) {
    Register r1(8);
    Register r2(8);

    setValue(r1, -1974);
    setValue(r2, 1974);
    Math::calculate(r1, r2, Operation::add);
    bool zero = true;
    for (uint8_t i = 0; i < 8; i++) {
        if (r1.getDigit(i) > 0) {
            zero = false;
            break;
        }
    }
    ASSERT_TRUE(zero);
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.getNegative());
    ASSERT_EQ(false, r1.getOverflow());
}

TEST_MATH(MulInt) {
    Register r1(4);
    Register r2(4);

    setValue(r1, 12);
    setValue(r2, 34);
    Math::calculate(r1, r2, Operation::mul);
    ASSERT_EQ(408, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.getNegative());
    ASSERT_EQ(false, r1.getOverflow());

    setValue(r1, 12);
    setValue(r2, -34);
    Math::calculate(r1, r2, Operation::mul);
    ASSERT_EQ(408, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(true, r1.getNegative());
    ASSERT_EQ(false, r1.getOverflow());
}

TEST_MATH(NonNegativeZeroAfterMul) {
    Register r1(8);
    Register r2(8);

    setValue(r1, -1974);
    setValue(r2, 0);
    Math::calculate(r1, r2, Operation::mul);
    ASSERT_TRUE(r1.isZeroData());
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.getNegative());
    ASSERT_EQ(false, r1.getOverflow());
}

TEST_MATH(MulTruncAfterPoint1) {
    Register r1(3);
    Register r2(3);

    setValue(r1, 87, 1); // 8.7
    setValue(r2, 54, 1); // 5.4
    Math::calculate(r1, r2, Operation::mul);
    ASSERT_EQ(469, getAbsIntValue(r1));
    ASSERT_EQ(1, r1.getPointPos());
    ASSERT_EQ(false, r1.getNegative());
    ASSERT_EQ(false, r1.getOverflow());
}

TEST_MATH(MulTruncAfterPoint2) {
    Register r1(3);
    Register r2(3);

    setValue(r1, 12, 1); // 1.2
    setValue(r2, 523, 2); // 5.23
    Math::calculate(r1, r2, Operation::mul);
    ASSERT_EQ(627, getAbsIntValue(r1));
    ASSERT_EQ(2, r1.getPointPos());
    ASSERT_EQ(false, r1.getNegative());
    ASSERT_EQ(false, r1.getOverflow());
}

TEST_MATH(MulOverflow) {
    Register r1(3);
    Register r2(3);

    setValue(r1, 987, 1); // 98.7
    setValue(r2, 654, 1); // 65.4
    Math::calculate(r1, r2, Operation::mul);
//    ASSERT_EQ(645, getAbsIntValue(r1));
    ASSERT_EQ(640, getAbsIntValue(r1));
    ASSERT_EQ(2, r1.getPointPos());
    ASSERT_EQ(false, r1.getNegative());
    ASSERT_EQ(true, r1.getOverflow());
}

TEST_MATH(Temp1) {
    Register r1(8);
    Register r2(8);
    Register rT(8);

    r1.setChangedCallback(on_r1_changed);
    r2.setChangedCallback(on_r2_changed);
    rT.setChangedCallback(on_rt_changed);

    setValue(r1, 56987658, 0);
    setValue(r2, 98065232, 0);
    Math::mul(r1, r2, rT);
    ASSERT_EQ(55885079, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.getNegative());
    ASSERT_EQ(true, r1.getOverflow());
}

TEST_MATH(Temp2) {
    Register r1(3);
    Register r2(3);

    setValue(r2, 604, 0);
    setValue(r1, 987, 0);
    Math::calculate(r1, r2, Operation::mul);
    ASSERT_EQ(591, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.getNegative());
    ASSERT_EQ(true, r1.getOverflow());
}
