//
// Created by dmitrydzz on 10.01.19.
//

#include "calculator/math.h"

using calculatorcomrade::Math;

#define S1 ((int8_t)1)

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
    int8_t size = r.getSize();
    for (int8_t i = 1; i < size; i++) {
        r.setDigit(i - S1, r.getDigit(i));
    }
    r.setDigit(size - S1, 0);
    if (updatePointPos && r.getPointPos() > 0)
        r.incPointPos(-1);
}

// "safe" means that left shift will be performed
// until there is a non-zero value in the highest digit.
bool Math::safeShiftLeft(Register &r, const bool updatePointPos) {
    int8_t size = r.getSize();
    int8_t lastIndex = size - S1;
    if (r.getDigit(size - S1) != 0 || r.getPointPos() == lastIndex) return false;
    for (auto i = lastIndex; i >= 1; i--) {
        r.setDigit(i, r.getDigit(i - S1));
    }
    r.setDigit(0, 0);
    if (updatePointPos)
        r.incPointPos(+1);
    return true;
}

int8_t Math::compareIgnoreSign(const Register &r1, const Register &r2) {
    int8_t size = r1.getSize();
    if (size != r2.getSize()) return 0;
    for (int8_t i = 0; i < size; i++) {
        int8_t index = size - i - S1;
        if (r1.getDigit(index) > r2.getDigit(index))
            return 1;
        else if (r1.getDigit(index) < r2.getDigit(index))
            return -1;
    }
    return 0;
}

void Math::normalizePointPositions(Register &r1, Register &r2) {
    int8_t size = r1.getSize();
    if (size != r2.getSize() || r1.getPointPos() == r2.getPointPos()) return;

    Register &rL = r1.getPointPos() < r2.getPointPos() ? r1 : r2;
    Register &rR = r1.getPointPos() > r2.getPointPos() ? r1 : r2;

    // First shift left the register where pointPos is smaller.
    for (int8_t i = 0; i < size; i++) {
        if (rL.getDigit(size - S1) != 0) break;
        safeShiftLeft(rL, true);
        if (r1.getPointPos() == r2.getPointPos()) return;
    }

    // Than shift right the other register until pointPos's are equal.
    for (int8_t i = 0; i < size; i++) {
        unsafeShiftRight(rR, true);
        if (r1.getPointPos() == r2.getPointPos()) return;
    }
}

void Math::truncRightZeros(Register &r) {
    int8_t size = r.getSize();
    for (int8_t i = 0; i < size; i++) {
        if (r.getDigit(0) != 0 || r.getPointPos() == 0) break;
        unsafeShiftRight(r, true);
    }
}

void Math::sum(Register &r1, Register &r2) {
    Math::sum(r1, r2, true);
}

