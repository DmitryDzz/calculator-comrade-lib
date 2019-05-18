//
// Created by dmitrydzz on 04.02.19.
//

#include <gmock/gmock.h>

#include "calculator/calculator.h"
#include "calculator/button.h"
#include "calculator/operation.h"
#include "calc_helper.h"

using namespace calculatorcomrade;

#define TEST_PERCENT(test_name) TEST(PercentOperations, test_name)

TEST_PERCENT(NoOperation) {
    Calculator c(8);
    Register &x = c.getX();
    c.input(Button::d5);
    c.input(Button::percent);
    ASSERT_EQ(5, getIntValue(x));
}

TEST_PERCENT(AddPercent) {
    Calculator c(8);
    Register &x = c.getX();

    c.input(Button::ca);
    c.input(Button::d2);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::plus);
    c.input(Button::d5);
    c.input(Button::percent);
    ASSERT_EQ(210, getIntValue(x));
    c.input(Button::percent);
    ASSERT_EQ(210, getIntValue(x));
    c.input(Button::equals);
    ASSERT_EQ(410, getIntValue(x));

    c.input(Button::ca);
    c.input(Button::minus);
    c.input(Button::d2);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::plus);
    c.input(Button::d5);
    c.input(Button::percent);
    ASSERT_EQ(-210, getIntValue(x));
    c.input(Button::percent);
    ASSERT_EQ(-210, getIntValue(x));
    c.input(Button::equals);
    ASSERT_EQ(-410, getIntValue(x));

    c.input(Button::ca);
    c.input(Button::d2);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::plus);
    c.input(Button::d5);
    c.input(Button::changeSign);
    c.input(Button::percent);
    ASSERT_EQ(190, getIntValue(x));
    c.input(Button::percent);
    ASSERT_EQ(190, getIntValue(x));
    c.input(Button::equals);
    ASSERT_EQ(-10, getIntValue(x));

    c.input(Button::ca);
    c.input(Button::minus);
    c.input(Button::d2);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::plus);
    c.input(Button::d5);
    c.input(Button::changeSign);
    c.input(Button::percent);
    ASSERT_EQ(-190, getIntValue(x));
    c.input(Button::percent);
    ASSERT_EQ(-190, getIntValue(x));
    c.input(Button::equals);
    ASSERT_EQ(10, getIntValue(x));
}

TEST_PERCENT(SubPercent) {
    Calculator c(8);
    Register &x = c.getX();

    c.input(Button::ca);
    c.input(Button::d2);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::minus);
    c.input(Button::d5);
    c.input(Button::percent);
    ASSERT_EQ(190, getIntValue(x));
    c.input(Button::percent);
    ASSERT_EQ(190, getIntValue(x));
    c.input(Button::equals);
    ASSERT_EQ(-10, getIntValue(x));

    c.input(Button::ca);
    c.input(Button::minus);
    c.input(Button::d2);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::minus);
    c.input(Button::d5);
    c.input(Button::percent);
    ASSERT_EQ(-190, getIntValue(x));
    c.input(Button::percent);
    ASSERT_EQ(-190, getIntValue(x));
    c.input(Button::equals);
    ASSERT_EQ(10, getIntValue(x));

    c.input(Button::ca);
    c.input(Button::d2);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::minus);
    c.input(Button::d5);
    c.input(Button::changeSign);
    c.input(Button::percent);
    ASSERT_EQ(210, getIntValue(x));
    c.input(Button::percent);
    ASSERT_EQ(210, getIntValue(x));
    c.input(Button::equals);
    ASSERT_EQ(410, getIntValue(x));

    c.input(Button::ca);
    c.input(Button::minus);
    c.input(Button::d2);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::minus);
    c.input(Button::d5);
    c.input(Button::changeSign);
    c.input(Button::percent);
    ASSERT_EQ(-210, getIntValue(x));
    c.input(Button::percent);
    ASSERT_EQ(-210, getIntValue(x));
    c.input(Button::equals);
    ASSERT_EQ(-410, getIntValue(x));
}

