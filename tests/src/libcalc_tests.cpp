//
// Created by dmitrydzz on 29.01.2019.
//

#include <gmock/gmock.h>

#include "calculator/libcalc.h"

TEST(TestLibCalcApi, TwoCalculators) {
    HCALC calc1;
    HRES hr = CreateCalculator(8, 0, &calc1);
    ASSERT_EQ(HRES_OK, hr);
    HCALC calc2;
    hr = CreateCalculator(12, 0, &calc2);
    ASSERT_EQ(HRES_OK, hr);

    int8_t size1;
    hr = GetSize(calc1, &size1);
    ASSERT_EQ(HRES_OK, hr);
    ASSERT_EQ(8, size1);

    int8_t size2;
    hr = GetSize(calc2, &size2);
    ASSERT_EQ(HRES_OK, hr);
    ASSERT_EQ(12, size2);

    DisposeAll();
    hr = GetSize(calc1, &size1);
    ASSERT_EQ(HRES_ERR_NO_INSTANCE, hr);
}

TEST(TestLibCalcApi, ManyCalculators) {
    HCALC hcalc;
    HRES hr;
    for (uint16_t i = 0; i < 255; i++) {
        hr = CreateCalculator(8, 0, &hcalc);
        ASSERT_EQ(HRES_OK, hr);
    }

    hr = CreateCalculator(8, 0, &hcalc);
    ASSERT_EQ(HRES_ERR_TOO_MANY_INSTANCES, hr);

    DisposeAll();
}
