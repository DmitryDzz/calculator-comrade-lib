//
// Created by dmitrydzz on 10.01.19.
//

#include <calculator/math.h>

using calculatorcomrade::Math;

#define U1 ((uint8_t)1)

void Math::calculate(Register &r1, Register &r2, const Operation &operation) {
    switch (operation) {
        case Operation::add:
            sum(r1, r2);
            break;
        case Operation::sub:
            r1.switchNegative();
            sum(r1, r2);
            r1.switchNegative();
            break;
        case Operation::mul:
            mul(r1, r2);
            break;
        case Operation::div:
            //TODO DZZ div
            break;
        default:
            //TODO DZZ %, ...
            break;
    }
}

// "unsafe" means that right shift will be performed
// even if the lowest digit is lost.
void Math::unsafeShiftRight(Register &r) {
    uint8_t digits = r.getDigits();
    if (digits == 0) return;
    for (uint8_t i = 1; i < digits; i++) {
        r.setDigit(i - U1, r.getDigit(i));
    }
    r.setDigit(digits - U1, 0);
    if (r.getPointPos() > 0)
        r.incPointPos(-1);
}

// "safe" means that left shift will be performed
// until there is a non-zero value in the highest digit.
void Math::safeShiftLeft(Register &r) {
    uint8_t digits = r.getDigits();
    if (digits == 0) return;
    auto lastIndex = static_cast<uint8_t>(digits - 1);
    if (r.getDigit(digits - U1) != 0 || r.getPointPos() == lastIndex) return;
    for (auto i = lastIndex; i >= 1; i--) {
        r.setDigit(i, r.getDigit(i - U1));
    }
    r.setDigit(0, 0);
    r.incPointPos(+1);
}

int8_t Math::compareIgnoreSign(const Register &r1, const Register &r2) {
    uint8_t digits = r1.getDigits();
    if (digits == 0) return 0;
    if (digits != r2.getDigits()) return 0;
    for (uint8_t i = 0; i < digits; i++) {
        uint8_t index = digits - i - (uint8_t)1;
        if (r1.getDigit(index) > r2.getDigit(index))
            return 1;
        else if (r1.getDigit(index) < r2.getDigit(index))
            return -1;
    }
    return 0;
}

void Math::normalizePointPositions(Register &r1, Register &r2) {
    uint8_t digits = r1.getDigits();
    if (digits == 0 || digits != r2.getDigits() || r1.getPointPos() == r2.getPointPos()) return;

    Register &rL = r1.getPointPos() < r2.getPointPos() ? r1 : r2;
    Register &rR = r1.getPointPos() > r2.getPointPos() ? r1 : r2;

    // First shift left the register where pointPos is smaller.
    for (uint8_t i = 0; i < digits; i++) {
        if (rL.getDigit(digits - U1) != 0) break;
        safeShiftLeft(rL);
        if (r1.getPointPos() == r2.getPointPos()) return;
    }

    // Than shift right the other register until pointPos's are equal.
    for (uint8_t i = 0; i < digits; i++) {
        unsafeShiftRight(rR);
        if (r1.getPointPos() == r2.getPointPos()) return;
    }
}

void Math::truncRightZeros(Register &r) {
    uint8_t digits = r.getDigits();
    if (digits == 0) return;

    for (uint8_t i = 0; i < digits; i++) {
        if (r.getDigit(0) != 0 || r.getPointPos() == 0) break;
        unsafeShiftRight(r);
    }
}

void Math::sum(Register &r1, Register &r2) {
    Math::sum(r1, r2, true);
}

