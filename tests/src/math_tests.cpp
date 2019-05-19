//
// Created by dmitrydzz on 10.01.19.
//

#include <gmock/gmock.h>

#include "calculator/config.h"
#include "calculator/math.h"
#include "calc_helper.h"

using calculatorcomrade::Config;
using calculatorcomrade::Register;
using calculatorcomrade::Math;
using calculatorcomrade::Operation;

#define TEST_MATH(test_name) TEST(TestMath, test_name)

std::string r1_text;
std::string r2_text;
std::string r3_text;

void on_r1_changed(Register &r) {
    calculatorcomrade::evaluateText(r, &r1_text);
//    r1_text = r1_text;
}

void on_r2_changed(Register &r) {
    calculatorcomrade::evaluateText(r, &r2_text);
//    r2_text = r2_text;
}

void on_r3_changed(Register &r) {
    calculatorcomrade::evaluateText(r, &r3_text);
//    r3_text = r3_text;
}

TEST_MATH(Compare) {
    Register r1(8);
    Register r2(8);

    setValue(r1, 0);
    setValue(r2, 0);
    ASSERT_EQ(0, Math::compare(r1, r2));

    setValue(r1, 5);
    setValue(r2, 10);
    ASSERT_EQ(-1, Math::compare(r1, r2));

    setValue(r1, 10);
    setValue(r2, 5);
    ASSERT_EQ(1, Math::compare(r1, r2));

    setValue(r1, -5);
    setValue(r2, -10);
    ASSERT_EQ(1, Math::compare(r1, r2));

    setValue(r1, -10);
    setValue(r2, -5);
    ASSERT_EQ(-1, Math::compare(r1, r2));

    setValue(r1, -5);
    setValue(r2, 10);
    ASSERT_EQ(-1, Math::compare(r1, r2));

    setValue(r1, 10);
    setValue(r2, -5);
    ASSERT_EQ(1, Math::compare(r1, r2));

    setValue(r1, 5);
    setValue(r2, -10);
    ASSERT_EQ(1, Math::compare(r1, r2));

    setValue(r1, -10);
    setValue(r2, 5);
    ASSERT_EQ(-1, Math::compare(r1, r2));

    setValue(r1, 123, 2);
    setValue(r2, 12345, 3);
    ASSERT_EQ(-1, Math::compare(r1, r2));

    setValue(r1, 123, 0);
    setValue(r2, 12345, 3);
    ASSERT_EQ(-1, Math::compare(r1, r2));

    setValue(r1, 123, 4);
    setValue(r2, 12345, 6);
    ASSERT_EQ(-1, Math::compare(r1, r2));

    setValue(r1, 123, 4);
    setValue(r2, 12345, 7);
    ASSERT_EQ(1, Math::compare(r1, r2));

    setValue(r1, 12345, 6);
    setValue(r2, 12345, 6);
    ASSERT_EQ(0, Math::compare(r1, r2));
}

