//
// Created by dmitrydzz on 08.10.18.
//

#ifndef CALCULATORCOMRADE_CALCULATOR_H
#define CALCULATORCOMRADE_CALCULATOR_H

#include "calculator/config.h"
#include "calculator/button.h"
#include "calculator/register.h"
#include "calculator/operation.h"

namespace calculatorcomrade {

    using DisplayEventCallback = void (*) ();

    class Calculator {
    public:
        explicit Calculator() : Calculator(Config::DEFAULT_SIZE, Config::OPTIONS_DEFAULT) {};
        explicit Calculator(int8_t size) : Calculator(size, Config::OPTIONS_DEFAULT) {};
        explicit Calculator(int8_t size, uint8_t options) :
                size_(size),
                options_(options),
                x_(size),
                y_(size),
                m_(size),
                operation_(Operation::add),
                hasOperation_(false),
                inNumber_(false),
                inputSize_(0),
                inputHasPoint_(false),
                lastButton_(Button::none),
                lastButtonWasCe_(false),
                displayEventCallback_(nullptr) {
            assert(size >= Config::MIN_SIZE);
            assert(size <= Config::MAX_SIZE);
        };

        int8_t getSize() { return size_; }
        uint8_t getOptions() { return options_; }
        void setOptions(uint8_t options) { options_ = options; }
        void setDisplayEventCallback(DisplayEventCallback callback);
        Register& getX() { return x_; }
        Register& getY() { return y_; }
        Register& getM() { return m_; }
        Operation getOperation() { return operation_; }

        void exchangeXY();
        bool memHasValue();
        void memClear();
        void memRestore();

        void input(Button button);

        /// Exports current state to dump.
        /// \param dump pointer, nullable.
        /// \return dump size.
        int8_t exportDump(int8_t *dump);

        /// Sets calculator's state to recently saved by exportDump method.
        /// \param dump
        /// \param dumpSize
        /// \return the returned value should be equal to dumpSize. Possible error codes: 1 - wrong dump version, 0 or 2 - wrong dump size.
        int8_t importDump(const int8_t *dump, int8_t dumpSize);
    private:
        uint8_t options_;
        int8_t size_;
        Register x_;
        Register y_;
        Register m_;
        Operation operation_;
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

        static void writeToDump(int8_t *dump, int8_t index, int8_t value);
        int8_t getDumpSize();
    };
}

#endif //CALCULATORCOMRADE_CALCULATOR_H