void Math::sum(Register &r1, Register &r2, bool truncRightZeros) {
    int8_t size = r1.getSize();
    assert(size == r2.getSize());

    normalizePointPositions(r1, r2);

    if (r1.getNegative() == r2.getNegative()) { // (same sign)
        bool extraDigit = false;
        for (int8_t i = 0; i < size; i++) {
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
            r1.setDigit(size - S1, 1);
            r1.setPointPos(size - S1);
        }
    } else { // (different signs)
        int8_t comparision = compareIgnoreSign(r1, r2);
        int8_t borrowedDigit = 0;
        int8_t srcDigit;
        if (comparision == 1) { // |r1| > |r2|
            for (int8_t i = 0; i < size; i++) {
                srcDigit = r1.getDigit(i) - borrowedDigit;
                if (srcDigit < r2.getDigit(i)) {
                    r1.setDigit(i, (int8_t)(srcDigit + 10 - r2.getDigit(i)));
                    borrowedDigit = 1;
                } else {
                    r1.setDigit(i, srcDigit - r2.getDigit(i));
                    borrowedDigit = 0;
                }
            }
        } else if (comparision == -1) { // |r1| < |r2|
            for (int8_t i = 0; i < size; i++) {
                srcDigit = r2.getDigit(i) - borrowedDigit;
                if (srcDigit < r1.getDigit(i)) {
                    r1.setDigit(i, (int8_t)(srcDigit + 10 - r1.getDigit(i)));
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
    int8_t size = r1.getSize();
    assert(size == r2.getSize());

    Register acc(size + size);
    Math::mul(r1, r2, acc);
}

void Math::mul(Register &r1, Register &r2, Register &acc) {
    int8_t size = r1.getSize();
    assert(size == r2.getSize());
    assert(size * 2 == acc.getSize());

    Register r2ex(acc.getSize());
    r2ex.set(r2);
    r2ex.setPointPos(0);
    r2ex.setNegative(false);

    acc.clear();
    int8_t lastRegIndex = size - S1;
    for (int8_t i = lastRegIndex; i >= 0; i--) {
        int8_t digit = r1.getDigit(i);
        for (int8_t j = 0; j < digit; j++) {
            Math::sum(acc, r2ex, false);
        }
        if (i > 0) {
            safeShiftLeft(acc, false);
            acc.setPointPos(0);
        }
    }

    int8_t accSize = acc.getSize();
    int8_t firstDigitIndex = 0;
    for (int8_t i = accSize - S1; i >= 0; i--) {
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
    acc.setPointPos(overflowPos > 0 ? size - overflowPos : pointPos);
    acc.setNegative(acc.isZero() ? false : r1.getNegative() != r2.getNegative());

    r1.set(acc);
    truncRightZeros(r1);
}

void Math::div(Register &r1, Register &r2) {
    int8_t size = r1.getSize();
    assert(size == r2.getSize());

    Register acc(size + size);
    Math::div(r1, r2, acc);
}

void Math::div(Register &r1, Register &r2, Register &acc) {
    int8_t size = r1.getSize();
    assert(size == r2.getSize());
    assert(size * 2 == acc.getSize());

    if (r2.isZero()) {
        r1.clear();
        r1.setOverflow(true);
        return;
    }

    bool negative = r1.getNegative() != r2.getNegative();

    acc.set(r1);
    acc.setNegative(false);

    Register r2ex(acc.getSize());
    r2ex.set(r2);
    r2ex.setChangedCallback(r2.getChangedCallback());
    r2ex.setNegative(true); // Make it negative to sum with positive acc later.
    r2.setChangedCallback(nullptr);

    normalizePointPositions(acc, r2ex);

    // Prepare for the result:
    r1.clear();

    int8_t overflowPos = 0;
    if (compareIgnoreSign(acc, r2ex) >= 0) {
        // Shift r2ex to the very right:
        int8_t lastIndex = acc.getSize() - S1;
        while (r2ex.getDigit(lastIndex) == 0)
            safeShiftLeft(r2ex, false);
        acc.setPointPos(0);
        r2ex.setPointPos(0);

        for (int8_t i = 0; i <= lastIndex; i++) {
            int8_t digit = 0;
            if (compareIgnoreSign(acc, r2ex) >= 0) {
                while (compareIgnoreSign(acc, r2ex) >= 0) {
                    sum(acc, r2ex);
                    digit++;
                }
            }
            bool canShift = safeShiftLeft(r1, false);
            if (!canShift) {
                overflowPos++;
                break;
            }
            r1.setDigit(0, digit);

            if (i < lastIndex)
                unsafeShiftRight(r2ex, false);
        }
    }

    if (!acc.isZero()) { // (there is a remainder in acc)
        r1.setPointPos(0);
        for (int8_t j = 0; j < size; j++) {
            safeShiftLeft(acc, false);

            int8_t digit = 0;
            if (compareIgnoreSign(acc, r2ex) >= 0) {
                while (compareIgnoreSign(acc, r2ex) >= 0) {
                    sum(acc, r2ex);
                    digit++;
                }
            }

            bool canShift = safeShiftLeft(r1, true);
            if (canShift)
                r1.setDigit(0, digit);
        }
    }

    r2.setChangedCallback(r2.getChangedCallback());

    r1.setNegative(negative);
    r1.setOverflow(overflowPos > 0);
    if (overflowPos > 0)
        r1.setPointPos(size - overflowPos);
    truncRightZeros(r1);
}