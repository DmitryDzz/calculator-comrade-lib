/**
 * Calculator Comrade Library
 * License: https://github.com/DmitryDzz/calculator-comrade-lib/blob/master/LICENSE
 * Author: Dmitry Dzakhov
 * Email: info@robot-mitya.ru
 */
#include <calculator/calculator.h>
#include <string>
#include <locale>

#include "calculator/calculator.h"
#include "calculator/math.h"

#define S1 ((int8_t)1)

using calculatorcomrade::Button;
using calculatorcomrade::Calculator;
using calculatorcomrade::Register;

void Calculator::setDisplayEventCallback(DisplayEventCallback const callback) {
    displayEventCallback_ = callback;
}

void Calculator::input(Button button) {
    if (x_.hasError()) {
        switch (button) {
            case Button::ca:
                clearAll();
                break;
            case Button::ce:
                if (x_.hasOverflow())
                    x_.setError(false, false);
                break;
            case Button::ceca:
                if (x_.hasOverflow())
                    x_.setError(false, false);
                else
                    clearAll();
                break;
            default:
                break;
        }

        saveButton(button);
        if (displayEventCallback_ != nullptr)
            displayEventCallback_();
        return;
    }

    bool isNumberOrPoint = false;
    switch (button) {
        case Button::d0 ... Button::d9:
        case Button::point:
        case Button::memR:
        case Button::memRC:
        case Button::sqrt:
            if (lastButton_ != Button::memRC) isNumberOrPoint = true;
            break;
        default:
            isNumberOrPoint = false;
            break;
    }

    switch (button) {
        case Button::d0 ... Button::d9:
        case Button::point:
            if (inNumber_ && inputSize_ == 0 && !inputHasPoint_) {
                x_.clear();
            }
            // No break! In case of a number after Sqrt operation.
        case Button::memR:
        case Button::memRC:
        case Button::sqrt:
        case Button::ce:
        case Button::ceca:
            // First digit or point after operation:
            if (isNumberOrPoint && !inNumber_) {
                if (hasOperation_) {
                    y_.set(x_);
                }
                if (button != Button::sqrt) {
                    x_.clear();
                }
                inputSize_ = 0;
                inputHasPoint_ = false;
                inNumber_ = true;
            }
            break;
        default:
            inputSize_ = 0;
            inputHasPoint_ = false;
            inNumber_ = false;
            break;
    }

    switch (button) {
        case Button::none:
            break;
        case Button::ca:
            clearAll();
            break;
        case Button::ce:
            clearEntry();
            break;
        case Button::ceca:
            if (!(hasOperation_ && inNumber_) || (button == lastButton_) || lastButtonWasCe_) clearAll();
            else clearEntry();
            break;
        case Button::d0 ... Button::d9:
            inputDigit((int8_t)button - (int8_t)Button::d0);
            break;
        case Button::point:
            inputPoint();
            break;
        case Button::plus:
            calculateAddSubMulDiv();
            operation_ = Operation::add;
            hasOperation_ = true;
            break;
        case Button::minus:
            calculateAddSubMulDiv();
            operation_ = Operation::sub;
            hasOperation_ = true;
            break;
        case Button::mul:
            calculateAddSubMulDiv();
            operation_ = Operation::mul;
            hasOperation_ = true;
            break;
        case Button::div:
            calculateAddSubMulDiv();
            operation_ = Operation::div;
            hasOperation_ = true;
            break;
        case Button::mu:
            if (hasOperation_) {
                y_.clear();
                operation_ = Operation::add;
                hasOperation_ = false;
            } else {
                operation_ = Operation::mu;
                hasOperation_ = true;
            }
            break;
        case Button::percent:
            calculatePercent();
            hasOperation_ = false;
            break;
        case Button::equals:
            calculateEquals();
            hasOperation_ = false;
            break;
        case Button::sqrt:
            calculateSqrt();
            break;
        case Button::changeSign:
            changeSign();
            break;
        case Button::memPlus:
            memPlusOrMinus(Operation::add);
            break;
        case Button::memMinus:
            memPlusOrMinus(Operation::sub);
            break;
        case Button::memRC:
            if (button == lastButton_) memClear();
            else memRestore();
            break;
        case Button::memR:
            memRestore();
            break;
        case Button::memC:
            memClear();
            break;
    }

    saveButton(button);
    if (displayEventCallback_ != nullptr)
        displayEventCallback_();
}

void Calculator::clearAll() {
    x_.clear();
    y_.clear();
    operation_ = Operation::add;
    hasOperation_ = false;
    clearInput();
}

