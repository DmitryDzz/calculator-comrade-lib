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
        uint8_t pointPos = 0;
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
            pointPos = 0;
            negative = false;
            overflow = false;
        }

        uint8_t getDigits() const {
            return digits_;
        }

        uint64_t getAbsIntValue() {
            //TODO Move to tests
            uint64_t result = 0;
            uint64_t factor = 1;
            for (int i = 0; i < digits_; i++, factor *= 10)
                result += factor * data_[i];
            return result;
        }

        void setValue(int64_t value) {
            //TODO Move to tests
            setValue(value, 0);
        }

        void setValue(int64_t value, uint8_t digitsAfterPoint) {
            //TODO Move to tests
            negative = value < 0;
            std::string text = std::to_string(negative ? -value : value);
            auto totalDigits = (uint8_t) text.size();

            if (digitsAfterPoint < totalDigits) {
                uint8_t intDigits = totalDigits - digitsAfterPoint;
                overflow = intDigits > digits_;
                if (overflow) {
                    pointPos = digits_ - (intDigits - digits_);
                    for (int16_t i = 0; i < digits_; i++) {
                        char digitChar = text[digits_ - i - 1];
                        std::string digitText(1, digitChar);
                        data_[i] = static_cast<uint8_t>(std::stoi(digitText));
                    }
                } else {
                    if (totalDigits > digits_) {
                        pointPos = digits_ - intDigits;
                        for (int16_t i = 0; i < digits_; i++) {
                            char digitChar = text[digits_ - i - 1];
                            std::string digitText(1, digitChar);
                            data_[i] = static_cast<uint8_t>(std::stoi(digitText));
                        }
                    } else {
                        pointPos = digitsAfterPoint;
                        for (int16_t i = 0; i < digits_; i++) {
                            char digitChar = i < totalDigits ? text[totalDigits - i - 1] : '0';
                            std::string digitText(1, digitChar);
                            data_[i] = static_cast<uint8_t>(std::stoi(digitText));
                        }
                    }
                }
            } else { // means: (digitsAfterPoint >= totalDigits)
                overflow = false;
                uint8_t newTotalDigits = digitsAfterPoint + (uint8_t)1;
                int16_t delta = newTotalDigits > digits_ ? newTotalDigits - digits_ : (int16_t)0;
                if (newTotalDigits - totalDigits >= digits_) {
                    pointPos = 0;
                } else {
                    pointPos = delta > (uint8_t)0 ? (uint8_t)(digitsAfterPoint - delta) : digitsAfterPoint;
                }
                for (int16_t i = 0; i < digits_; i++) {
                    int16_t charIndex = totalDigits - delta - ((uint8_t)1) - i;
                    char digitChar = charIndex >= 0 ? text[charIndex] : '0';
                    std::string digitText(1, digitChar);
                    data_[i] = static_cast<uint8_t>(std::stoi(digitText));
                }
            }
        }

        void set(const Register& rhs) {
            this->clear();
            uint8_t digits = rhs.digits_;
            if (this->digits_ < digits)
                digits = this->digits_;
            for (int i = 0; i < digits; i++)
                this->data_[i] = rhs.data_[i];
            this->pointPos = rhs.pointPos;
            this->negative = rhs.negative;
            this->overflow = rhs.overflow;
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
    };

    inline bool operator==(const Register& lhs, const Register& rhs) {
        return Register::isEqual(lhs, rhs);
    }

    inline bool operator!=(const Register& lhs, const Register& rhs) {
        return !Register::isEqual(lhs, rhs);
    }


}

#endif //CALCULATORCOMRADE_REGISTER_H
