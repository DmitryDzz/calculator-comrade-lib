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

State& Calculator::getState() {
    return state_;
}

void Calculator::input(const std::string& button) {
    input(stringToButton(button));
}

void Calculator::input(Button button) {
    switch (button) {
        case Button::d0 ... Button::d9:
        case Button::point:
            // First digit or point after operation:
            if (!inNumber_) {
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
            inNumber_ = false;
            break;
    }

    switch (button) {
        case Button::none:
            break;
        case Button::ca:
            state_.clear();
            hasOperation_ = false;
            clearInput();
            break;
        case Button::ce:
            state_.x.clear();
            clearInput();
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
            state_.y.set(state_.x);
            state_.operation = Operation::mul;
            hasOperation_ = true;
            break;
        case Button::div:
            calculateAddSubMulDiv();
            state_.y.setOne();
            state_.operation = Operation::div;
            hasOperation_ = true;
            break;
        case Button::percent:
            state_.operation = Operation::percent;
            break;
        case Button::equals:
            calculateEquals();
            hasOperation_ = false;
            break;
        case Button::sqrt:
            break;
        case Button::memPlus:
            break;
        case Button::memMinus:
            break;
        case Button::memR:
            break;
        case Button::memC:
            break;
    }
}

Button Calculator::stringToButton(const std::string& button) {
    if (button == "CA")
        return Button::ca;
    else if (button == "CE")
        return Button::ce;
    else if (button == "0")
        return Button::d0;
    else if (button == "1")
        return Button::d1;
    else if (button == "2")
        return Button::d2;
    else if (button == "3")
        return Button::d3;
    else if (button == "4")
        return Button::d4;
    else if (button == "5")
        return Button::d5;
    else if (button == "6")
        return Button::d6;
    else if (button == "7")
        return Button::d7;
    else if (button == "8")
        return Button::d8;
    else if (button == "9")
        return Button::d9;
    else if (button == ".")
        return Button::point;
    else if (button == "+")
        return Button::plus;
    else if (button == "-")
        return Button::minus;
    else if (button == "*")
        return Button::mul;
    else if (button == "/")
        return Button::div;
    else if (button == "SQRT")
        return Button::sqrt;
    else if (button == "%")
        return Button::percent;
    else if (button == "=")
        return Button::equals;
    else if (button == "M+")
        return Button::memPlus;
    else if (button == "M-")
        return Button::memMinus;
    else if (button == "MR")
        return Button::memR;
    else if (button == "MC")
        return Button::memC;
    return Button::none;
}

void Calculator::clearInput() {
    state_.x.clear();
    inputSize_ = 0;
    inputHasPoint_ = false;
}

void Calculator::inputDigit(int8_t digit) {
    if (digit == 0 && inputSize_ == 0) return;
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

void Calculator::calculateEquals() {
    Operation op = state_.operation;
    if (hasOperation_ && (op == Operation::add || op == Operation::sub || op == Operation::div)) {
        state_.exchangeXY();
    }
    state_.calculate();
}

void Calculator::calculateAddSubMulDiv() {
    if (!hasOperation_) return;
    calculateEquals();
    state_.y.clear();
}
