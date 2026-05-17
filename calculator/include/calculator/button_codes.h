/**
 * Calculator Comrade Library
 * Copyright (c) 2019-2026 Dmitry Dzakhov (dmitrydzz)
 * SPDX-License-Identifier: MIT
 */
#ifndef CALCULATORCOMRADE_BUTTON_CODES_H
#define CALCULATORCOMRADE_BUTTON_CODES_H

#ifdef __cplusplus
#include <cstdint>
using CalculatorButtonCode = std::uint8_t;
#else
#include <stdint.h>
typedef uint8_t CalculatorButtonCode;
#endif

#ifdef __cplusplus
enum : CalculatorButtonCode {
#else
enum {
#endif
    CALC_BUTTON_NONE = 0,
    CALC_BUTTON_CA = 1,         // clear all
    CALC_BUTTON_CE = 2,         // clear entry
    CALC_BUTTON_CECA = 3,       // clear entry, clear all
    CALC_BUTTON_D0 = 4,
    CALC_BUTTON_D1 = 5,
    CALC_BUTTON_D2 = 6,
    CALC_BUTTON_D3 = 7,
    CALC_BUTTON_D4 = 8,
    CALC_BUTTON_D5 = 9,
    CALC_BUTTON_D6 = 10,
    CALC_BUTTON_D7 = 11,
    CALC_BUTTON_D8 = 12,
    CALC_BUTTON_D9 = 13,
    CALC_BUTTON_POINT = 14,
    CALC_BUTTON_PLUS = 15,
    CALC_BUTTON_MINUS = 16,
    CALC_BUTTON_CHANGESIGN = 17,
    CALC_BUTTON_MUL = 18,
    CALC_BUTTON_DIV = 19,
    CALC_BUTTON_MU = 20,
    CALC_BUTTON_SQRT = 21,
    CALC_BUTTON_PERCENT = 22,
    CALC_BUTTON_EQUALS = 23,
    CALC_BUTTON_MEMPLUS = 24,   // M+
    CALC_BUTTON_MEMMINUS = 25,  // M-
    CALC_BUTTON_MEMR = 26,      // memory restore
    CALC_BUTTON_MEMC = 27,      // memory clean
    CALC_BUTTON_MEMRC = 28      // memory restore, memory clean
};

#endif //CALCULATORCOMRADE_BUTTON_CODES_H