void Math::sum(Register &r1, Register &r2, bool truncRightZeros) {
    uint8_t digits = r1.getDigits();
    if (digits != r2.getDigits() || digits == 0) {
        r1.clear();
        r1.setOverflow(true); // just indicate an error
        return;
    }

    normalizePointPositions(r1, r2);

    if (r1.getNegative() == r2.getNegative()) { // (same sign)
        bool extraDigit = false;
        for (uint8_t i = 0; i < digits; i++) {
            r1.setDigit(i, r1.getDigit(i) + r2.getDigit(i));
            if (extraDigit)
                r1.incDigit(i, 1);

            extraDigit = r1.getDigit(i) > 9;
            if (extraDigit)
                r1.incDigit(i, -10);
        }

        if (extraDigit) {
            r1.setOverflow(true);
            unsafeShiftRight(r1);
            r1.setDigit(digits - U1, 1);
            r1.setPointPos(digits - U1);
        }
    } else { // (different signs)
        int8_t comparision = compareIgnoreSign(r1, r2);
        uint8_t borrowedDigit = 0;
        uint8_t srcDigit;
        if (comparision == 1) { // |r1| > |r2|
            for (uint8_t i = 0; i < digits; i++) {
                srcDigit = r1.getDigit(i) - borrowedDigit;
                if (srcDigit < r2.getDigit(i)) {
                    r1.setDigit(i, (uint8_t)(srcDigit + 10 - r2.getDigit(i)));
                    borrowedDigit = 1;
                } else {
                    r1.setDigit(i, srcDigit - r2.getDigit(i));
                    borrowedDigit = 0;
                }
            }
        } else if (comparision == -1) { // |r1| < |r2|
            for (uint8_t i = 0; i < digits; i++) {
                srcDigit = r2.getDigit(i) - borrowedDigit;
                if (srcDigit < r1.getDigit(i)) {
                    r1.setDigit(i, (uint8_t)(srcDigit + 10 - r1.getDigit(i)));
                    borrowedDigit = 1;
                } else {
                    r1.setDigit(i, srcDigit - r1.getDigit(i));
                    borrowedDigit = 0;
                }
            }
            r1.setNegative(r2.getNegative());
        } else { // |r1|==|r2|
            r1.clear();
        }
    }

    if (truncRightZeros) {
        Math::truncRightZeros(r1);
        Math::truncRightZeros(r2);
    }
}

void Math::mul(Register &r1, Register &r2) {
    uint8_t digits = r1.getDigits();
    if (digits != r2.getDigits() || digits == 0) {
        r1.clear();
        r1.setOverflow(true); // just indicate an error
        return;
    }

    Register ex(digits);
    Math::mul(r1, r2, ex);
}

void Math::mul(Register &r1, Register &r2, Register &r3) {
    uint8_t digits = r1.getDigits();
    if (digits != r2.getDigits() || digits == 0) {
        r1.clear();
        r1.setOverflow(true); // just indicate an error
        return;
    }

    bool negative = r1.getNegative() != r2.getNegative();
    uint8_t pointPos = r1.getPointPos() + r2.getPointPos();
    uint8_t overflowPos = 0;

    r3.set(r1); // r3 is for the first operand. The second one is in r2.
    r3.setNegative(false);
    r3.setPointPos(0);

    r1.clear(); // r1 will accumulate the result value.
    auto lastIndex = static_cast<uint8_t>(digits - 1);
    for (uint8_t i = 0; i < digits; i++) {
        uint8_t digit = r2.getDigit(i);

        if (digit > 0) {
            for (uint8_t j = 0; j < digit; j++) {
                sum(r1, r3, false);
                if (r1.getOverflow()) {
                    r1.setOverflow(false);
                    r1.setPointPos(0);
                    unsafeShiftRight(r3);

                    if (pointPos == 0) overflowPos++;
                    else pointPos--;
                }
            }
        }

        // Break the cycle or shift registers for the next iteration:
        if (i == lastIndex) break;
        bool hasNonZeroDigits = false;
        for (uint8_t j = i; j <= lastIndex; j++) {
            if (r2.getDigit(j) > 0) {
                hasNonZeroDigits = true;
                break;
            }
        }
        if (!hasNonZeroDigits) break;

        // Shift r3 left:
        if (r3.getDigit(lastIndex) > 0) {
            // Cannot shift r3 to the left, so we'll shift the result to the right:
            unsafeShiftRight(r1);

            if (pointPos == 0) overflowPos++;
            else pointPos--;
        } else {
            // Do left shift for r3:
            for (uint8_t j = lastIndex; j >= 1; j--)
                r3.setDigit(j, r3.getDigit(j - U1));
            r3.setDigit(0, 0);
        }
    }

    truncRightZeros(r1);
    r1.setNegative(r1.isZeroData() ? false : negative);
    if (overflowPos > 0) {
        r1.setOverflow(true);
        r1.setPointPos(digits - overflowPos);
    } else {
        r1.setPointPos(pointPos);
    }
}