void Calculator::clearEntry() {
    if (inputSize_ > 0 || inputHasPoint_ || lastButton_ == Button::sqrt)
        clearInput();
}

void Calculator::clearInput() {
    x_.clear();
    inputSize_ = 0;
    inputHasPoint_ = false;
}

void Calculator::inputDigit(int8_t digit) {
    if (digit == 0 && !inputHasPoint_ && inputSize_ == 0) return;
    if (inputSize_ >= size_ || x_.getPointPos() == size_ - 1) return;
    shiftLeftOnInput();
    x_.setDigit(0, digit);
    inputSize_++;
    if (inputHasPoint_) x_.incPointPos(1);
}

void Calculator::inputPoint() {
    if (inputSize_ >= size_) return;
    inputHasPoint_ = true;
}

void Calculator::shiftLeftOnInput() {
    if (size_ == 0 || inputSize_ >= size_) return;
    if (inputSize_ > 0) {
        for (int8_t i = 0; i < inputSize_; i++)
            x_.setDigit(inputSize_ - i, x_.getDigit(inputSize_ - i - S1));
        x_.setDigit(0, 0);
    }
}

void Calculator::saveButton(const Button button) {
    lastButtonWasCe_ = false;
    switch (button) {
        case Button::ceca:
        case Button::memRC:
        case Button::plus:
        case Button::minus:
        case Button::mul:
        case Button::div:
        case Button::mu:
        case Button::sqrt:
            lastButton_ = button;
            break;
        case Button::ce:
            // This is a patch for test ClearEntry4: "3 * ce =" => 9
            lastButtonWasCe_ = true;
            break;
        default:
            lastButton_ = Button::none;
            break;
    }
}

void Calculator::calculateAddSubMulDiv() {
    if (!hasOperation_) return;

    // Do nothing if it's just another arithmetic operation:
    if (lastButton_ == Button::plus ||
        lastButton_ == Button::minus ||
        lastButton_ == Button::mul ||
        lastButton_ == Button::div ||
        lastButton_ == Button::mu) return;

    Operation op = operation_;
    if (op == Operation::add || op == Operation::sub || op == Operation::div) {
        exchangeXY();
    }

    Math::calculate(x_, y_, operation_, options_);

    if (op == Operation::add || op == Operation::sub)
        y_.clear();
}

void Calculator::calculateEquals() {
    Operation op = operation_;

    // MU operator ugly patch.
    if (op == Operation::mu) {
        if (!hasOperation_) {
            Math::calculate(x_, y_, Operation::mul, options_);
        }
        y_.clear();
        operation_ = Operation::add;
        return;
    }

    if (hasOperation_) {
        if (op == Operation::add || op == Operation::sub || op == Operation::div) {
            exchangeXY();
        }

        if (lastButton_ == Button::mul)
            y_.set(x_);
        else if (lastButton_ == Button::div)
            x_.setOne();
    }
    Math::calculate(x_, y_, operation_, options_);
}

void Calculator::calculatePercent() {
    Operation op = operation_;
    if (hasOperation_) {
        if (op == Operation::add || op == Operation::sub || op == Operation::div || op == Operation ::mu) {
            exchangeXY();
        }

        Math::calculatePercent(x_, y_, operation_, options_);
    } else {
        if (op == Operation::mul || op == Operation::div) {
            Math::calculatePercent(x_, y_, operation_, options_);
        }
    }
}

void Calculator::calculateSqrt() {
    inputSize_ = 0;
    inputHasPoint_ = false;
    Math::sqrt(x_);
}

void Calculator::changeSign() {
    Math::changeSign(x_);
}

void Calculator::memPlusOrMinus(const Operation memOperation) {
    assert(memOperation == Operation::add || memOperation == Operation::sub);
    inNumber_ = false;

    if (hasOperation_) {
        calculateEquals();
        y_.clear();
        operation_ = Operation::add;
        hasOperation_ = false;
        if (x_.hasError()) return;
    }

    Register acc(m_.getSize());
    acc.set(m_);
    if (options_ & Config::OPTION_MEM_CAN_TRUNC_X) {
        Math::calculate(acc, x_, memOperation, options_);
    } else {
        Register xT(x_.getSize());
        xT.set(x_);
        Math::calculate(acc, xT, memOperation, options_);
    }
    if (acc.hasError()) {
        x_.clear();
        x_.setError(true, false);
    } else {
        m_.set(acc);
    }
}

void Calculator::exchangeXY() {
    Register tmp(size_);
    tmp.set(x_);
    x_.set(y_);
    y_.set(tmp);
}

