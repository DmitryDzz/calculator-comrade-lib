//
// Created by dmitrydzz on 08.10.18.
//

#ifndef CALCULATORCOMRADE_STATE_H
#define CALCULATORCOMRADE_STATE_H

#include <stdint-gcc.h>
#include "operation.h"
#include "display_register.h"
#include "register.h"

namespace calculatorcomrade {

    class State {
    public:
        Register x;
        Register y;
        Operation operation = Operation::none;
        DisplayRegister displayRegister = DisplayRegister::x;

        State() = default;

        bool operator==(const State& other) {
            return *this == other;
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
