//
// Created by dmitrydzz on 08.10.18.
//

#ifndef CALCULATORCOMRADE_CALCULATOR_H
#define CALCULATORCOMRADE_CALCULATOR_H

#include "calculator/config.h"
#include "calculator/button.h"
#include "calculator/operation.h"
#include "calculator/state.h"

namespace calculatorcomrade {

    class Calculator {
    public:
        const static int8_t DIGITS = 8;

        Calculator() : Calculator(DIGITS) {};
        explicit Calculator(int8_t digits) :
                state_(digits),
                digits_(digits),
                hasOperation_(false),
                inNumber_(false),
                inputSize_(0),
                inputHasPoint_(false) {
            assert(digits > 0);
            assert(digits <= Config::MAX_DIGITS);
        };

        State& getState();
        void input(Button button);
        void input(const std::string& button);
    private:
        int8_t digits_;
        State state_;
        bool hasOperation_;
        bool inNumber_;

        Button stringToButton(const std::string& button);

        int8_t inputSize_;
        bool inputHasPoint_;
        void clearInput();
        void inputDigit(int8_t digit);
        void inputPoint();
        void shiftLeftOnInput();

        void calculateEquals();
        void calculateAddSubMulDiv();
    };
};

#endif //CALCULATORCOMRADE_CALCULATOR_H
