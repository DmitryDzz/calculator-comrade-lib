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
        explicit Calculator(uint8_t digits) : state_(digits), digits_(digits), hasOperation_(false), inNumber_(false) {};

        State& getState();
        void input(Button button);
        void input(const std::string& button);
    private:
        uint8_t digits_;
        State state_;
        bool hasOperation_;
        bool inNumber_;

        Button stringToButton(const std::string& button);

        uint8_t inputSize_ = 0;
        bool inputHasPoint_ = false;
        void clearInput();
        void inputDigit(uint8_t digit);
        void inputPoint();
        void shiftLeftOnInput();

        void calculateEquals();
        void calculateAddSubMulDiv();
    };
};

#endif //CALCULATORCOMRADE_CALCULATOR_H
