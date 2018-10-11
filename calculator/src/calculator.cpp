//
// Created by dmitrydzz on 08.10.18.
//

#include <calculator/calculator.h>

#include "calculator/calculator.h"

using calculatorcomrade::State;
using calculatorcomrade::Calculator;

State Calculator::getState() {
    return state_;
}

void Calculator::input(calculatorcomrade::Button button) {
    switch (button) {
        case Button::ca:
            clearAll();
            break;
        case Button::d0 ... Button::d9:
            inputDigit((int)button - (int)Button::d0);
            break;
    }
}

void Calculator::clearAll() {
    state_ = {};
}

void Calculator::clearEntry() {

}

void Calculator::inputDigit(int digit) {

}
