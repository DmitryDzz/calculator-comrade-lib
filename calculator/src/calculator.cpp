//
// Created by dmitrydzz on 08.10.18.
//

#include <calculator/calculator.h>
#include <string>
#include <locale>

#include "calculator/calculator.h"

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
    if (state_.x.getOverflow()) {
        if (button == Button::ca)
            clearAll();
        else if (button == Button::ce || button == Button::ceca)
            state_.x.setOverflow(false);

        lastButton_ = button;
        if (displayEventCallback_ != nullptr)
            displayEventCallback_();
        return;
    }

    bool isNumberOrPoint;
    switch (button) {
        case Button::d0 ... Button::d9:
        case Button::point:
            isNumberOrPoint = true;
            break;
        default:
            isNumberOrPoint = false;
            break;
    }

    switch (button) {
        case Button::d0 ... Button::d9:
        case Button::point:
        case Button::ce:
        case Button::ceca:
            // First digit or point after operation:
            if (isNumberOrPoint && !inNumber_) {
                if (hasOperation_) {
                    state_.y.set(state_.x);
                }
                state_.x.clear();
                inputSize_ = 0;
                inputHasPoint_ = false;
            }
            inNumber_ = true;
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
            if (button == lastButton_) clearAll();
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
            memPlus();
            break;
        case Button::memMinus:
            memMinus();
            break;
        case Button::memRC:
            //TODO DZZ
            break;
        case Button::memR:
            memRestore();
            break;
        case Button::memC:
            memClear();
            break;
    }

    lastButton_ = button;
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
    else
        clearAll();
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

    state_.calculate();

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

    state_.calculate();
}

void Calculator::calculatePercent() {
    Operation op = state_.operation;
    if (hasOperation_) {
        if (op == Operation::add || op == Operation::sub || op == Operation::div) {
            state_.exchangeXY();
        }

        state_.calculatePercent();
    } else {
        if (op == Operation::mul || op == Operation::div) {
            state_.calculatePercent();
        }
    }
}

void Calculator::calculateSqrt() {
    state_.calculateSqrt();
}

void Calculator::changeSign() {
    state_.changeSign();
}

void Calculator::memPlus()
{
    inNumber_ = false;
    state_.memPlus();
}

void Calculator::memMinus()
{
    inNumber_ = false;
    state_.memPlus();
}

void Calculator::memClear()
{
    inNumber_ = false;
    state_.memClear();
}

void Calculator::memRestore()
{
    inNumber_ = false;
    state_.memClear();
}
