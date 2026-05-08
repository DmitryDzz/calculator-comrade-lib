/**
 * Calculator Comrade Library
 * License: https://github.com/DmitryDzz/calculator-comrade-lib/blob/master/LICENSE
 * Author: Dmitry Dzakhov
 * Email: info@robot-mitya.ru
 */
#ifndef CALCULATORCOMRADE_CONFIG_H
#define CALCULATORCOMRADE_CONFIG_H

#include "calculator/option_codes.h"
#include "calculator/types.h"

namespace calculatorcomrade {

    class Config {
    public:
        // MU operator requires at least 3 digits to store value 100 (%) in register.
        // So min size of registers is limited by 3.
        static constexpr CalcInt MIN_SIZE = 3;
        static constexpr CalcInt MAX_SIZE = 16;
        static constexpr CalcInt DEFAULT_SIZE = 8;

        static constexpr uint8_t DUMP_VERSION = 1;

        static constexpr CalcOptions OPTION_TRUNC_ZEROS_ON_OVERFLOW = CALC_OPTION_TRUNC_ZEROS_ON_OVERFLOW;
        static constexpr CalcOptions OPTION_MEMORY_OVERFLOW_CLEARS_X = CALC_OPTION_MEMORY_OVERFLOW_CLEARS_X;
        static constexpr CalcOptions OPTIONS_DEFAULT = CALC_OPTIONS_DEFAULT;
    };
}

#endif //CALCULATORCOMRADE_CONFIG_H
