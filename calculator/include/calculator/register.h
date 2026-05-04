/**
 * Calculator Comrade Library
 * License: https://github.com/DmitryDzz/calculator-comrade-lib/blob/master/LICENSE
 * Author: Dmitry Dzakhov
 * Email: info@robot-mitya.ru
 */
#ifndef CALCULATORCOMRADE_REGISTER_H
#define CALCULATORCOMRADE_REGISTER_H

#include <cassert>

#include "calculator/types.h"
#include "calculator/config.h"

namespace calculatorcomrade {
    constexpr CalcInt SM1 = -1;
    constexpr CalcInt S0 = 0;
    constexpr CalcInt S1 = 1;
    constexpr CalcInt S2 = 2;
    constexpr CalcInt S9 = 9;
    constexpr CalcInt S10 = 10;

    class Register;

    using RegisterChangedCallback = void(*)(Register &r);

    class Register {
    public:
        Register() = delete;
        explicit Register(const CalcInt size) : size_(size) {
            assert(size > 0);
            clearInternal();
        }

        void clear() {
            clearInternal();
            notify();
        }

        CalcInt getSize() const {
            return size_;
        }

        void set(const Register& rhs) {
            clearInternal();
            const CalcInt size = size_ >= rhs.size_ ? rhs.size_ : size_;
            assert(size > 0);
            for (CalcInt i = 0; i < size; i++) {
                data_[i] = rhs.data_[i];
            }
            pointPos_ = rhs.pointPos_;
            negative_ = rhs.negative_;
            hasError_ = rhs.hasError_;
            hasOverflow_ = rhs.hasOverflow_;
            notify();
        }

        void setSafe(const Register& rhs) {
            assert(size_ + size_ >= rhs.size_);
            assert(!rhs.hasError_);
            assert(!rhs.hasOverflow_);
            clearInternal();
            if (size_ < rhs.size_) {
                CalcInt firstSrcIndex = 0;
                for (CalcInt i = rhs.size_ - S1; i >= 0; i--) {
                    if (rhs.data_[i] != 0) {
                        firstSrcIndex = i;
                        break;
                    }
                }
                const CalcInt srcPointPos = rhs.pointPos_;
                if (srcPointPos > firstSrcIndex)
                    firstSrcIndex = srcPointPos;
                const CalcInt firstDstIndex = firstSrcIndex < size_ ? firstSrcIndex : size_ - S1;
                CalcInt srcIndex = firstSrcIndex;
                CalcInt dstIndex = firstDstIndex;
                CalcInt dstPointPos = -S1;
                for (CalcInt i = 0; i < size_; i++) { // (maximum size_ iterations)
                    data_[dstIndex] = rhs.data_[srcIndex];
                    if (srcPointPos == srcIndex) {
                        pointPos_ = dstIndex;
                        dstPointPos = dstIndex;
                    }
                    if (srcIndex == 0) break;
                    srcIndex--;
                    if (dstIndex == 0) break;
                    dstIndex--;
                }
                if (dstPointPos < 0) {
                    setPointPos(size_ - (srcIndex - srcPointPos + S1));
                    hasError_ = true; // (overflow)
                    hasOverflow_ = true;
                }
                negative_ = rhs.negative_;
            } else {
                const CalcInt size = rhs.size_;
                for (CalcInt i = 0; i < size; i++)
                    data_[i] = rhs.data_[i];
                pointPos_ = rhs.pointPos_;
                negative_ = rhs.negative_;
                hasError_ = rhs.hasError_;
                hasOverflow_ = rhs.hasOverflow_;
            }
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

        RegisterChangedCallback getChangedCallback() const {
            return changedCallback_;
        }

        bool isZero() const {
            return isZero(false);
        }

        bool isZero(const bool ignorePointPos) const {
            for (CalcInt i = 0; i < size_; i++)
                if (data_[i] > 0)
                    return false;
            return ignorePointPos ? true : pointPos_ == 0;
        }

        bool operator==(const Register& other) const {
            return isEqual(*this, other);
        }

        bool operator!=(const Register& other) const {
            return !isEqual(*this, other);
        }

        CalcDigit& getDigit(const CalcInt index) {
            return data_[index];
        }

        const CalcDigit& getDigit(const CalcInt index) const {
            return data_[index];
        }

        CalcDigit getDisplayDigit(const CalcInt index) const {
            if (data_[index] > 0 || pointPos_ >= index) return data_[index];

            bool hasNonZeroDigitsToTheRight = false;
            for (CalcInt i = index + S1; i < size_; i++) {
                hasNonZeroDigitsToTheRight = data_[i] > 0;
                if (hasNonZeroDigitsToTheRight) break;
            }
            return static_cast<CalcDigit>(hasNonZeroDigitsToTheRight ? S0 : SM1);
        }

        void setDigit(const CalcInt index, const CalcDigit value) {
            data_[index] = value;
            notify();
        }

        void incDigit(const CalcInt index, const CalcDigit delta) {
            const CalcInt digit = data_[index] + delta;
            setDigit(index, static_cast<CalcDigit>(digit));
        }

        CalcInt getPointPos() const {
            return pointPos_;
        }

        void setPointPos(const CalcInt value) {
            pointPos_ = value;
            notify();
        }

        void incPointPos(const CalcInt delta) {
            setPointPos(pointPos_ + delta);
        }

        bool isNegative() const {
            return negative_;
        }

        void setNegative(const bool value) {
            negative_ = isZero(true) ? false : value;
            notify();
        }

        void switchNegative() {
            setNegative(!negative_);
        }

        bool hasError() const {
            return hasError_;
        }

        bool hasOverflow() const {
            return hasOverflow_;
        }

        void setError(const bool hasError, const bool hasOverflow) {
            hasError_ = hasError;
            hasOverflow_ = hasOverflow;
            notify();
        }

        static bool isEqual(const Register& lhs, const Register& rhs) {
            if (lhs.size_ != rhs.size_)
                return false;
            for (CalcInt i = 0; i < lhs.size_; i++)
                if (lhs.data_[i] != rhs.data_[i])
                    return false;
            return lhs.pointPos_ == rhs.pointPos_ &&
                   lhs.negative_ == rhs.negative_ &&
                   lhs.hasError_ == rhs.hasError_ &&
                   lhs.hasOverflow_ == rhs.hasOverflow_;
        }
    private:
        CalcInt size_;
        CalcDigit data_[Config::MAX_SIZE * 2]{}; // *2 in case r*r
        CalcInt pointPos_ = 0;
        bool negative_ = false;
        bool hasError_ = false;
        bool hasOverflow_ = false;

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
            for (CalcInt i = 0; i < size_; i++)
                data_[i] = 0;
            pointPos_ = 0;
            negative_ = false;
            hasError_ = false;
            hasOverflow_ = false;
        }
    };

    // inline bool operator==(const Register& lhs, const Register& rhs) {
    //     return Register::isEqual(lhs, rhs);
    // }
    //
    // inline bool operator!=(const Register& lhs, const Register& rhs) {
    //     return !Register::isEqual(lhs, rhs);
    // }
}

#endif //CALCULATORCOMRADE_REGISTER_H
