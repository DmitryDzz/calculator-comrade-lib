//
// Created by dmitrydzz on 10.01.19.
//

#include <calculator/math.h>

using calculatorcomrade::Math;

void Math::calculate(Register &r1, Register &r2, const Operation &operation) {
    switch (operation) {
        case Operation::add:
            sum(r1, r2);
            break;
        case Operation::sub:
            r1.negative = !r1.negative;
            sum(r1, r2);
            r1.negative = !r1.negative;
            break;
        case Operation::mul:
            //TODO DZZ mul
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
        r[i - 1] = r[i];
    }
    r[digits - 1] = 0;
    if (r.pointPos > 0)
        r.pointPos -= 1;
}

// "safe" means that left shift will be performed
// until there is a non-zero value in the highest digit.
void Math::safeShiftLeft(Register &r) {
    uint8_t digits = r.getDigits();
    auto lastIndex = static_cast<uint8_t>(digits - 1);
    if (digits == 0 || r[digits - 1] != 0 || r.pointPos == lastIndex) return;
    for (auto i = lastIndex; i >= 1; i--) {
        r[i] = r[i - 1];
    }
    r[0] = 0;
    r.pointPos += 1;
}

void Math::sum(Register &r1, Register &r2) {
    bool error = r1.getDigits() != r2.getDigits();
    error |= r1.getDigits() == 0;
    error |= r2.getDigits() == 0;
    if (error) {
        r1.clear();
        r1.overflow = true; // just indicate an error
        return;
    }

    normalizePointPositions(r1, r2);

    uint8_t digits = r1.getDigits();
    if (r1.negative == r2.negative) { // (same sign)
        bool extraDigit = false;
        for (uint8_t i = 0; i < digits; i++) {
            r1[i] = r1[i] + r2[i];
            if (extraDigit)
                r1[i] += 1;

            extraDigit = r1[i] > 9;
            if (extraDigit) {
                r1[i] -= 10;
            }
        }

        if (extraDigit) {
            r1.overflow = true;
            r1.pointPos = digits;
            unsafeShiftRight(r1);
            r1[digits - 1] = 1;
        }
    } else { // (different signs)
        int8_t comparision = compareIgnoreSign(r1, r2);
        if (comparision == 1) { // |r1| > |r2|
            for (uint8_t i = 0; i < digits; i++) {
                r1[i] = r1[i] < r2[i] ? (uint8_t)(r1[i] + 10 - r2[i]) : r1[i] - r2[i];
            }
        } else if (comparision == -1) { // |r1| < |r2|
            for (uint8_t i = 0; i < digits; i++) {
                r1[i] = r2[i] < r1[i] ? (uint8_t)(r2[i] + 10 - r1[i]) : r2[i] - r1[i];
            }
            r1.negative = r2.negative;
        } else { // |r1|==|r2|
            r1.clear();
        }
    }

    truncRightZeros(r1);
    truncRightZeros(r2);
}

int8_t Math::compareIgnoreSign(const Register &r1, const Register &r2) {
    uint8_t digits = r1.getDigits();
    if (digits == 0) return 0;
    if (digits != r2.getDigits()) return 0;
    for (auto i = static_cast<uint8_t>(digits - 1); i >= 0; i--) {
        if (r1[i] > r2[i])
            return 1;
        else if (r1[i] < r2[i])
            return -1;
    }
    return 0;
}

void Math::normalizePointPositions(Register &r1, Register &r2) {
    uint8_t digits = r1.getDigits();
    if (digits == 0 || digits != r2.getDigits() || r1.pointPos == r2.pointPos) return;

    Register &rL = r1.pointPos < r2.pointPos ? r1 : r2;
    Register &rR = r1.pointPos > r2.pointPos ? r1 : r2;

    // First shift left the register where pointPos is smaller.
    for (uint8_t i = 0; i < digits; i++) {
        if (rL[digits - 1] != 0) break;
        safeShiftLeft(rL);
        if (r1.pointPos == r2.pointPos) return;
    }

    // Than shift right the other register until pointPos's are equal.
    for (uint8_t i = 0; i < digits; i++) {
        unsafeShiftRight(rR);
        if (r1.pointPos == r2.pointPos) return;
    }
}

void Math::truncRightZeros(Register &r) {
    uint8_t digits = r.getDigits();
    if (digits == 0) return;

    for (uint8_t i = 0; i < digits; i++) {
        if (r[0] != 0 || r.pointPos == 0) break;
        unsafeShiftRight(r);
    }
}

