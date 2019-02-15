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
using calculatorcomrade::State;

void Calculator::setDisplayEventCallback(DisplayEventCallback const callback) {
    displayEventCallback_ = callback;
}

State& Calculator::getState() {
    return state_;
}

void Calculator::input(Button button) {
    if (state_.x.hasError()) {
        switch (button) {
            case Button::ca:
                clearAll();
                break;
            case Button::ce:
                if (state_.x.hasOverflow())
                    state_.x.setError(false, false);
                break;
            case Button::ceca:
                if (state_.x.hasOverflow())
                    state_.x.setError(false, false);
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
        case Button::memR:
        case Button::memRC:
        case Button::sqrt:
        case Button::ce:
        case Button::ceca:
            // First digit or point after operation:
            if (isNumberOrPoint && !inNumber_) {
                if (hasOperation_) {
                    state_.y.set(state_.x);
                }
                if (button != Button::sqrt) {
                    state_.x.clear();
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
            if (button == lastButton_ || lastButtonWasCe_) clearAll();
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
            state_.operation = Operation::add;
            hasOperation_ = true;
            break;
        case Button::minus:
            calculateAddSubMulDiv();
            state_.operation = Operation::sub;
            hasOperation_ = true;
            break;
        case Button::mul:
            calculateAddSubMulDiv();
            state_.operation = Operation::mul;
            hasOperation_ = true;
            break;
        case Button::div:
            calculateAddSubMulDiv();
            state_.operation = Operation::div;
            hasOperation_ = true;
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
    state_.clear();
    hasOperation_ = false;
    clearInput();
}

void Calculator::clearEntry() {
    if (inputSize_ > 0 || inputHasPoint_)
        clearInput();
}

void Calculator::clearInput() {
    state_.x.clear();
    inputSize_ = 0;
    inputHasPoint_ = false;
}

void Calculator::inputDigit(int8_t digit) {
    if (digit == 0 && !inputHasPoint_ && inputSize_ == 0) return;
    if (inputSize_ >= size_ || state_.x.getPointPos() == size_ - 1) return;
    shiftLeftOnInput();
    state_.x.setDigit(0, digit);
    inputSize_++;
    if (inputHasPoint_) state_.x.incPointPos(1);
}

void Calculator::inputPoint() {
    if (inputSize_ >= size_) return;
    inputHasPoint_ = true;
}

void Calculator::shiftLeftOnInput() {
    if (size_ == 0 || inputSize_ >= size_) return;
    if (inputSize_ > 0) {
        for (int8_t i = 0; i < inputSize_; i++)
            state_.x.setDigit(inputSize_ - i, state_.x.getDigit(inputSize_ - i - S1));
        state_.x.setDigit(0, 0);
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
            lastButton_ = button;
            break;
        case Button::ce:
            // This is a patch for test ClearEntry4: "3 * ce =" => 9
            //TODO DZZ Check it on another calculator with CE button.
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
        lastButton_ == Button::div) return;

    Operation op = state_.operation;
    if (op == Operation::add || op == Operation::sub || op == Operation::div) {
        state_.exchangeXY();
    }

    Math::calculate(state_.x, state_.y, state_.operation, options_);

    if (op == Operation::add || op == Operation::sub)
        state_.y.clear();
}

void Calculator::calculateEquals() {
    if (hasOperation_) {
        Operation op = state_.operation;
        if (op == Operation::add || op == Operation::sub || op == Operation::div) {
            state_.exchangeXY();
        }

        if (lastButton_ == Button::mul)
            state_.y.set(state_.x);
        else if (lastButton_ == Button::div)
            state_.x.setOne();
    }

    Math::calculate(state_.x, state_.y, state_.operation, options_);
}

void Calculator::calculatePercent() {
    Operation op = state_.operation;
    if (hasOperation_) {
        if (op == Operation::add || op == Operation::sub || op == Operation::div) {
            state_.exchangeXY();
        }

        Math::calculatePercent(state_.x, state_.y, state_.operation, options_);
    } else {
        if (op == Operation::mul || op == Operation::div) {
            Math::calculatePercent(state_.x, state_.y, state_.operation, options_);
        }
    }
}

void Calculator::calculateSqrt() {
    inputSize_ = 0;
    inputHasPoint_ = false;
    Math::sqrt(state_.x);
}

void Calculator::changeSign() {
    Math::changeSign(state_.x);
}

void Calculator::memPlusOrMinus(const Operation memOperation) {
    assert(memOperation == Operation::add || memOperation == Operation::sub);
    inNumber_ = false;

    Register &x = state_.x;
    Register &y = state_.y;
    Register &m = state_.m;

    if (hasOperation_) {
        calculateEquals();
        y.clear();
        state_.operation = Operation::add;
        hasOperation_ = false;
        if (x.hasError()) return;
    }

    Register acc(m.getSize());
    acc.set(m);
    if (options_ & Config::OPTION_MEM_CAN_TRUNC_X) {
        Math::calculate(acc, x, memOperation, options_);
    } else {
        Register xT(x.getSize());
        xT.set(x);
        Math::calculate(acc, xT, memOperation, options_);
    }
    if (acc.hasError()) {
        x.clear();
        x.setError(true, false);
    } else {
        m.set(acc);
    }
}

void Calculator::memClear()
{
    inNumber_ = false;
    state_.memClear();
}

void Calculator::memRestore()
{
    inNumber_ = false;
    state_.memRestore();
}
