//
// Created by dmitrydzz on 08.10.18.
//

#ifndef CALCULATORCOMRADE_STATE_H
#define CALCULATORCOMRADE_STATE_H

#include <cassert>

#include "calculator/config.h"
#include "calculator/operation.h"
#include "calculator/register.h"
#include "calculator/math.h"

namespace calculatorcomrade {

    class State {
    public:
        Register x;
        Register y;
        Operation operation;

        State() : State(Config::DEFAULT_SIZE) {}

        explicit State(int8_t size) : size_(size), x(size), y(size), operation(Operation::add) {
            assert(size > 0);
            assert(size <= Config::MAX_SIZE);
        }

        void clear() {
            x.clear();
            y.clear();
            operation = Operation::add;
        }

        /**
         * Exchange values in X and Y registers.
         */
        void exchangeXY() {
            Register tmp(size_);
            tmp.set(x);
            x.set(y);
            y.set(tmp);
        }

        /**
         * Calculates "x operation y". The result is placed to register X.
         */
        void calculate() {
            Math::calculate(x, y, operation);
        }

        void calculatePercent() {
            Math::calculatePercent(x, y, operation);
        }

        void calculateSqrt() {
            Math::sqrt(x);
        }

        void changeSign() {
            Math::changeSign(x);
        }

        bool operator==(const State &other) {
            return isEqual(*this, other);
        }

        bool operator!=(const State &other) {
            return !isEqual(*this, other);
        }

        static bool isEqual(const State &lhs, const State &rhs) {
            bool result = lhs.x == rhs.x &&
                          lhs.y == rhs.y &&
                          lhs.operation == rhs.operation;
            return result;
        }

    private:
        int8_t size_;
    };

    inline bool operator==(const State& lhs, const State& rhs) {
        return State::isEqual(lhs, rhs);
    }

    inline bool operator!=(const State& lhs, const State& rhs) {
        return !State::isEqual(lhs, rhs);
    }
}

#endif //CALCULATORCOMRADE_STATE_H
