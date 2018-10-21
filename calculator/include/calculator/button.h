//
// Created by dmitrydzz on 08.10.18.
//

#ifndef CALCULATORCOMRADE_BUTTON_H
#define CALCULATORCOMRADE_BUTTON_H

namespace calculatorcomrade {

    enum class Button {
        none,
        ca,         // clear all
        ce,         // clear entry
        d0,
        d1,
        d2,
        d3,
        d4,
        d5,
        d6,
        d7,
        d8,
        d9,
        point,
        plus,
        minus,
        mul,
        div,
        sqrt,
        percent,
        equals,
        memPlus,    // M+
        memMinus,   // M-
        memR,       // memory restore
        memC        // memory clean
    };
}

#endif //CALCULATORCOMRADE_BUTTON_H
