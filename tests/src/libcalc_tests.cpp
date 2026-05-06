/**
 * Calculator Comrade Library
 * License: https://github.com/DmitryDzz/calculator-comrade-lib/blob/master/LICENSE
 * Author: Dmitry Dzakhov
 * Email: info@robot-mitya.ru
 */
#include <gmock/gmock.h>

#include "calculator/libcalc.h"

TEST(TestLibCalcApi, TwoCalculators) {
    HCALC calc1;
    CalculatorResult result = CreateCalculator(8, 0, &calc1);
    ASSERT_EQ(CALC_OK, result);
    HCALC calc2;
    result = CreateCalculator(12, 0, &calc2);
    ASSERT_EQ(CALC_OK, result);

    uint8_t size1;
    result = GetSize(calc1, &size1);
    ASSERT_EQ(CALC_OK, result);
    ASSERT_EQ(8, size1);

    uint8_t size2;
    result = GetSize(calc2, &size2);
    ASSERT_EQ(CALC_OK, result);
    ASSERT_EQ(12, size2);

    DisposeAll();
    result = GetSize(calc1, &size1);
    ASSERT_EQ(CALC_ERR_NO_INSTANCE, result);
}

TEST(TestLibCalcApi, ManyCalculatorsAtTheSameTime) {
    HCALC hcalc;
    CalculatorResult result;
    for (uint16_t i = 0; i < 255; i++) {
        result = CreateCalculator(8, 0, &hcalc);
        ASSERT_EQ(CALC_OK, result);
    }

    result = CreateCalculator(8, 0, &hcalc);
    ASSERT_EQ(CALC_ERR_TOO_MANY_INSTANCES, result);

    DisposeAll();
}

TEST(TestLibCalcApi, ManyCalculatorsOneAfterAnother) {
    HCALC hcalc;
    for (int i = 0; i < 300; i++) {
        CalculatorResult result = CreateCalculator(8, 0, &hcalc);
        ASSERT_EQ(CALC_OK, result);
        result = DisposeCalculator(hcalc);
        ASSERT_EQ(CALC_OK, result);
    }
}
