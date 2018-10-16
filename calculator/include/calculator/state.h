//
// Created by dmitrydzz on 08.10.18.
//

#ifndef CALCULATORCOMRADE_STATE_H
#define CALCULATORCOMRADE_STATE_H

#include <cassert>

#include "calculator/config.h"
#include "calculator/operation.h"
#include "calculator/display_register.h"
#include "calculator/register.h"

namespace calculatorcomrade {

    class State {
    public:
        Register x;
        Register y;
        Operation operation = Operation::none;
        DisplayRegister displayRegister = DisplayRegister::x;

        State() : State(Config::DEFAULT_DIGITS) {}
        explicit State(uint8_t digits) : x(digits), y(digits) {
            assert(digits <= Config::MAX_DIGITS);
        }

        void clear() {
            x.clear();
            y.clear();
            //TODO How to reset the object to default state?
            operation = {};
            displayRegister = {};
        }

        bool operator==(const State& other) {
            return isEqual(*this, other);
        }

        bool operator!=(const State& other) {
            return !isEqual(*this, other);
        }

        bool static isEqual(const State& lhs, const State& rhs) {
            bool result = lhs.x == rhs.x &&
                          lhs.y == rhs.y &&
                          lhs.operation == rhs.operation &&
                          lhs.displayRegister == rhs.displayRegister;
            return result;
        }
    };

    bool operator==(const State& lhs, const State& rhs) {
        return State::isEqual(lhs, rhs);
    }

    bool operator!=(const State& lhs, const State& rhs) {
        return !State::isEqual(lhs, rhs);
    }
}

#endif //CALCULATORCOMRADE_STATE_H