bool Calculator::memHasValue() {
    return !m_.isZero();
}

void Calculator::memClear()
{
    inNumber_ = false;
    m_.clear();
}

void Calculator::memRestore()
{
    inNumber_ = false;
    x_.set(m_);
}

int8_t Calculator::exportDump(int8_t *dump) {
    int8_t index = 0;

    // Header:
    writeToDump(dump, index++, Config::DUMP_VERSION); // dump version
    writeToDump(dump, index++, getDumpSize());        // dump size

    // Body:
    writeToDump(dump, index++, size_);
    writeToDump(dump, index++, options_);
    writeToDump(dump, index++, static_cast<int8_t>(operation_));
    writeToDump(dump, index++, hasOperation_ ? 1 : 0);
    writeToDump(dump, index++, inNumber_ ? 1 : 0);
    writeToDump(dump, index++, inputSize_);
    writeToDump(dump, index++, inputHasPoint_ ? 1 : 0);
    writeToDump(dump, index++, static_cast<int8_t>(lastButton_));
    writeToDump(dump, index++, lastButtonWasCe_ ? 1 : 0);

    // Register X:
    for (int8_t i = 0; i < size_; i++) {
        writeToDump(dump, index++, x_.getDigit(i));
    }
    writeToDump(dump, index++, x_.getPointPos());
    writeToDump(dump, index++, x_.isNegative() ? 1 : 0);
    writeToDump(dump, index++, x_.hasError() ? 1 : 0);
    writeToDump(dump, index++, x_.hasOverflow() ? 1 : 0);

    // Register Y:
    for (int8_t i = 0; i < size_; i++) {
        writeToDump(dump, index++, y_.getDigit(i));
    }
    writeToDump(dump, index++, y_.getPointPos());
    writeToDump(dump, index++, y_.isNegative() ? 1 : 0);
    writeToDump(dump, index++, y_.hasError() ? 1 : 0);
    writeToDump(dump, index++, y_.hasOverflow() ? 1 : 0);

    // Register M:
    for (int8_t i = 0; i < size_; i++) {
        writeToDump(dump, index++, m_.getDigit(i));
    }
    writeToDump(dump, index++, m_.getPointPos());
    writeToDump(dump, index++, m_.isNegative() ? 1 : 0);
    writeToDump(dump, index++, m_.hasError() ? 1 : 0);
    writeToDump(dump, index++, m_.hasOverflow() ? 1 : 0);

    return index;
}

int8_t Calculator::importDump(const int8_t *dump, int8_t dumpSize) {
    int8_t index = 0;
    if (dumpSize < 2) return index;
    if (dump[index++] != Config::DUMP_VERSION) return index;
    if (dump[index++] != getDumpSize()) return index;

    size_ = dump[index++];
    options_ = dump[index++];
    operation_ = (Operation) dump[index++];
    hasOperation_ = dump[index++] == 1;
    inNumber_ = dump[index++] == 1;
    inputSize_ = dump[index++];
    inputHasPoint_ = dump[index++] == 1;
    lastButton_ = (Button) dump[index++];
    lastButtonWasCe_ = dump[index++] == 1;

    // Register X:
    for (int8_t i = 0; i < size_; i++) {
        x_.setDigit(i, dump[index++]);
    }
    x_.setPointPos(dump[index++]);
    x_.setNegative(dump[index++] == 1);
    bool hasError = dump[index++] == 1;
    bool hasOverflow = dump[index++] == 1;
    x_.setError(hasError, hasOverflow);

    // Register Y:
    for (int8_t i = 0; i < size_; i++) {
        y_.setDigit(i, dump[index++]);
    }
    y_.setPointPos(dump[index++]);
    y_.setNegative(dump[index++] == 1);
    hasError = dump[index++] == 1;
    hasOverflow = dump[index++] == 1;
    y_.setError(hasError, hasOverflow);

    // Register M:
    for (int8_t i = 0; i < size_; i++) {
        m_.setDigit(i, dump[index++]);
    }
    m_.setPointPos(dump[index++]);
    m_.setNegative(dump[index++] == 1);
    hasError = dump[index++] == 1;
    hasOverflow = dump[index++] == 1;
    m_.setError(hasError, hasOverflow);

    return index;
}

void Calculator::writeToDump(int8_t *dump, int8_t index, int8_t value) {
    if (dump != nullptr) {
        dump[index] = value;
    }
}

int8_t Calculator::getDumpSize() {
    return 11 + 3 * (4 + size_);
}
