/**
 * Calculator Comrade Library
 * Copyright (c) 2019-2026 Dmitry Dzakhov (dmitrydzz)
 * SPDX-License-Identifier: MIT
 */
#ifndef CALCULATORCOMRADE_OPERATION_H
#define CALCULATORCOMRADE_OPERATION_H

#include "operation_codes.h"

namespace calculatorcomrade {

    enum class Operation : uint8_t {
        add = CALC_OPERATION_ADD,
        sub = CALC_OPERATION_SUB,
        mul = CALC_OPERATION_MUL,
        div = CALC_OPERATION_DIV,
        mu = CALC_OPERATION_MU
    };
}

#endif //CALCULATORCOMRADE_OPERATION_H
