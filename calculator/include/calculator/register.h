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

        void setOne() {
            clear();
            if (digits_ > 0)
                data_[0] = 1;
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
