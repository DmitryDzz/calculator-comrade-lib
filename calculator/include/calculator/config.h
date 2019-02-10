//
// Created by dmitrydzz on 14.10.18.
//

#ifndef CALCULATORCOMRADE_CONFIG_H
#define CALCULATORCOMRADE_CONFIG_H

#include <stdint.h>

class Config {
public:
    static const int8_t MAX_SIZE = 16;
    static const int8_t DEFAULT_SIZE = 8;

    static const uint8_t OPTION_TRUNC_ZEROS_ON_OVERFLOW = 1;
    // See test MemTruncsX for explanation of OPTION_MEM_CAN_TRUNC_X.
    static const uint8_t OPTION_MEM_CAN_TRUNC_X = 2;

//    static const uint8_t OPTIONS_DEFAULT = 0;
//    static const uint8_t OPTIONS_DEFAULT = OPTION_TRUNC_ZEROS_ON_OVERFLOW | OPTION_MEM_CAN_TRUNC_X;
    static const uint8_t OPTIONS_DEFAULT = OPTION_MEM_CAN_TRUNC_X;
};

#endif //CALCULATORCOMRADE_CONFIG_H
