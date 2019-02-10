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

    using DisplayEventCallback = void (*) ();

    class Calculator {
    public:
        explicit Calculator() : Calculator(Config::DEFAULT_SIZE, 0) {};
        explicit Calculator(int8_t size) : Calculator(size, 0) {};
        explicit Calculator(int8_t size, uint8_t options) :
                options_(options),
                state_(size),
                size_(size),
                lastButton_(Button::none),
                lastButtonWasCe_(false),
                hasOperation_(false),
                inNumber_(false),
                displayEventCallback_(nullptr),
                inputSize_(0),
                inputHasPoint_(false) {
            assert(size > 0);
            assert(size <= Config::MAX_SIZE);
        };

        int8_t getSize() { return size_; }
        uint8_t getOptions() { return options_; }
        void setOptions(uint8_t options) { options_ = options; }
        void setDisplayEventCallback(DisplayEventCallback callback);
        State& getState();
        void input(Button button);
    private:
        uint8_t options_;
        int8_t size_;
        State state_;
        Button lastButton_;
        bool lastButtonWasCe_;
        bool hasOperation_;
        bool inNumber_;
        DisplayEventCallback displayEventCallback_;

        int8_t inputSize_;
        bool inputHasPoint_;
        void clearAll();
        void clearEntry();
        void clearInput();
        void inputDigit(int8_t digit);
        void inputPoint();
        void shiftLeftOnInput();
        void saveButton(Button button);

        void calculateEquals();
        void calculateAddSubMulDiv();
        void calculatePercent();
        void calculateSqrt();
        void changeSign();

        void memPlusOrMinus(Operation memOperation);
        void memClear();
        void memRestore();
    };
};

#endif //CALCULATORCOMRADE_CALCULATOR_H
