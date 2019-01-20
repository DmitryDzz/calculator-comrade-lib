//
// Created by dmitrydzz on 08.10.18.
//

#ifndef CALCULATORCOMRADE_STATE_H
#define CALCULATORCOMRADE_STATE_H

#include <cassert>

//TODO DZZ Remove it:
#include <string>


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

        State() : State(Config::DEFAULT_DIGITS) {}

        explicit State(int8_t digits) : digits_(digits), x(digits), y(digits), operation(Operation::add) {
            assert(digits > 0);
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

        void calculateMul() {
            int64_t xValue = x.getNegative() ? -getAbsIntValueTemp(x) : getAbsIntValueTemp(x);
            int64_t yValue = y.getNegative() ? -getAbsIntValueTemp(y) : getAbsIntValueTemp(y);
            xValue = xValue * yValue;
            setValueTemp(x, xValue < 0 ? -xValue : xValue);
            x.setNegative(xValue < 0);
        }

        void calculateDiv() {
            if (getAbsIntValueTemp(x) == 1 && getAbsIntValueTemp(y) == 10) {
                int8_t pointPos = x.getPointPos() + (int8_t) 1;
                bool negative = x.getNegative() != y.getNegative();
                setValueTemp(x, 1, pointPos);
                x.setNegative(negative);
                return;
            }

            int64_t xValue = x.getNegative() ? -getAbsIntValueTemp(x) : getAbsIntValueTemp(x);
            int64_t yValue = y.getNegative() ? -getAbsIntValueTemp(y) : getAbsIntValueTemp(y);
            xValue = xValue / yValue;
            setValueTemp(x, xValue < 0 ? -xValue : xValue);
            x.setNegative(xValue < 0);
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
        int8_t digits_;

        //TODO DZZ Delete these three methods after mul and div implementation
        uint64_t getAbsIntValueTemp(Register &r) {
            uint64_t result = 0;
            uint64_t factor = 1;
            int8_t digits = r.getDigits();
            for (int8_t i = 0; i < digits; i++, factor *= 10)
                result += factor * r.getDigit(i);
            return result;
        }

        void setValueTemp(Register &r, int64_t value) {
            setValueTemp(r, value, 0);
        }

        void setValueTemp(Register &r, int64_t value, int8_t digitsAfterPoint) {
            int8_t digits = r.getDigits();
            r.setNegative(value < 0);
            std::string text = std::to_string(r.getNegative() ? -value : value);
            auto totalDigits = (int8_t) text.size();

            if (digitsAfterPoint < totalDigits) {
                int8_t intDigits = totalDigits - digitsAfterPoint;
                r.setOverflow(intDigits > digits);
                if (r.getOverflow()) {
                    r.setPointPos(digits - (intDigits - digits));
                    for (int16_t i = 0; i < digits; i++) {
                        char digitChar = text[digits - i - 1];
                        std::string digitText(1, digitChar);
                        r.setDigit((int8_t)i, (int8_t)std::stoi(digitText));
                    }
                } else {
                    if (totalDigits > digits) {
                        r.setPointPos(digits - intDigits);
                        for (int16_t i = 0; i < digits; i++) {
                            char digitChar = text[digits - i - 1];
                            std::string digitText(1, digitChar);
                            r.setDigit((int8_t)i, (int8_t)std::stoi(digitText));
                        }
                    } else {
                        r.setPointPos(digitsAfterPoint);
                        for (int16_t i = 0; i < digits; i++) {
                            char digitChar = i < totalDigits ? text[totalDigits - i - 1] : '0';
                            std::string digitText(1, digitChar);
                            r.setDigit((int8_t)i, (int8_t)std::stoi(digitText));
                        }
                    }
                }
            } else { // means: (digitsAfterPoint >= totalDigits)
                r.setOverflow(false);
                int8_t newTotalDigits = digitsAfterPoint + (int8_t) 1;
                int16_t delta = newTotalDigits > digits ? newTotalDigits - digits : (int16_t) 0;
                if (newTotalDigits - totalDigits >= digits) {
                    r.setPointPos(0);
                } else {
                    r.setPointPos(delta > (int8_t) 0 ? (int8_t) (digitsAfterPoint - delta) : digitsAfterPoint);
                }
                for (int16_t i = 0; i < digits; i++) {
                    int16_t charIndex = totalDigits - delta - ((int8_t) 1) - i;
                    char digitChar = charIndex >= 0 ? text[charIndex] : '0';
                    std::string digitText(1, digitChar);
                    r.setDigit((int8_t)i, (int8_t)std::stoi(digitText));
                }
            }
        }
    };

    inline bool operator==(const State& lhs, const State& rhs) {
        return State::isEqual(lhs, rhs);
    }

    inline bool operator!=(const State& lhs, const State& rhs) {
        return !State::isEqual(lhs, rhs);
    }
}

#endif //CALCULATORCOMRADE_STATE_H
