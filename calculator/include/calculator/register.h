//
// Created by dmitrydzz on 09.10.18.
//

#ifndef CALCULATORCOMRADE_REGISTER_H
#define CALCULATORCOMRADE_REGISTER_H

#include <array>
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iterator>
#include <vector>
#include <string>

#include "calculator/config.h"

namespace calculatorcomrade {
    class Register {
    public:
        uint8_t pointPos = 0xFF;
        bool negative = false;
        bool overflow = false;

        Register() = delete;
        explicit Register(uint8_t digits) : digits_(digits) {
            assert(digits <= Config::MAX_DIGITS);
            data_ = new uint8_t[digits]();
        }

        void clear() {
            for (int i = 0; i < digits_; i++)
                data_[i] = 0;
            inputSize_ = 0;
            pointPos = 0xFF;
            negative = false;
            overflow = false;
        }

        void inputDigit(uint8_t digit) {
            if (digit == 0 && inputSize_ == 0) return;
            if (inputSize_ >= digits_) return;
            shiftDigits();
            data_[0] = digit;
            inputSize_++;
            if (pointPos != 0xFF) pointPos++;
        }

        void inputPoint() {
            if (inputSize_ >= digits_) return;
            if (pointPos == 0xFF) pointPos = 0;
        }

        uint64_t getValue() {
            uint64_t result = 0;
            uint64_t factor = 1;
            for (int i = 0; i < digits_; i++, factor *= 10)
                result += factor * data_[i];
            return result;
        }

        void setValue(int64_t value) {
            negative = value < 0;
            std::string text = std::to_string(negative ? -value : value);
            auto textDigits = (uint8_t) text.size();
            overflow = textDigits > digits_;
            for (int8_t i = 0; i < digits_; i++) {
                char digitChar = i < textDigits ? text[textDigits - i - 1] : '0';
                std::string digitText(1, digitChar);
                data_[i] = static_cast<uint8_t>(std::stoi(digitText));
            }
            if (overflow)
                pointPos = textDigits - digits_;
        }

        bool operator==(const Register& other) {
            return isEqual(*this, other);
        }

        bool operator!=(const Register& other) {
            return !isEqual(*this, other);
        }

        uint8_t& operator[](int index) {
            return data_[index];
        }

        const uint8_t& operator[](int index) const {
            return data_[index];
        }

        static bool isEqual(const Register& lhs, const Register& rhs) {
            if (lhs.digits_ != rhs.digits_)
                return false;
            for (int i = 0; i < lhs.digits_; i++)
                if (lhs.data_[i] != rhs.data_[i])
                    return false;
            return lhs.pointPos == rhs.pointPos &&
                   lhs.negative == rhs.negative &&
                   lhs.overflow == rhs.overflow;
        }
    private:
        uint8_t digits_;
        uint8_t* data_;
        uint8_t inputSize_ = 0;

        void shiftDigits() {
            if (inputSize_ >= digits_) return;
            for (int i = inputSize_ - 1; i >= 0; i--) {
                data_[i + 1] = data_[i];
            }
            data_[0] = 0;
        }
    };

    inline bool operator==(const Register& lhs, const Register& rhs) {
        return Register::isEqual(lhs, rhs);
    }

    inline bool operator!=(const Register& lhs, const Register& rhs) {
        return !Register::isEqual(lhs, rhs);
    }
}

#endif //CALCULATORCOMRADE_REGISTER_H
