/**
 * Calculator Comrade Library
 * Copyright (c) 2019-2026 Dmitry Dzakhov (dmitrydzz)
 * SPDX-License-Identifier: MIT
 */
#ifndef CALCULATORCOMRADE_OPERATION_CODES_H
#define CALCULATORCOMRADE_OPERATION_CODES_H

#ifdef __cplusplus
    #include <cstdint>
    using CalculatorOperationCode = std::uint8_t;
#else
    #include <stdint.h>
    typedef uint8_t CalculatorOperationCode;
#endif

#ifdef __cplusplus
enum : CalculatorOperationCode {
#else
enum {
#endif
    CALC_OPERATION_ADD = 0,
    CALC_OPERATION_SUB = 1,
    CALC_OPERATION_MUL = 2,
    CALC_OPERATION_DIV = 3,
    CALC_OPERATION_MU = 4
};

#endif //CALCULATORCOMRADE_OPERATION_CODES_H
