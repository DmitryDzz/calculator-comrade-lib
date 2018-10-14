//
// Created by dmitrydzz on 08.10.18.
//

#include <calculator/calculator.h>

#include "calculator/calculator.h"
#include "calculator/display_register.h"

using calculatorcomrade::State;
using calculatorcomrade::Calculator;
using calculatorcomrade::Register;
using calculatorcomrade::DisplayRegister;

Register& Calculator::getDisplayedRegister() {
    if (state_.displayRegister == DisplayRegister::x)
        return state_.x;
    return state_.y;
}

State Calculator::getState() {
    return state_;
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

void Calculator::clearAll() {
    state_.clear();
}

void Calculator::clearEntry() {
    getDisplayedRegister().clear();
}