TEST_MATH(AddInt) {
    Register r1(8);
    Register r2(8);

    setValue(r1, 123);
    setValue(r2, 456);
    Math::calculate(r1, r2, Operation::add, Config::OPTIONS_DEFAULT);
    ASSERT_EQ(579, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());

    setValue(r1, -123);
    setValue(r2, -456);
    Math::calculate(r1, r2, Operation::add, Config::OPTIONS_DEFAULT);
    ASSERT_EQ(579, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(true, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());

    setValue(r1, -123);
    setValue(r2, 456);
    Math::calculate(r1, r2, Operation::add, Config::OPTIONS_DEFAULT);
    ASSERT_EQ(333, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());

    setValue(r1, 123);
    setValue(r2, -456);
    Math::calculate(r1, r2, Operation::add, Config::OPTIONS_DEFAULT);
    ASSERT_EQ(333, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(true, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());
}

TEST_MATH(AddOverflowTruncZeros) {
    Register r1(8);
    Register r2(8);

    uint8_t options = Config::OPTIONS_DEFAULT | Config::OPTION_TRUNC_ZEROS_ON_OVERFLOW;

    setValue(r1, 99999999);
    setValue(r2, 1);
    Math::calculate(r1, r2, Operation::add, options);
    ASSERT_EQ(1, getIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(true, r1.hasError());

    setValue(r1, -99999999);
    setValue(r2, -1);
    Math::calculate(r1, r2, Operation::add, options);
    ASSERT_EQ(-1, getIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(true, r1.hasError());
}

TEST_MATH(AddOverflowDoNotTruncZeros) {
    Register r1(8);
    Register r2(8);

    uint8_t options = Config::OPTIONS_DEFAULT & (~Config::OPTION_TRUNC_ZEROS_ON_OVERFLOW);

    setValue(r1, 99999999);
    setValue(r2, 1);
    Math::calculate(r1, r2, Operation::add, options);
    ASSERT_EQ(10000000, getIntValue(r1));
    ASSERT_EQ(7, r1.getPointPos());
    ASSERT_EQ(true, r1.hasError());

    setValue(r1, -99999999);
    setValue(r2, -1);
    Math::calculate(r1, r2, Operation::add, options);
    ASSERT_EQ(-10000000, getIntValue(r1));
    ASSERT_EQ(7, r1.getPointPos());
    ASSERT_EQ(true, r1.hasError());
}

TEST_MATH(AddOverflowNoRound) {
    Register r1(8);
    Register r2(8);

    // There's no rounding on overflow (1):
    setValue(r1, 99999933);
    setValue(r2, 121); // The result in 9 digits is 10000005[4]
    Math::calculate(r1, r2, Operation::add, Config::OPTIONS_DEFAULT);
    ASSERT_EQ(10000005, getAbsIntValue(r1));
    ASSERT_EQ(7, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(true, r1.hasError());

    // There's no rounding on overflow (2):
    setValue(r1, 99999933);
    setValue(r2, 126); // The result in 9 digits is 10000005[9]
    Math::calculate(r1, r2, Operation::add, Config::OPTIONS_DEFAULT);
    ASSERT_EQ(10000005, getAbsIntValue(r1));
    ASSERT_EQ(7, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(true, r1.hasError());
}

TEST_MATH(AddNoOverflow) {
    Register r1(8);
    Register r2(8);

    r1.setChangedCallback(on_r1_changed);
    r2.setChangedCallback(on_r2_changed);

    setValue(r1, 90000001, 7);
    setValue(r2, 1);
    Math::calculate(r1, r2, Operation::add, Config::OPTIONS_DEFAULT);
    ASSERT_FALSE(r1.hasError());
    ASSERT_EQ(10, getIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
}

TEST_MATH(AddReal) {
    Register r1(8);
    Register r2(8);

    setValue(r1, 123456, 3); // 123.456
    setValue(r2, 123, 2);    //   1.23
    Math::calculate(r1, r2, Operation::add, Config::OPTIONS_DEFAULT);
    ASSERT_EQ(124686, getAbsIntValue(r1));
    ASSERT_EQ(3, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());
    ASSERT_EQ(123, getAbsIntValue(r2));
    ASSERT_EQ(2, r2.getPointPos());
}

TEST_MATH(SubInt) {
    Register r1(8);
    Register r2(8);

    setValue(r1, 2);
    setValue(r2, 2);
    Math::calculate(r1, r2, Operation::sub, Config::OPTIONS_DEFAULT);
    ASSERT_EQ(0, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());

    setValue(r1, 12345);
    setValue(r2, 6789);
    Math::calculate(r1, r2, Operation::sub, Config::OPTIONS_DEFAULT);
    ASSERT_EQ(5556, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());

    setValue(r1, -123);
    setValue(r2, -468);
    Math::calculate(r1, r2, Operation::sub, Config::OPTIONS_DEFAULT);
    ASSERT_EQ(345, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());

    setValue(r1, -123);
    setValue(r2, 468);
    Math::calculate(r1, r2, Operation::sub, Config::OPTIONS_DEFAULT);
    ASSERT_EQ(591, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(true, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());

    setValue(r1, 123);
    setValue(r2, -468);
    Math::calculate(r1, r2, Operation::sub, Config::OPTIONS_DEFAULT);
    ASSERT_EQ(591, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());
}

TEST_MATH(SubOverflowTruncZeros) {
    Register r1(8);
    Register r2(8);

    uint8_t options = Config::OPTIONS_DEFAULT | Config::OPTION_TRUNC_ZEROS_ON_OVERFLOW;

    setValue(r1, -99999999);
    setValue(r2, 1);
    Math::calculate(r1, r2, Operation::sub, options);
    ASSERT_EQ(-1, getIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(true, r1.hasError());

    setValue(r1, 99999999);
    setValue(r2, -1);
    Math::calculate(r1, r2, Operation::sub, options);
    ASSERT_EQ(1, getIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(true, r1.hasError());
}

TEST_MATH(SubOverflowDoNotTruncZeros) {
    Register r1(8);
    Register r2(8);

    uint8_t options = Config::OPTIONS_DEFAULT & (~Config::OPTION_TRUNC_ZEROS_ON_OVERFLOW);

    setValue(r1, -99999999);
    setValue(r2, 1);
    Math::calculate(r1, r2, Operation::sub, options);
    ASSERT_EQ(-10000000, getIntValue(r1));
    ASSERT_EQ(7, r1.getPointPos());
    ASSERT_EQ(true, r1.hasError());

    setValue(r1, 99999999);
    setValue(r2, -1);
    Math::calculate(r1, r2, Operation::sub, options);
    ASSERT_EQ(10000000, getIntValue(r1));
    ASSERT_EQ(7, r1.getPointPos());
    ASSERT_EQ(true, r1.hasError());
}

TEST_MATH(SubOverflowNoRound) {
    Register r1(8);
    Register r2(8);

    // There's no rounding on overflow (1):
    setValue(r1, -99999933);
    setValue(r2, 121); // The result in 9 digits is 100000054
    Math::calculate(r1, r2, Operation::sub, Config::OPTIONS_DEFAULT);
    ASSERT_EQ(10000005, getAbsIntValue(r1));
    ASSERT_EQ(7, r1.getPointPos());
    ASSERT_EQ(true, r1.isNegative());
    ASSERT_EQ(true, r1.hasError());

    // There's no rounding on overflow (2):
    setValue(r1, -99999933);
    setValue(r2, 126); // The result in 9 digits is 100000059
    Math::calculate(r1, r2, Operation::sub, Config::OPTIONS_DEFAULT);
    ASSERT_EQ(10000005, getAbsIntValue(r1));
    ASSERT_EQ(7, r1.getPointPos());
    ASSERT_EQ(true, r1.isNegative());
    ASSERT_EQ(true, r1.hasError());
}

TEST_MATH(SubReal) {
    Register r1(8);
    Register r2(8);

    setValue(r1, 123456, 3); // 123.456
    setValue(r2, 123, 2);    //   1.23
    Math::calculate(r1, r2, Operation::sub, Config::OPTIONS_DEFAULT);
    ASSERT_EQ(122226, getAbsIntValue(r1));
    ASSERT_EQ(3, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());
    ASSERT_EQ(123, getAbsIntValue(r2));
    ASSERT_EQ(2, r2.getPointPos());
}

TEST_MATH(NonNegativeZeroAfterSum) {
    Register r1(8);
    Register r2(8);

    setValue(r1, -1974);
    setValue(r2, 1974);
    Math::calculate(r1, r2, Operation::add, Config::OPTIONS_DEFAULT);
    bool zero = true;
    for (int8_t i = 0; i < 8; i++) {
        if (r1.getDigit(i) > 0) {
            zero = false;
            break;
        }
    }
    ASSERT_TRUE(zero);
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());
}

TEST_MATH(MulInt) {
    Register r1(4);
    Register r2(4);

    setValue(r1, 12);
    setValue(r2, 34);
    Math::calculate(r1, r2, Operation::mul, Config::OPTIONS_DEFAULT);
    ASSERT_EQ(408, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());

    setValue(r1, 12);
    setValue(r2, -34);
    Math::calculate(r1, r2, Operation::mul, Config::OPTIONS_DEFAULT);
    ASSERT_EQ(408, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(true, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());
}

TEST_MATH(NonNegativeZeroAfterMul) {
    Register r1(8);
    Register r2(8);

    setValue(r1, -1974);
    setValue(r2, 0);
    Math::calculate(r1, r2, Operation::mul, Config::OPTIONS_DEFAULT);
    ASSERT_TRUE(r1.isZero());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());
}

TEST_MATH(MulTruncAfterPoint1) {
    Register r1(3);
    Register r2(3);

    setValue(r1, 87, 1); // 8.7
    setValue(r2, 54, 1); // 5.4
    Math::calculate(r1, r2, Operation::mul, Config::OPTIONS_DEFAULT);
    ASSERT_EQ(469, getAbsIntValue(r1));
    ASSERT_EQ(1, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());
}

TEST_MATH(MulTruncAfterPoint2) {
    Register r1(3);
    Register r2(3);
    Register acc(6);

    r1.setChangedCallback(on_r1_changed);
    r2.setChangedCallback(on_r2_changed);
    acc.setChangedCallback(on_r3_changed);

    setValue(r1, 12, 1); // 1.2
    setValue(r2, 523, 2); // 5.23
    Math::mul(r1, r2, acc);
    ASSERT_EQ(627, getAbsIntValue(r1));
    ASSERT_EQ(2, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());
}

TEST_MATH(MulOverflow) {
    Register r1(3);
    Register r2(3);
    Register acc(6);

    r1.setChangedCallback(on_r1_changed);
    r2.setChangedCallback(on_r2_changed);
    acc.setChangedCallback(on_r3_changed);

    setValue(r1, 987, 1); // 98.7
    setValue(r2, 654, 1); // 65.4
    Math::mul(r1, r2, acc);
    ASSERT_EQ(645, getAbsIntValue(r1));
    ASSERT_EQ(2, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(true, r1.hasError());
}

TEST_MATH(MulReadOperations) {
    Register r1(8);
    Register r2(8);
    Register acc(16);

    r1.setChangedCallback(on_r1_changed);
    r2.setChangedCallback(on_r2_changed);
    acc.setChangedCallback(on_r3_changed);

    setValue(r1, 56987658, 0);
    setValue(r2, 2, 0);
    Math::mul(r1, r2, acc);
    ASSERT_EQ(11397531, getAbsIntValue(r1));
    ASSERT_EQ(7, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(true, r1.hasError());

    setValue(r1, 56987658, 0);
    setValue(r2, 32, 0);
    Math::mul(r1, r2, acc);
    ASSERT_EQ(1823605, getAbsIntValue(r1));
    ASSERT_EQ(5, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(true, r1.hasError());

    setValue(r1, 56987658, 0);
    setValue(r2, 232, 0);
    Math::mul(r1, r2, acc);
    ASSERT_EQ(13221136, getAbsIntValue(r1));
    ASSERT_EQ(5, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(true, r1.hasError());

    setValue(r1, 56987658, 0);
    setValue(r2, 5232, 0);
    Math::mul(r1, r2, acc);
    ASSERT_EQ(29815942, getAbsIntValue(r1));
    ASSERT_EQ(4, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(true, r1.hasError());

    setValue(r1, 56987658, 0);
    setValue(r2, 65232, 0);
    Math::mul(r1, r2, acc);
    ASSERT_EQ(37174189, getAbsIntValue(r1));
    ASSERT_EQ(3, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(true, r1.hasError());

    setValue(r1, 56987658, 0);
    setValue(r2, 8065232, 0);
    Math::mul(r1, r2, acc);
    ASSERT_EQ(45961868, getAbsIntValue(r1));
    ASSERT_EQ(1, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(true, r1.hasError());

    setValue(r1, 56987658, 0);
    setValue(r2, 98065232, 0);
    Math::mul(r1, r2, acc);
    ASSERT_EQ(55885079, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(true, r1.hasError());
}

TEST_MATH(DivInt1) {
    Register r1(2);
    Register r2(2);
    Register acc(4);

    r1.setChangedCallback(on_r1_changed);
    r2.setChangedCallback(on_r2_changed);
    acc.setChangedCallback(on_r3_changed);

    // 15 : 5 = 3
    setValue(r1, 15);
    setValue(r2, 5);
    Math::div(r1, r2, acc);
    ASSERT_EQ(3, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());

    // -15 : 5 = -3
    setValue(r1, -15);
    setValue(r2, 5);
    Math::div(r1, r2, acc);
    ASSERT_EQ(3, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(true, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());

    // 15 : (-5) = -3
    setValue(r1, 15);
    setValue(r2, -5);
    Math::div(r1, r2, acc);
    ASSERT_EQ(3, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(true, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());
}

TEST_MATH(DivInt2) {
    Register r1(3);
    Register r2(3);
    Register acc(6);

    r1.setChangedCallback(on_r1_changed);
    r2.setChangedCallback(on_r2_changed);
    acc.setChangedCallback(on_r3_changed);

    // 500 : 5 = 100
    setValue(r1, 500);
    setValue(r2, 5);
    Math::div(r1, r2, acc);
    ASSERT_EQ(100, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());
}

TEST_MATH(DivZero) {
    Register r1(2);
    Register r2(2);

    // 15 : 0 = [Err]0
    setValue(r1, 15);
    setValue(r2, 0);
    Math::div(r1, r2);
    ASSERT_TRUE(r1.isZero());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(true, r1.hasError());

    setValue(r1, -15, 1); // r1 = -1.5
    setValue(r2, 0);
    Math::div(r1, r2);
    ASSERT_TRUE(r1.isZero());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(true, r1.hasError());
}

TEST_MATH(DivReal1) {
    Register r1(2);
    Register r2(2);
    Register acc(4);

    r1.setChangedCallback(on_r1_changed);
    r2.setChangedCallback(on_r2_changed);
    acc.setChangedCallback(on_r3_changed);

    // 5 : 2 = 2.5
    setValue(r1, 5);
    setValue(r2, 2);
    Math::div(r1, r2, acc);
    ASSERT_EQ(25, getAbsIntValue(r1));
    ASSERT_EQ(1, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());
}

TEST_MATH(DivReal2) {
    Register r1(4);
    Register r2(4);
    Register acc(8);

    r1.setChangedCallback(on_r1_changed);
    r2.setChangedCallback(on_r2_changed);
    acc.setChangedCallback(on_r3_changed);

    // 10 : 6 = 1.666
    setValue(r1, 10);
    setValue(r2, 6);
    Math::div(r1, r2, acc);
    ASSERT_EQ(1666, getAbsIntValue(r1));
    ASSERT_EQ(3, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());
}

TEST_MATH(DivReal3) {
    Register r1(4);
    Register r2(4);
    Register acc(8);

    r1.setChangedCallback(on_r1_changed);
    r2.setChangedCallback(on_r2_changed);
    acc.setChangedCallback(on_r3_changed);

    // 1 : 6 = 0.166
    setValue(r1, 1);
    setValue(r2, 6);
    Math::div(r1, r2, acc);
    ASSERT_EQ(166, getAbsIntValue(r1));
    ASSERT_EQ(3, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());
}

TEST_MATH(DivReal4) {
    Register r1(8);
    Register r2(8);
    Register acc(16);

    r1.setChangedCallback(on_r1_changed);
    r2.setChangedCallback(on_r2_changed);
    acc.setChangedCallback(on_r3_changed);

    // 15 : 26 = 0.576923
    setValue(r1, 15);
    setValue(r2, 26);
    Math::div(r1, r2, acc);
    ASSERT_EQ(576923, getAbsIntValue(r1));
    ASSERT_EQ(6, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());
}

TEST_MATH(DivReal5) {
    Register r1(8);
    Register r2(8);
    Register acc(16);

    r1.setChangedCallback(on_r1_changed);
    r2.setChangedCallback(on_r2_changed);
    acc.setChangedCallback(on_r3_changed);

    // 197.4 : 0.01 = 19740
    setValue(r1, 1974, 1);
    setValue(r2, 1, 2);
    Math::div(r1, r2, acc);
    ASSERT_EQ(19740, getAbsIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());
}

TEST_MATH(DivReal6) {
    Register r1(8);
    Register r2(8);
    Register acc(16);

    r1.setChangedCallback(on_r1_changed);
    r2.setChangedCallback(on_r2_changed);
    acc.setChangedCallback(on_r3_changed);

    // 1 : 24 = 0.0416666
    setValue(r1, 1);
    setValue(r2, 24);
    Math::div(r1, r2, acc);
    ASSERT_EQ(416666, getAbsIntValue(r1));
    ASSERT_EQ(7, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());
}

TEST_MATH(DivReal7) {
    Register r1(3);
    Register r2(3);
    Register acc(6);

    r1.setChangedCallback(on_r1_changed);
    r2.setChangedCallback(on_r2_changed);
    acc.setChangedCallback(on_r3_changed);

    // 2.5 : 2 = 1.25
    setValue(r1, 25, 1);
    setValue(r2, 2);
    Math::div(r1, r2, acc);
    ASSERT_EQ(125, getAbsIntValue(r1));
    ASSERT_EQ(2, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());
}

TEST_MATH(DivOverflow1) {
    Register r1(3);
    Register r2(3);
    Register acc(6);

    r1.setChangedCallback(on_r1_changed);
    r2.setChangedCallback(on_r2_changed);
    acc.setChangedCallback(on_r3_changed);

    // 999 : 0.02 = [Err]49.9 (=49950)
    setValue(r1, 999);
    setValue(r2, 2, 2);
    Math::div(r1, r2, acc);
    ASSERT_EQ(499, getAbsIntValue(r1));
    ASSERT_EQ(1, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(true, r1.hasError());
}

TEST_MATH(DivOverflow2) {
    Register r1(8);
    Register r2(8);
    Register acc(16);

    r1.setChangedCallback(on_r1_changed);
    r2.setChangedCallback(on_r2_changed);
    acc.setChangedCallback(on_r3_changed);

    // 99999999 : 0.02 = [Err]49.999999
    setValue(r1, 99999999);
    setValue(r2, 2, 2);
    Math::div(r1, r2, acc);
    ASSERT_EQ(49999999, getAbsIntValue(r1));
    ASSERT_EQ(6, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(true, r1.hasError());
}

TEST_MATH(PercentMul1) {
    Register r1(8);
    Register r2(8);

    r1.setChangedCallback(on_r1_changed);
    r2.setChangedCallback(on_r2_changed);

    // 99999999 * 5 % => 4999999.9
    setValue(r1, 5);
    setValue(r2, 99999999);
    Math::mulPercent(r1, r2);
    ASSERT_EQ(49999999, getIntValue(r1));
    ASSERT_EQ(1, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());

    // 99999999 * (-5) % => -4999999.9
    setValue(r1, -5);
    setValue(r2, 99999999);
    Math::mulPercent(r1, r2);
    ASSERT_EQ(-49999999, getIntValue(r1));
    ASSERT_EQ(1, r1.getPointPos());
    ASSERT_EQ(true, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());

    // -99999999 * 5 % => -4999999.9
    setValue(r1, 5);
    setValue(r2, -99999999);
    Math::mulPercent(r1, r2);
    ASSERT_EQ(-49999999, getIntValue(r1));
    ASSERT_EQ(1, r1.getPointPos());
    ASSERT_EQ(true, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());

    // -99999999 * (-5) % => 4999999.9
    setValue(r1, -5);
    setValue(r2, -99999999);
    Math::mulPercent(r1, r2);
    ASSERT_EQ(49999999, getIntValue(r1));
    ASSERT_EQ(1, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());
}

TEST_MATH(PercentMul2) {
    Register r1(8);
    Register r2(8);

    r1.setChangedCallback(on_r1_changed);
    r2.setChangedCallback(on_r2_changed);

    // 0.0000002 * 50 % => 0.0000001
    setValue(r1, 50);
    setValue(r2, 2, 7);
    Math::mulPercent(r1, r2);
    ASSERT_EQ(1, getIntValue(r1));
    ASSERT_EQ(7, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());
}

TEST_MATH(PercentDiv) {
    Register r1(8);
    Register r2(8);

    r1.setChangedCallback(on_r1_changed);
    r2.setChangedCallback(on_r2_changed);

    // 10 / 5 % => 200
    setValue(r1, 10);
    setValue(r2, 5);
    Math::divPercent(r1, r2);
    ASSERT_EQ(200, getIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.isNegative());
    ASSERT_EQ(false, r1.hasError());
}

TEST_MATH(PercentAdd) {
    Register r1(8);
    Register r2(8);

    r1.setChangedCallback(on_r1_changed);
    r2.setChangedCallback(on_r2_changed);

    // 200 + 5 % => 210
    setValue(r1, 200);
    setValue(r2, 5);
    Math::addPercent(r1, r2);
    ASSERT_EQ(210, getIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.hasError());

    // -200 + 5 % => -210
    setValue(r1, -200);
    setValue(r2, 5);
    Math::addPercent(r1, r2);
    ASSERT_EQ(-210, getIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.hasError());

    // -200 + (-5) % => -190
    setValue(r1, -200);
    setValue(r2, -5);
    Math::addPercent(r1, r2);
    ASSERT_EQ(-190, getIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.hasError());

    // 200 + (-5) % => 190
    setValue(r1, 200);
    setValue(r2, -5);
    Math::addPercent(r1, r2);
    ASSERT_EQ(190, getIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.hasError());
}

TEST_MATH(PercentSub) {
    Register r1(8);
    Register r2(8);

    r1.setChangedCallback(on_r1_changed);
    r2.setChangedCallback(on_r2_changed);

    // 200 - 5 % => 190
    setValue(r1, 200);
    setValue(r2, 5);
    Math::subPercent(r1, r2);
    ASSERT_EQ(190, getIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.hasError());

    // -200 - 5 % => -190
    setValue(r1, -200);
    setValue(r2, 5);
    Math::subPercent(r1, r2);
    ASSERT_EQ(-190, getIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.hasError());

    // -200 - (-5) % => -210
    setValue(r1, -200);
    setValue(r2, -5);
    Math::subPercent(r1, r2);
    ASSERT_EQ(-210, getIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.hasError());

    // 200 - (-5) % => 190
    setValue(r1, 200);
    setValue(r2, -5);
    Math::subPercent(r1, r2);
    ASSERT_EQ(210, getIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_EQ(false, r1.hasError());
}

TEST_MATH(SqrtInt) {
    Register r(8);

    r.setChangedCallback(on_r1_changed);

    setValue(r, 9);
    Math::sqrt(r);
    ASSERT_EQ(3, getIntValue(r));
    ASSERT_FALSE(r.hasError());

    setValue(r, 4);
    Math::sqrt(r);
    ASSERT_EQ(2, getIntValue(r));
    ASSERT_FALSE(r.hasError());

    setValue(r, 0);
    Math::sqrt(r);
    ASSERT_EQ(0, getIntValue(r));
    ASSERT_FALSE(r.hasError());

    setValue(r, -4);
    Math::sqrt(r);
    ASSERT_EQ(2, getIntValue(r));
    ASSERT_TRUE(r.hasError());

    setValue(r, -9);
    Math::sqrt(r);
    ASSERT_EQ(3, getIntValue(r));
    ASSERT_TRUE(r.hasError());
}

TEST_MATH(Sqrt) {
    Register r(8);
    Register h(16);
    Register g(16);

    r.setChangedCallback(on_r1_changed);
    h.setChangedCallback(on_r2_changed);
    g.setChangedCallback(on_r3_changed);

    // √4 = 2
    // √2 = 1.4142135
    setValue(r, 4);
    Math::sqrt(r, h, g);
    ASSERT_EQ(2, getIntValue(r));
    ASSERT_EQ(0, r.getPointPos());
    ASSERT_FALSE(r.isNegative());
    ASSERT_FALSE(r.hasError());
    Math::sqrt(r, h, g);
    ASSERT_EQ(14142135, getIntValue(r));
    ASSERT_EQ(7, r.getPointPos());
    ASSERT_FALSE(r.isNegative());
    ASSERT_FALSE(r.hasError());

    // √99999998 = 9999.9998
    // √9999.9998 = 99.999998
    setValue(r, 99999998);
    Math::sqrt(r, h, g);
    ASSERT_EQ(99999998, getIntValue(r));
    ASSERT_EQ(4, r.getPointPos());
    ASSERT_FALSE(r.isNegative());
    ASSERT_FALSE(r.hasError());
    Math::sqrt(r, h, g);
    ASSERT_EQ(99999998, getIntValue(r));
    ASSERT_EQ(6, r.getPointPos());
    ASSERT_FALSE(r.isNegative());
    ASSERT_FALSE(r.hasError());

    // √1.0000003 = 1.0000001
    // √1.0000001 = 1.
    setValue(r, 10000003, 7);
    Math::sqrt(r, h, g);
    ASSERT_EQ(10000001, getIntValue(r));
    ASSERT_EQ(7, r.getPointPos());
    ASSERT_FALSE(r.isNegative());
    ASSERT_FALSE(r.hasError());
    Math::sqrt(r, h, g);
    ASSERT_EQ(1, getIntValue(r));
    ASSERT_EQ(0, r.getPointPos());
    ASSERT_FALSE(r.isNegative());
    ASSERT_FALSE(r.hasError());
}

TEST_MATH(Mu) {
    Register r1(8);
    Register r2(8);

    r1.setChangedCallback(on_r1_changed);
    r2.setChangedCallback(on_r2_changed);

    // 200 mu 60 % => 500
    setValue(r1, 200);
    setValue(r2, 60);
    Math::muPercent(r1, r2);
    ASSERT_EQ(500, getIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_FALSE(r1.hasError());
    ASSERT_EQ(6, getIntValue(r2));
    ASSERT_EQ(1, r2.getPointPos());
    ASSERT_FALSE(r2.hasError());

    // -200 mu 60 % => -500
    setValue(r1, -200);
    setValue(r2, 60);
    Math::muPercent(r1, r2);
    ASSERT_EQ(-500, getIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_FALSE(r1.hasError());
    ASSERT_EQ(6, getIntValue(r2));
    ASSERT_EQ(1, r2.getPointPos());
    ASSERT_FALSE(r2.hasError());

    // 200 mu (-60) % => 125
    setValue(r1, 200);
    setValue(r2, -60);
    Math::muPercent(r1, r2);
    ASSERT_EQ(125, getIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_FALSE(r1.hasError());
    ASSERT_EQ(-6, getIntValue(r2));
    ASSERT_EQ(1, r2.getPointPos());
    ASSERT_FALSE(r2.hasError());

    // (-200) mu (-60) % => 125
    setValue(r1, -200);
    setValue(r2, -60);
    Math::muPercent(r1, r2);
    ASSERT_EQ(-125, getIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_FALSE(r1.hasError());
    ASSERT_EQ(-6, getIntValue(r2));
    ASSERT_EQ(1, r2.getPointPos());
    ASSERT_FALSE(r2.hasError());
}

TEST_MATH(MuError) {
    Register r1(8);
    Register r2(8);

    r1.setChangedCallback(on_r1_changed);
    r2.setChangedCallback(on_r2_changed);

    // 200 mu 100 % => [err] 0
    setValue(r1, 200);
    setValue(r2, 100);
    Math::muPercent(r1, r2);
    ASSERT_EQ(0, getIntValue(r1));
    ASSERT_EQ(0, r1.getPointPos());
    ASSERT_TRUE(r1.hasError());
    ASSERT_FALSE(r1.hasOverflow());
    ASSERT_EQ(1, getIntValue(r2));
    ASSERT_EQ(0, r2.getPointPos());
    ASSERT_FALSE(r2.hasError());
}