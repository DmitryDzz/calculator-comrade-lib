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
        Register() = delete;
        explicit Register(uint8_t digits) : digits_(digits) {
            assert(digits > 0);
            assert(digits <= Config::MAX_DIGITS);
            data_ = new uint8_t[digits]();
            clearInternal();
        }

        void clear() {
            clearInternal();
            notify();
        }

        uint8_t getDigits() const {
            return digits_;
        }

        void set(const Register& rhs) {
            clearInternal();
            uint8_t digits = rhs.digits_;
            if (this->digits_ < digits)
                digits = this->digits_;
            if (digits > 0)
                for (uint8_t i = 0; i < digits; i++)
                    data_[i] = rhs.data_[i];
            pointPos_ = rhs.pointPos_;
            negative_ = rhs.negative_;
            overflow_ = rhs.overflow_;
            notify();
        }

        void setOne() {
            clearInternal();
            if (digits_ > 0)
                data_[0] = 1;
            notify();
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


        inline uint8_t& getDigit(const uint8_t index) {
            return data_[index];
        };

        inline const uint8_t& getDigit(const uint8_t index) const {
            return data_[index];
        };

        inline void setDigit(const uint8_t index, const uint8_t value) {
            data_[index] = value;
            notify();
        }

        inline void incDigit(const uint8_t index, const int8_t delta) {
            uint8_t digit = data_[index] + delta;
            setDigit(index, digit);
        }

        inline uint8_t getPointPos() {
            return pointPos_;
        }

        inline void setPointPos(const uint8_t value) {
            pointPos_ = value;
            notify();
        }

        inline void incPointPos(const int8_t delta) {
            setPointPos(pointPos_ + delta);
        }

        inline bool getNegative() {
            return negative_;
        }

        inline void setNegative(const bool value) {
            negative_ = value;
            notify();
        }

        inline void switchNegative() {
            negative_ = !negative_;
            notify();
        }

        inline bool getOverflow() {
            return overflow_;
        }

        inline void setOverflow(const bool value) {
            overflow_ = value;
            notify();
        }

        static bool isEqual(const Register& lhs, const Register& rhs) {
            if (lhs.digits_ != rhs.digits_)
                return false;
            if (lhs.digits_ > 0)
                for (uint8_t i = 0; i < lhs.digits_; i++)
                    if (lhs.data_[i] != rhs.data_[i])
                        return false;
            return lhs.pointPos_ == rhs.pointPos_ &&
                   lhs.negative_ == rhs.negative_ &&
                   lhs.overflow_ == rhs.overflow_;
        }
    private:
        uint8_t digits_;
        uint8_t* data_;
        uint8_t pointPos_ = 0;
        bool negative_ = false;
        bool overflow_ = false;

        RegisterChangedCallback changedCallback_ = nullptr;
        bool canNotify_ = true;
        void notify() {
            if (changedCallback_ != nullptr) {
                if (canNotify_) {
                    canNotify_ = false;
                    changedCallback_(*this);
                    canNotify_ = true;
                }
            }
        }

        void clearInternal() {
            if (digits_ > 0)
                for (uint8_t i = 0; i < digits_; i++)
                    data_[i] = 0;
            pointPos_ = 0;
            negative_ = false;
            overflow_ = false;
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
