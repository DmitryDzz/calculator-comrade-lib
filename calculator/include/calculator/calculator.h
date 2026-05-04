/**
 * Calculator Comrade Library
 * License: https://github.com/DmitryDzz/calculator-comrade-lib/blob/master/LICENSE
 * Author: Dmitry Dzakhov
 * Email: info@robot-mitya.ru
 */
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
        explicit Calculator() : Calculator(Config::DEFAULT_SIZE, Config::OPTIONS_DEFAULT) {}
        explicit Calculator(const CalcInt size) : Calculator(size, Config::OPTIONS_DEFAULT) {}
        explicit Calculator(const CalcInt size, const CalcOptions options) :
                options_(options),
                size_(size),
                x_(size),
                y_(size),
                m_(size),
                operation_(Operation::add),
                lastButton_(Button::none),
                lastButtonWasCe_(false),
                hasOperation_(false),
                inNumber_(false),
                displayEventCallback_(nullptr),
                inputSize_(0),
                inputHasPoint_(false) {
            assert(size >= Config::MIN_SIZE);
            assert(size <= Config::MAX_SIZE);
        }

        CalcInt getSize() const { return size_; }
        uint8_t getOptions() const { return options_; }
        void setOptions(const uint8_t options) { options_ = options; }
        void setDisplayEventCallback(DisplayEventCallback callback);
        Register& getX() { return x_; }
        Register& getY() { return y_; }
        Register& getM() { return m_; }
        Operation getOperation() const { return operation_; }

        void exchangeXY();
        bool memHasValue() const;
        void memClear();
        void memRestore();

        void input(Button button);

        /// Exports current state to dump.
        /// \param dump pointer, nullable.
        /// \return dump size.
        uint8_t exportDump(uint8_t *dump);

        /// Sets calculator's state to recently saved by exportDump method.
        /// \param dump
        /// \param dumpSize
        /// \return the returned value should be equal to dumpSize. Possible error codes: 1 - wrong dump version, 0 or 2 - wrong dump size.
        uint8_t importDump(const uint8_t *dump, uint8_t dumpSize);
    private:
        uint8_t options_;
        CalcInt size_;
        Register x_;
        Register y_;
        Register m_;
        Operation operation_;
        Button lastButton_;
        bool lastButtonWasCe_;
        bool hasOperation_;
        bool inNumber_;
        DisplayEventCallback displayEventCallback_;

        CalcInt inputSize_;
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

        static void writeToDump(uint8_t *dump, uint8_t index, uint8_t value);
        uint8_t getDumpSize() const;
    };
}

#endif //CALCULATORCOMRADE_CALCULATOR_H