TEST_PERCENT(MulPercent) {
    Calculator c(8);
    Register &x = c.getX();
    Register &y = c.getY();

    c.input(Button::ca);
    c.input(Button::d2);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::mul);
    c.input(Button::d5);
    c.input(Button::percent);
    ASSERT_EQ(10, getIntValue(x));
    ASSERT_EQ(200, getIntValue(y));
    c.input(Button::percent);
    ASSERT_EQ(20, getIntValue(x));
    ASSERT_EQ(200, getIntValue(y));
    c.input(Button::equals);
    ASSERT_EQ(4000, getIntValue(x));
    ASSERT_EQ(200, getIntValue(y));

    c.input(Button::ca);
    c.input(Button::minus);
    c.input(Button::d2);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::mul);
    c.input(Button::d5);
    c.input(Button::percent);
    ASSERT_EQ(-10, getIntValue(x));
    ASSERT_EQ(-200, getIntValue(y));
    c.input(Button::percent);
    ASSERT_EQ(20, getIntValue(x));
    ASSERT_EQ(-200, getIntValue(y));
    c.input(Button::equals);
    ASSERT_EQ(-4000, getIntValue(x));
    ASSERT_EQ(-200, getIntValue(y));

    c.input(Button::ca);
    c.input(Button::d2);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::mul);
    c.input(Button::d5);
    c.input(Button::changeSign);
    c.input(Button::percent);
    ASSERT_EQ(-10, getIntValue(x));
    ASSERT_EQ(200, getIntValue(y));
    c.input(Button::percent);
    ASSERT_EQ(-20, getIntValue(x));
    ASSERT_EQ(200, getIntValue(y));
    c.input(Button::equals);
    ASSERT_EQ(-4000, getIntValue(x));
    ASSERT_EQ(200, getIntValue(y));

    c.input(Button::ca);
    c.input(Button::minus);
    c.input(Button::d2);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::mul);
    c.input(Button::d5);
    c.input(Button::changeSign);
    c.input(Button::percent);
    ASSERT_EQ(10, getIntValue(x));
    ASSERT_EQ(-200, getIntValue(y));
    c.input(Button::percent);
    ASSERT_EQ(-20, getIntValue(x));
    ASSERT_EQ(-200, getIntValue(y));
    c.input(Button::equals);
    ASSERT_EQ(4000, getIntValue(x));
    ASSERT_EQ(-200, getIntValue(y));
}

TEST_PERCENT(DivPercent1) {
    Calculator c(8);
    Register &x = c.getX();
    Register &y = c.getY();

    c.input(Button::ca);
    c.input(Button::d2);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::div);
    c.input(Button::d5);
    c.input(Button::percent);
    ASSERT_EQ(4000, getIntValue(x));
    ASSERT_EQ(5, getIntValue(y));
    c.input(Button::percent);
    ASSERT_EQ(80000, getIntValue(x));
    ASSERT_EQ(5, getIntValue(y));
    c.input(Button::equals);
    ASSERT_EQ(16000, getIntValue(x));
    ASSERT_EQ(5, getIntValue(y));

    c.input(Button::ca);
    c.input(Button::d2);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::div);
    c.input(Button::d5);
    c.input(Button::changeSign);
    c.input(Button::percent);
    ASSERT_EQ(-4000, getIntValue(x));
    ASSERT_EQ(-5, getIntValue(y));
    c.input(Button::percent);
    ASSERT_EQ(80000, getIntValue(x));
    ASSERT_EQ(-5, getIntValue(y));
    c.input(Button::equals);
    ASSERT_EQ(-16000, getIntValue(x));
    ASSERT_EQ(-5, getIntValue(y));

    c.input(Button::ca);
    c.input(Button::minus);
    c.input(Button::d2);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::div);
    c.input(Button::d5);
    c.input(Button::percent);
    ASSERT_EQ(-4000, getIntValue(x));
    ASSERT_EQ(5, getIntValue(y));
    c.input(Button::percent);
    ASSERT_EQ(-80000, getIntValue(x));
    ASSERT_EQ(5, getIntValue(y));
    c.input(Button::equals);
    ASSERT_EQ(-16000, getIntValue(x));
    ASSERT_EQ(5, getIntValue(y));

    c.input(Button::ca);
    c.input(Button::minus);
    c.input(Button::d2);
    c.input(Button::d0);
    c.input(Button::d0);
    c.input(Button::div);
    c.input(Button::d5);
    c.input(Button::changeSign);
    c.input(Button::percent);
    ASSERT_EQ(4000, getIntValue(x));
    ASSERT_EQ(-5, getIntValue(y));
    c.input(Button::percent);
    ASSERT_EQ(-80000, getIntValue(x));
    ASSERT_EQ(-5, getIntValue(y));
    c.input(Button::equals);
    ASSERT_EQ(16000, getIntValue(x));
    ASSERT_EQ(-5, getIntValue(y));
}
