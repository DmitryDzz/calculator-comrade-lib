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
        Calculator() : Calculator(Config::DEFAULT_SIZE) {};
        explicit Calculator(int8_t size) :
                state_(size),
                size_(size),
                hasOperation_(false),
                inNumber_(false),
                inputSize_(0),
                inputHasPoint_(false) {
            assert(size > 0);
            assert(size <= Config::MAX_SIZE);
        };

        State& getState();
        void input(Button button);
    private:
        int8_t size_;
        State state_;
        bool hasOperation_;
        bool inNumber_;

        int8_t inputSize_;
        bool inputHasPoint_;
        void clearInput();
        void inputDigit(int8_t digit);
        void inputPoint();
        void shiftLeftOnInput();

        void calculateEquals();
        void calculateAddSubMulDiv();
        void calculatePercent();
    };
};

#endif //CALCULATORCOMRADE_CALCULATOR_H
