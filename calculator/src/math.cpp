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
void Math::unsafeShiftRight(Register &r, const bool updatePointPos) {
    uint8_t digits = r.getDigits();
    if (digits == 0) return;
    for (uint8_t i = 1; i < digits; i++) {
        r.setDigit(i - U1, r.getDigit(i));
    }
    r.setDigit(digits - U1, 0);
    if (updatePointPos && r.getPointPos() > 0)
        r.incPointPos(-1);
}

// "safe" means that left shift will be performed
// until there is a non-zero value in the highest digit.
void Math::safeShiftLeft(Register &r, const bool updatePointPos) {
    uint8_t digits = r.getDigits();
    if (digits == 0) return;
    auto lastIndex = static_cast<uint8_t>(digits - 1);
    if (r.getDigit(digits - U1) != 0 || r.getPointPos() == lastIndex) return;
    for (auto i = lastIndex; i >= 1; i--) {
        r.setDigit(i, r.getDigit(i - U1));
    }
    r.setDigit(0, 0);
    if (updatePointPos)
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
        safeShiftLeft(rL, true);
        if (r1.getPointPos() == r2.getPointPos()) return;
    }

    // Than shift right the other register until pointPos's are equal.
    for (uint8_t i = 0; i < digits; i++) {
        unsafeShiftRight(rR, true);
        if (r1.getPointPos() == r2.getPointPos()) return;
    }
}

void Math::truncRightZeros(Register &r) {
    uint8_t digits = r.getDigits();
    if (digits == 0) return;

    for (uint8_t i = 0; i < digits; i++) {
        if (r.getDigit(0) != 0 || r.getPointPos() == 0) break;
        unsafeShiftRight(r, true);
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
            unsafeShiftRight(r1, false);
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

    Register acc(digits + digits);
    Math::mul(r1, r2, acc);
}

void Math::mul(Register &r1, Register &r2, Register &acc) {
    int8_t digits = r1.getDigits();
    assert(digits > 0);
    assert(digits == r2.getDigits());
    assert(digits * 2 == acc.getDigits());

    Register r2ex(acc.getDigits());
    r2ex.set(r2);
    r2ex.setPointPos(0);
    r2ex.setNegative(false);

    acc.clear();
    int8_t lastRegIndex = digits - U1;
    for (int8_t i = lastRegIndex; i >= 0; i--) {
        uint8_t digit = r1.getDigit(i);
        for (int8_t j = 0; j < digit; j++) {
            Math::sum(acc, r2ex, false);
        }
        if (i > 0) {
            safeShiftLeft(acc, false);
            acc.setPointPos(0);
        }
    }

    int8_t accSize = acc.getDigits();
    int8_t firstDigitIndex = 0;
    for (int8_t i = accSize - U1; i >= 0; i--) {
        if (acc.getDigit(i) > 0) {
            firstDigitIndex = i;
            break;
        }
    }

    int8_t pointPos = r1.getPointPos() + r2.getPointPos();
    int8_t overflowPos = 0;
    while (firstDigitIndex > lastRegIndex) {
        unsafeShiftRight(acc, false);
        if (pointPos == 0) overflowPos++;
        else pointPos--;
        firstDigitIndex--;
    }
    acc.setOverflow(overflowPos > 0);
    acc.setPointPos(overflowPos > 0 ? digits - overflowPos : pointPos);
    acc.setNegative(acc.isZeroData() ? false : r1.getNegative() != r2.getNegative());

    r1.set(acc);
    truncRightZeros(r1);
}
