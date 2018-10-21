//
// Created by dmitrydzz on 08.10.18.
//

#include <calculator/calculator.h>
#include <string>
#include <locale>

#include "calculator/calculator.h"
#include "calculator/display_register.h"

using calculatorcomrade::Button;
using calculatorcomrade::Calculator;
using calculatorcomrade::DisplayRegister;
using calculatorcomrade::Register;
using calculatorcomrade::State;

Register& Calculator::getDisplayedRegister() {
    if (state_.displayRegister == DisplayRegister::x)
        return state_.x;
    return state_.y;
}

State Calculator::getState() {
    return state_;
}

void Calculator::input(const std::string& button) {
    input(stringToButton(button));
}

void Calculator::input(calculatorcomrade::Button button) {
    switch (button) {
        case Button::ca:
            clearAll();
            break;
        case Button::ce:
            clearEntry();
            break;
        case Button::d0 ... Button::d9:
            getDisplayedRegister().inputDigit((uint8_t)((int)button - (int)Button::d0));
            break;
        case Button::point:
            getDisplayedRegister().inputPoint();
            break;
        case Button::minus:
            state_.operation = Operation::sub;
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

void Calculator::clearAll() {
    state_.clear();
}

void Calculator::clearEntry() {
    getDisplayedRegister().clear();
}
