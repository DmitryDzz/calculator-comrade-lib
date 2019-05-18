//
// Created by dmitrydzz on 11.01.19.
//

#ifndef CALCULATORCOMRADE_CALC_HELPER_HPP
#define CALCULATORCOMRADE_CALC_HELPER_HPP

#include <cstdint>
#include <string>
#include "calculator/register.h"
#include "calculator/button.h"

namespace calculatorcomrade {

    int64_t getAbsIntValue(Register &r);

    int64_t getIntValue(Register &r);

    void setValue(Register &r, int64_t value);

    void setValue(Register &r, int64_t value, int8_t digitsAfterPoint);

    void evaluateText(Register &r, std::string *output);
}

#endif //CALCULATORCOMRADE_CALC_HELPER_HPP
