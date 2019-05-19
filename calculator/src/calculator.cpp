//
// Created by dmitrydzz on 08.10.18.
//

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
