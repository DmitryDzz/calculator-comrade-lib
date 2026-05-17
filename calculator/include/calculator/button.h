/**
 * Calculator Comrade Library
 * Copyright (c) 2019-2026 Dmitry Dzakhov (dmitrydzz)
 * SPDX-License-Identifier: MIT
 */
#ifndef CALCULATORCOMRADE_BUTTON_H
#define CALCULATORCOMRADE_BUTTON_H

#include "calculator/button_codes.h"

namespace calculatorcomrade {

    enum class Button : uint8_t {
        none = CALC_BUTTON_NONE,
        ca = CALC_BUTTON_CA,                // clear all
        ce = CALC_BUTTON_CE,                // clear entry
        ceca = CALC_BUTTON_CECA,            // clear entry, clear all
        d0 = CALC_BUTTON_D0,
        d1 = CALC_BUTTON_D1,
        d2 = CALC_BUTTON_D2,
        d3 = CALC_BUTTON_D3,
        d4 = CALC_BUTTON_D4,
        d5 = CALC_BUTTON_D5,
        d6 = CALC_BUTTON_D6,
        d7 = CALC_BUTTON_D7,
        d8 = CALC_BUTTON_D8,
        d9 = CALC_BUTTON_D9,
        point = CALC_BUTTON_POINT,
        plus = CALC_BUTTON_PLUS,
        minus = CALC_BUTTON_MINUS,
        changeSign = CALC_BUTTON_CHANGESIGN,
        mul = CALC_BUTTON_MUL,
        div = CALC_BUTTON_DIV,
        mu = CALC_BUTTON_MU,
        sqrt = CALC_BUTTON_SQRT,
        percent = CALC_BUTTON_PERCENT,
        equals = CALC_BUTTON_EQUALS,
        memPlus = CALC_BUTTON_MEMPLUS,      // M+
        memMinus = CALC_BUTTON_MEMMINUS,    // M-
        memR = CALC_BUTTON_MEMR,            // memory restore
        memC = CALC_BUTTON_MEMC,            // memory clean
        memRC = CALC_BUTTON_MEMRC           // memory restore, memory clean
    };
}

#endif //CALCULATORCOMRADE_BUTTON_H
