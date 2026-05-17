/**
 * Calculator Comrade Library
 * Copyright (c) 2019-2026 Dmitry Dzakhov (dmitrydzz)
 * SPDX-License-Identifier: MIT
 */
#ifndef CALCULATORCOMRADE_CALC_HELPER_HPP
#define CALCULATORCOMRADE_CALC_HELPER_HPP

#include <string>
#include "calculator/register.h"

namespace calculatorcomrade {

    CalcInt getAbsIntValue(Register &r);

    CalcInt getIntValue(Register &r);

    void setValue(Register &r, CalcInt value);

    void setValue(Register &r, CalcInt value, CalcInt digitsAfterPoint);

    void evaluateText(Register &r, std::string *output);
}

#endif //CALCULATORCOMRADE_CALC_HELPER_HPP
