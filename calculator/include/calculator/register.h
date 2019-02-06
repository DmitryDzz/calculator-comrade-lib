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
        explicit Register(int8_t size) : size_(size) {
            assert(size > 0);
            data_ = new int8_t[size]();
            clearInternal();
        }

        void clear() {
            clearInternal();
            notify();
        }

        inline int8_t getSize() const {
            return size_;
        }

        void set(const Register& rhs) {
            clearInternal();
            int8_t size = size_ >= rhs.getSize() ? rhs.size_ : size_;
            assert(size > 0);
            for (int8_t i = 0; i < size; i++)
                data_[i] = rhs.data_[i];
            pointPos_ = rhs.pointPos_;
            negative_ = rhs.negative_;
            hasError_ = rhs.hasError_;
            notify();
        }

        void setOne() {
            clearInternal();
            data_[0] = 1;
            notify();
        }

        void setChangedCallback(const RegisterChangedCallback changedCallback) {
            changedCallback_ = changedCallback;
        }

        RegisterChangedCallback getChangedCallback() {
            return changedCallback_;
        }

        bool isZero() {
            return isZero(false);
        }

        bool isZero(bool ignorePointPos) {
            for (int8_t i = 0; i < size_; i++)
                if (data_[i] > 0)
                    return false;
            return ignorePointPos ? true : pointPos_ == 0;
        }

        bool operator==(const Register& other) {
            return isEqual(*this, other);
        }

        bool operator!=(const Register& other) {
            return !isEqual(*this, other);
        }


        inline int8_t& getDigit(const int8_t index) {
            return data_[index];
        };

        inline const int8_t& getDigit(const int8_t index) const {
            return data_[index];
        };

        inline void setDigit(const int8_t index, const int8_t value) {
            data_[index] = value;
            notify();
        }

        inline void incDigit(const int8_t index, const int8_t delta) {
            int8_t digit = data_[index] + delta;
            setDigit(index, digit);
        }

        inline int8_t getPointPos() {
            return pointPos_;
        }

        inline void setPointPos(const int8_t value) {
            pointPos_ = value;
            notify();
        }

        inline void incPointPos(const int8_t delta) {
            setPointPos(pointPos_ + delta);
        }

        inline bool isNegative() {
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

        inline bool hasError() {
            return hasError_;
        }

        inline void setError(const bool value) {
            hasError_ = value;
            notify();
        }

        static bool isEqual(const Register& lhs, const Register& rhs) {
            if (lhs.size_ != rhs.size_)
                return false;
            for (int8_t i = 0; i < lhs.size_; i++)
                if (lhs.data_[i] != rhs.data_[i])
                    return false;
            return lhs.pointPos_ == rhs.pointPos_ &&
                   lhs.negative_ == rhs.negative_ &&
                   lhs.hasError_ == rhs.hasError_;
        }
    private:
        int8_t size_;
        int8_t* data_;
        int8_t pointPos_ = 0;
        bool negative_ = false;
        bool hasError_ = false;

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
            for (int8_t i = 0; i < size_; i++)
                data_[i] = 0;
            pointPos_ = 0;
            negative_ = false;
            hasError_ = false;
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
