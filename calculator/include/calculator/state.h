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
#include "calculator/math.h"

namespace calculatorcomrade {

    class State {
    public:
        Register x;
        Register y;
        Operation operation;

        State() : State(Config::DEFAULT_DIGITS) {}
        explicit State(uint8_t digits) : digits_(digits), x(digits), y(digits), operation(Operation::add) {
            assert(digits <= Config::MAX_DIGITS);
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
            Register tmp(digits_);
            tmp.set(x);
            x.set(y);
            y.set(tmp);
        }

        /**
         * Calculates "x operation y". The result is placed to register X.
         */
        void calculate() {
            //TODO Make it real
            switch (operation) {
                case Operation::add:
                case Operation::sub:
                    Math::calculate(x, y, operation);
                    break;
                case Operation::mul:
                    calculateMul();
                    break;
                case Operation::div:
                    calculateDiv();
                    break;
                default:
                    break;
            }
        }

//        void calculateAdd() {
//            int64_t xValue = x.negative ? -x.getAbsValue() : x.getAbsIntValue();
//            int64_t yValue = y.negative ? -y.getAbsValue() : y.getAbsIntValue();
//            xValue = xValue + yValue;
//            x.setValue(xValue < 0 ? -xValue : xValue);
//            x.negative = xValue < 0;
//        }
//
//        void calculateSub() {
//            int64_t xValue = x.negative ? -x.getAbsValue() : x.getAbsIntValue();
//            int64_t yValue = y.negative ? -y.getAbsIntValue() : y.getAbsValue();
//            xValue = xValue - yValue;
//            x.setValue(xValue < 0 ? -xValue : xValue);
//            x.negative = xValue < 0;
//        }

        void calculateMul() {
            int64_t xValue = x.negative ? -x.getAbsIntValue() : x.getAbsIntValue();
            int64_t yValue = y.negative ? -y.getAbsIntValue() : y.getAbsIntValue();
            xValue = xValue * yValue;
            x.setValue(xValue < 0 ? -xValue : xValue);
            x.negative = xValue < 0;
        }

        void calculateDiv() {
            if (x.getAbsIntValue() == 1 && y.getAbsIntValue() == 10) {
                uint8_t pointPos = x.pointPos + (uint8_t)1;
                bool negative = x.negative != y.negative;
                x.setValue(1, pointPos);
                x.negative = negative;
                return;
            }

            int64_t xValue = x.negative ? -x.getAbsIntValue() : x.getAbsIntValue();
            int64_t yValue = y.negative ? -y.getAbsIntValue() : y.getAbsIntValue();
            xValue = xValue / yValue;
            x.setValue(xValue < 0 ? -xValue : xValue);
            x.negative = xValue < 0;
        }

        bool operator==(const State& other) {
            return isEqual(*this, other);
        }

        bool operator!=(const State& other) {
            return !isEqual(*this, other);
        }

        static bool isEqual(const State& lhs, const State& rhs) {
            bool result = lhs.x == rhs.x &&
                          lhs.y == rhs.y &&
                          lhs.operation == rhs.operation;
            return result;
        }
    private:
        uint8_t digits_;
    };

    inline bool operator==(const State& lhs, const State& rhs) {
        return State::isEqual(lhs, rhs);
    }

    inline bool operator!=(const State& lhs, const State& rhs) {
        return !State::isEqual(lhs, rhs);
    }
}

#endif //CALCULATORCOMRADE_STATE_H
