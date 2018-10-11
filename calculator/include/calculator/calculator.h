//
// Created by dmitrydzz on 08.10.18.
//

#ifndef CALCULATORCOMRADE_CALCULATOR_H
#define CALCULATORCOMRADE_CALCULATOR_H

#include "calculator/state.h"
#include "calculator/button.h"
#include "calculator/operation.h"
#include "calculator/display_register.h"

namespace calculatorcomrade {

    class Calculator {
    public:
        Calculator() = default;
        Calculator(int digits) : digits_(digits) {};

        State getState();
        void input(Button button);
    private:
        int digits_ = 8;
        State state_;

        void clearAll();
        void clearEntry();
        void inputDigit(int digit);
    };
};

#endif //CALCULATORCOMRADE_CALCULATOR_H
