//
// Created by dmitrydzz on 18.10.18.
//

#include <gmock/gmock.h>
#include "json.hpp"

#include "calculator/calculator.h"
#include "calculator/state.h"
#include "calculator/button.h"
#include "calculator/operation.h"

using calculatorcomrade::Calculator;
using calculatorcomrade::State;
using calculatorcomrade::Button;
using calculatorcomrade::Operation;

#define TEST_STATE(test_name) TEST(TestState, test_name)

TEST_STATE(First) {
    int x = 5;
    EXPECT_EQ(5, x);
}