/**
 * Calculator Comrade Library
 * License: https://github.com/DmitryDzz/calculator-comrade-lib/blob/master/LICENSE
 * Author: Dmitry Dzakhov
 * Email: info@robot-mitya.ru
 */
#ifndef CALCULATORCOMRADE_CONFIG_H
#define CALCULATORCOMRADE_CONFIG_H

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

        static constexpr CalcOptions OPTION_TRUNC_ZEROS_ON_OVERFLOW = 0b00000001;
        // See test MemTruncsX for explanation of OPTION_MEM_CAN_TRUNC_X.
        static constexpr CalcOptions OPTION_MEM_CAN_TRUNC_X = 0b00000010;

        //    static constexpr CalcOptions OPTIONS_DEFAULT = 0;
        //    static constexpr CalcOptions OPTIONS_DEFAULT = OPTION_TRUNC_ZEROS_ON_OVERFLOW | OPTION_MEM_CAN_TRUNC_X;
        static constexpr CalcOptions OPTIONS_DEFAULT = OPTION_MEM_CAN_TRUNC_X;
    };
}

#endif //CALCULATORCOMRADE_CONFIG_H
