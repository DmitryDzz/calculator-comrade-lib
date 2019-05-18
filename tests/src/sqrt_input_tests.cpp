//
// Created by dmitrydzz on 11.02.2019.
//

#include <gmock/gmock.h>

#include "calculator/calculator.h"
#include "calc_helper.h"

using namespace calculatorcomrade;

#define TEST_SQRT(test_name) TEST(TestSqrt, test_name)

TEST_SQRT(SqrtRegularOperations) {
    Calculator c(8);
    Register &x = c.getX();
    Register &y= c.getY();

    c.input(Button::ca);
    c.input(Button::d9);
    c.input(Button::sqrt);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());

    // 5 + 9 √ =  =>  8
    // =  =>  11
    c.input(Button::ca);
    c.input(Button::d5);
    c.input(Button::plus);
    c.input(Button::d9);
    ASSERT_EQ(9, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(5, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    c.input(Button::sqrt);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_EQ(5, getIntValue(y));
    ASSERT_EQ(0, y.getPointPos());
    c.input(Button::equals);
    ASSERT_EQ(8, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    c.input(Button::equals);
    ASSERT_EQ(11, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());

    // 5 - 9 √ =  =>  2
    // =  =>  -1
    c.input(Button::ca);
    c.input(Button::d5);
    c.input(Button::minus);
    c.input(Button::d9);
    c.input(Button::sqrt);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    c.input(Button::equals);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    c.input(Button::equals);
    ASSERT_EQ(-1, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());

    // 2 * 9 √ =  =>  6
    // =  =>  12
    c.input(Button::ca);
    c.input(Button::d2);
    c.input(Button::mul);
    c.input(Button::d9);
    c.input(Button::sqrt);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    c.input(Button::equals);
    ASSERT_EQ(6, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    c.input(Button::equals);
    ASSERT_EQ(12, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());

    // 27 / 9 √ =  =>  9
    // =  =>  3
    c.input(Button::ca);
    c.input(Button::d2);
    c.input(Button::d7);
    c.input(Button::div);
    c.input(Button::d9);
    c.input(Button::sqrt);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    c.input(Button::equals);
    ASSERT_EQ(9, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    c.input(Button::equals);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
}

TEST_SQRT(SqrtFakeNegative) {
    Calculator c(8);
    Register &x = c.getX();

    c.input(Button::minus);
    c.input(Button::d9);
    c.input(Button::sqrt);
    ASSERT_EQ(3, getIntValue(x));
    c.input(Button::equals);
    ASSERT_EQ(-3, getIntValue(x));
    c.input(Button::equals);
    ASSERT_EQ(-6, getIntValue(x));
}

TEST_SQRT(SqrtAfterOperator1) {
    Calculator c(8);
    Register &x = c.getX();

    // 9 + √  =>  3
    // =  =>  12
    // =  =>  15
    c.input(Button::ca);
    c.input(Button::d9);
    c.input(Button::plus);
    c.input(Button::sqrt);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    c.input(Button::equals);
    ASSERT_EQ(12, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    c.input(Button::equals);
    ASSERT_EQ(15, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());

    // 9 - √  =>  3
    // =  =>  6
    // =  =>  3
    c.input(Button::ca);
    c.input(Button::d9);
    c.input(Button::minus);
    c.input(Button::sqrt);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    c.input(Button::equals);
    ASSERT_EQ(6, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    c.input(Button::equals);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());

    // 9 * √  =>  3
    // =  =>  27
    // =  =>  243
    c.input(Button::ca);
    c.input(Button::d9);
    c.input(Button::mul);
    c.input(Button::sqrt);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    c.input(Button::equals);
    ASSERT_EQ(27, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    c.input(Button::equals);
    ASSERT_EQ(243, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());

    // 9 / √  =>  3
    // =  =>  3
    // =  =>  1
    c.input(Button::ca);
    c.input(Button::d9);
    c.input(Button::div);
    c.input(Button::sqrt);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    c.input(Button::equals);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    c.input(Button::equals);
    ASSERT_EQ(1, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
}

TEST_SQRT(SqrtAfterOperator2) {
    Calculator c(8);
    Register &x = c.getX();
    Register &y = c.getY();

    // 5 + 9 √ 2  =>  2
    // =  =>  7
    // =  =>  9
    c.input(Button::ca);
    c.input(Button::d5);
    c.input(Button::plus);
    c.input(Button::d9);
    c.input(Button::sqrt);
    c.input(Button::d2);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(5, getIntValue(y));
    c.input(Button::equals);
    ASSERT_EQ(7, getIntValue(x));
    ASSERT_EQ(2, getIntValue(y));
    c.input(Button::equals);
    ASSERT_EQ(9, getIntValue(x));
    ASSERT_EQ(2, getIntValue(y));

    // 5 - 9 √ 2  =>  2
    // =  =>  3
    // =  =>  1
    c.input(Button::ca);
    c.input(Button::d5);
    c.input(Button::minus);
    c.input(Button::d9);
    c.input(Button::sqrt);
    c.input(Button::d2);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(5, getIntValue(y));
    c.input(Button::equals);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(2, getIntValue(y));
    c.input(Button::equals);
    ASSERT_EQ(1, getIntValue(x));
    ASSERT_EQ(2, getIntValue(y));

    // 2 * 9 √ 4  =>  4
    // =  =>  8
    // =  =>  16
    c.input(Button::ca);
    c.input(Button::d2);
    c.input(Button::mul);
    c.input(Button::d9);
    c.input(Button::sqrt);
    c.input(Button::d4);
    ASSERT_EQ(4, getIntValue(x));
    ASSERT_EQ(2, getIntValue(y));
    c.input(Button::equals);
    ASSERT_EQ(8, getIntValue(x));
    ASSERT_EQ(2, getIntValue(y));
    c.input(Button::equals);
    ASSERT_EQ(16, getIntValue(x));
    ASSERT_EQ(2, getIntValue(y));

    // 8 / 9 √ 2  =>  2
    // =  =>  4
    // =  =>  2
    c.input(Button::ca);
    c.input(Button::d8);
    c.input(Button::div);
    c.input(Button::d9);
    c.input(Button::sqrt);
    c.input(Button::d2);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(8, getIntValue(y));
    c.input(Button::equals);
    ASSERT_EQ(4, getIntValue(x));
    ASSERT_EQ(2, getIntValue(y));
    c.input(Button::equals);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(2, getIntValue(y));
}

TEST_SQRT(SqrtAfterOperation) {
    Calculator c(8);
    Register &x = c.getX();

    // 2 + 7 + √  =>  3
    // =  =>  12
    // =  =>  15
    c.input(Button::ca);
    c.input(Button::d2);
    c.input(Button::plus);
    c.input(Button::d7);
    c.input(Button::plus);
    c.input(Button::sqrt);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    c.input(Button::equals);
    ASSERT_EQ(12, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    c.input(Button::equals);
    ASSERT_EQ(15, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());

    // 12 - 3 - √  =>  3
    // =  =>  6
    // =  =>  3
    c.input(Button::ca);
    c.input(Button::d1);
    c.input(Button::d2);
    c.input(Button::minus);
    c.input(Button::d3);
    c.input(Button::minus);
    c.input(Button::sqrt);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    c.input(Button::equals);
    ASSERT_EQ(6, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    c.input(Button::equals);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());

    // 2 * 2 * √  =>  2
    // =  =>  8
    // =  =>  32
    c.input(Button::ca);
    c.input(Button::d2);
    c.input(Button::mul);
    c.input(Button::d2);
    c.input(Button::mul);
    c.input(Button::sqrt);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    c.input(Button::equals);
    ASSERT_EQ(8, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    c.input(Button::equals);
    ASSERT_EQ(32, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());

    // 27 / 3 / √  =>  3
    // =  =>  3
    // =  =>  1
    c.input(Button::ca);
    c.input(Button::d2);
    c.input(Button::d7);
    c.input(Button::div);
    c.input(Button::d3);
    c.input(Button::div);
    c.input(Button::sqrt);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    c.input(Button::equals);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    c.input(Button::equals);
    ASSERT_EQ(1, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
}

TEST_SQRT(AfterSqrt1) {
    Calculator c(8);
    Register &x = c.getX();
    Register &y = c.getY();

    c.input(Button::d4);
    c.input(Button::sqrt);
    ASSERT_EQ(2, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    c.input(Button::d1);
    ASSERT_EQ(1, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    c.input(Button::equals);
    ASSERT_EQ(1, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
}

TEST_SQRT(AfterSqrt2) {
    Calculator c(8);
    Register &x = c.getX();
    Register &y = c.getY();

    c.input(Button::d8);
    c.input(Button::sqrt);
    ASSERT_EQ(28284271, getIntValue(x));
    ASSERT_EQ(7, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    c.input(Button::d9);
    ASSERT_EQ(9, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    c.input(Button::equals);
    ASSERT_EQ(9, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
}

TEST_SQRT(AfterSqrt3) {
    Calculator c(8);
    Register &x = c.getX();
    Register &y = c.getY();

    c.input(Button::d8);
    c.input(Button::d1);
    c.input(Button::sqrt);
    ASSERT_EQ(9, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    c.input(Button::sqrt);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    c.input(Button::sqrt);
    ASSERT_EQ(17320508, getIntValue(x));
    ASSERT_EQ(7, x.getPointPos());
    ASSERT_TRUE(y.isZero());
    c.input(Button::d9);
    ASSERT_EQ(9, getIntValue(x));
    ASSERT_EQ(0, x.getPointPos());
    ASSERT_TRUE(y.isZero());
}

TEST_SQRT(CeCaAfterOperationAndSqrt) {
    Calculator c(8);
    Register &x = c.getX();
    Register &y = c.getY();

    c.input(Button::d2);
    c.input(Button::plus);
    c.input(Button::d9);
    ASSERT_EQ(9, getIntValue(x));
    ASSERT_EQ(2, getIntValue(y));
    c.input(Button::sqrt);
    ASSERT_EQ(3, getIntValue(x));
    ASSERT_EQ(2, getIntValue(y));
    c.input(Button::ceca);
    ASSERT_TRUE(x.isZero());
    ASSERT_EQ(2, getIntValue(y));
    c.input(Button::ceca);
    ASSERT_TRUE(x.isZero());
    ASSERT_TRUE(y.isZero());
}