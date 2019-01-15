//
// Created by dmitrydzz on 09.10.18.
//

#ifndef CALCULATORCOMRADE_REGISTER_H
#define CALCULATORCOMRADE_REGISTER_H

#include <cassert>

#include "calculator/config.h"

namespace calculatorcomrade {
    class Register;

    using RegisterChangedCallback = void(*)(Register &r);

    class Register {
    public:
        uint8_t pointPos = 0;
        bool negative = false;
        bool overflow = false;

        Register() = delete;
        explicit Register(uint8_t digits) : digits_(digits) {
            assert(digits <= Config::MAX_DIGITS);
            data_ = new uint8_t[digits]();
            changedCallback_ = nullptr;
            inChangedCallback_ = false;
        }

        void clear() {
            if (digits_ > 0)
                for (uint8_t i = 0; i < digits_; i++)
                    data_[i] = 0;
            pointPos = 0;
            negative = false;
            overflow = false;
        }

        uint8_t getDigits() const {
            return digits_;
        }

        void set(const Register& rhs) {
            clear();
            uint8_t digits = rhs.digits_;
            if (this->digits_ < digits)
                digits = this->digits_;
            if (digits > 0)
                for (uint8_t i = 0; i < digits; i++)
                    data_[i] = rhs.data_[i];
            pointPos = rhs.pointPos;
            negative = rhs.negative;
            overflow = rhs.overflow;
        }

        void setOne() {
            clear();
            if (digits_ > 0)
                data_[0] = 1;
        }

        void setChangedCallback(const RegisterChangedCallback changedCallback) {
            changedCallback_ = changedCallback;
        }

        bool isZeroData() {
            if (digits_ == 0) return true;
            for (uint8_t i = 0; i < digits_; i++)
                if (data_[i] > 0)
                    return false;
            return true;
        }

        bool operator==(const Register& other) {
            return isEqual(*this, other);
        }

        bool operator!=(const Register& other) {
            return !isEqual(*this, other);
        }

        uint8_t& operator[](uint8_t index) {
            if (changedCallback_ != nullptr) {
                if (!inChangedCallback_) {
                    inChangedCallback_ = true;
                    changedCallback_(*this);
                    inChangedCallback_ = false;
                }
            }
            return data_[index];
        }

        const uint8_t& operator[](uint8_t index) const {
            return data_[index];
        }

        static bool isEqual(const Register& lhs, const Register& rhs) {
            if (lhs.digits_ != rhs.digits_)
                return false;
            if (lhs.digits_ > 0)
                for (uint8_t i = 0; i < lhs.digits_; i++)
                    if (lhs.data_[i] != rhs.data_[i])
                        return false;
            return lhs.pointPos == rhs.pointPos &&
                   lhs.negative == rhs.negative &&
                   lhs.overflow == rhs.overflow;
        }
    private:
        uint8_t digits_;
        uint8_t* data_;

        RegisterChangedCallback changedCallback_;
        bool inChangedCallback_;
    };

    inline bool operator==(const Register& lhs, const Register& rhs) {
        return Register::isEqual(lhs, rhs);
    }

    inline bool operator!=(const Register& lhs, const Register& rhs) {
        return !Register::isEqual(lhs, rhs);
    }


}

#endif //CALCULATORCOMRADE_REGISTER_H
