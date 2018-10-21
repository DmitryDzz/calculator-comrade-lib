//
// Created by dmitrydzz on 08.10.18.
//

#ifndef CALCULATORCOMRADE_CALCULATOR_H
#define CALCULATORCOMRADE_CALCULATOR_H

#include "calculator/button.h"
#include "calculator/display_register.h"
#include "calculator/operation.h"
#include "calculator/state.h"

namespace calculatorcomrade {

    class Calculator {
    public:
        const static uint8_t DIGITS = 8;

        Calculator() : Calculator(DIGITS) {};
        explicit Calculator(uint8_t digits) : state_(digits), digits_(digits) {};

        State getState();
        void input(Button button);
        void input(const std::string& button);
    private:
        uint8_t digits_;
        State state_;

        Register& getDisplayedRegister();
        Button stringToButton(const std::string& button);

        void clearAll();
        void clearEntry();
    };
};

#endif //CALCULATORCOMRADE_CALCULATOR_H
