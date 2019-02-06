//
// Created by dmitrydzz on 10.01.19.
//

#include "calculator/math.h"

using calculatorcomrade::Math;

#define S1 ((int8_t)1)
#define S2 ((int8_t)2)

void Math::calculate(Register &r1, Register &r2, const Operation &operation) {
    switch (operation) {
        case Operation::add:
            add(r1, r2);
            break;
        case Operation::sub:
            sub(r1, r2);
            break;
        case Operation::mul:
            mul(r1, r2);
            break;
        case Operation::div:
            div(r1, r2);
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

void Math::doubleSizedRegisterToSingle(Register &r2, Register &r) {
    int8_t size = r.getSize();
    int8_t size2 = r2.getSize();

    int8_t pointPos = r2.getPointPos();

    int8_t firstDigitIndex = 0;
    for (int8_t i = size2 - S1; i >= 0; i--) {
        if (r2.getDigit(i) > 0) {
            firstDigitIndex = i;
            break;
        }
    }
    if (firstDigitIndex < pointPos)
        firstDigitIndex = pointPos;

    int8_t overflowPos = 0;
    while (firstDigitIndex >= size) {
        unsafeShiftRight(r2, false);
        if (pointPos == 0) overflowPos++;
        else pointPos--;
        firstDigitIndex--;
    }
    r2.setError(overflowPos > 0);
    r2.setPointPos(overflowPos > 0 ? size - overflowPos : pointPos);
    if (r2.isZero(true))
        r2.setNegative(false);

    r.set(r2);
}

void Math::add(Register &r1, Register &r2) {
    int8_t size = r1.getSize();
    assert(size == r2.getSize());
    int8_t size2 = size + size;

    // This could be done (and it is) in addInternal() method.
    // See TestSpecial.RegisterYChanged test for details.
    normalizePointPositions(r1, r2);

    Register r1ex(size2);
    Register r2ex(size2);
    r1ex.setChangedCallback(r1.getChangedCallback());
    r2ex.setChangedCallback(r2.getChangedCallback());
    r1ex.set(r1);
    r2ex.set(r2);

    Math::addInternal(r1ex, r2ex);

    r1.setChangedCallback(r1ex.getChangedCallback());
    r2.setChangedCallback(r2ex.getChangedCallback());
    doubleSizedRegisterToSingle(r1ex, r1);
    doubleSizedRegisterToSingle(r2ex, r2);
    Math::truncRightZeros(r1);
    Math::truncRightZeros(r2);
}

void Math::addInternal(Register &r1, Register &r2) {
    int8_t size = r1.getSize();
    assert(size == r2.getSize());

    normalizePointPositions(r1, r2);

    if (r1.isNegative() == r2.isNegative()) { // (same sign)
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
            r1.setError(true);
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
            r1.setNegative(r2.isNegative());
        } else { // |r1|==|r2|
            r1.clear();
        }
    }
}

void Math::sub(Register &r1, Register &r2) {
    r1.switchNegative();
    add(r1, r2);
    r1.switchNegative();
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
            Math::addInternal(acc, r2ex);
        }
        if (i > 0) {
            safeShiftLeft(acc, false);
            acc.setPointPos(0);
        }
    }

    acc.setNegative(r1.isNegative() != r2.isNegative());
    acc.setPointPos(r1.getPointPos() + r2.getPointPos());
    doubleSizedRegisterToSingle(acc, r1);
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
    int8_t size2 = size + size;
    assert(size == r2.getSize());
    assert(size2 == acc.getSize());

    if (r2.isZero(true)) {
        r1.clear();
        r1.setError(true);
        return;
    }

    bool negative = r1.isNegative() != r2.isNegative();

    acc.set(r1);
    acc.setNegative(false);

    Register r2ex(size2);
    r2ex.set(r2);
    r2ex.setChangedCallback(r2.getChangedCallback());
    r2ex.setNegative(true); // Make it negative to sum with positive acc later.
    r2.setChangedCallback(nullptr);

    normalizePointPositions(acc, r2ex);

    // Prepare for the result:
    Register r1ex(size2);
    r1ex.setChangedCallback(r1.getChangedCallback());
    r1.setChangedCallback(nullptr);

    if (compareIgnoreSign(acc, r2ex) >= 0) {
        // Shift r2ex to the very right:
        int8_t lastIndex2 = size2 - S1;
        int8_t shifts = 0;
        while (r2ex.getDigit(lastIndex2) == 0)
            if (safeShiftLeft(r2ex, false)) shifts++;
            else break;
        acc.setPointPos(0);
        r2ex.setPointPos(0);

        for (int8_t i = 0; i <= shifts; i++) {
            int8_t digit = 0;
            if (compareIgnoreSign(acc, r2ex) >= 0) {
                while (compareIgnoreSign(acc, r2ex) >= 0) {
                    addInternal(acc, r2ex);
                    digit++;
                }
            }
            safeShiftLeft(r1ex, false);
            r1ex.setDigit(0, digit);

            if (i < shifts)
                unsafeShiftRight(r2ex, false);
        }
    }

    if (!acc.isZero(true)) { // (there is a remainder in acc)
        r1ex.setPointPos(0);
        for (int8_t j = 0; j < size2; j++) {
            safeShiftLeft(acc, false);

            int8_t digit = 0;
            if (compareIgnoreSign(acc, r2ex) >= 0) {
                while (compareIgnoreSign(acc, r2ex) >= 0) {
                    addInternal(acc, r2ex);
                    digit++;
                }
            }

            bool canShift = safeShiftLeft(r1ex, true);
            if (canShift)
                r1ex.setDigit(0, digit);
        }
    }

    r1ex.setNegative(negative);

    r1.setChangedCallback(r1ex.getChangedCallback());
    r2.setChangedCallback(r2ex.getChangedCallback());

    doubleSizedRegisterToSingle(r1ex, r1);
    truncRightZeros(r1);
}

void Math::calculatePercent(Register &r1, Register &r2, const Operation &operation) {
    switch (operation) {
        case Operation::add:
            addPercent(r1, r2);
            break;
        case Operation::sub:
            subPercent(r1, r2);
            break;
        case Operation::mul:
            mulPercent(r1, r2);
            break;
        case Operation::div:
            divPercent(r1, r2);
            break;
    }
}

void Math::addPercent(Register &r1ex, Register &r2ex, Register &accEx) {
    bool negative = r1ex.isNegative() != r2ex.isNegative();

    // Percent to acc:
    // 1. r1ex copy to accEx
    // 2. accEx = accEx / 100 * r2ex
    accEx.set(r1ex);
    accEx.setPointPos(r1ex.getPointPos() + S2);
    mul(accEx, r2ex);
    accEx.setNegative(negative);

    // Source value (first operand) to r2ex:
    r2ex.set(r1ex);
    // Result to r1ex: percent + source value
    r1ex.set(accEx);
    add(r1ex, r2ex);

    // Some white magic according to tests on real calculators:
    r2ex.setNegative(negative);
}

void Math::addPercent(Register &r1, Register &r2) {
    int8_t size = r1.getSize();
    int8_t size2 = size + size;
    assert(size == r2.getSize());

    Register r1ex(size2);
    Register r2ex(size2);
    Register accEx(size2);
    r1ex.setChangedCallback(r1.getChangedCallback());
    r2ex.setChangedCallback(r2.getChangedCallback());
    r1.setChangedCallback(nullptr);
    r2.setChangedCallback(nullptr);
    r1ex.set(r1);
    r2ex.set(r2);

    addPercent(r1ex, r2ex, accEx);

    // Some white magic according to tests on real calculators:
    r2.set(r1);
    r2.setNegative(accEx.isNegative());

    r1.setChangedCallback(r1ex.getChangedCallback());
    r2.setChangedCallback(r2ex.getChangedCallback());

    doubleSizedRegisterToSingle(r1ex, r1);
    truncRightZeros(r1);
}

void Math::subPercent(Register &r1, Register &r2) {
    int8_t size = r1.getSize();
    int8_t size2 = size + size;
    assert(size == r2.getSize());

    Register r1ex(size2);
    Register r2ex(size2);
    Register accEx(size2);
    r1ex.setChangedCallback(r1.getChangedCallback());
    r2ex.setChangedCallback(r2.getChangedCallback());
    r1.setChangedCallback(nullptr);
    r2.setChangedCallback(nullptr);
    r1ex.set(r1);
    r2ex.set(r2);

    r2ex.switchNegative();
    addPercent(r1ex, r2ex, accEx);

    // Some white magic according to tests on real calculators:
    r2.set(r1);
    r2.setNegative(!accEx.isNegative());

    r1.setChangedCallback(r1ex.getChangedCallback());
    r2.setChangedCallback(r2ex.getChangedCallback());

    doubleSizedRegisterToSingle(r1ex, r1);
    truncRightZeros(r1);
}

void Math::mulPercent(Register &r1, Register &r2) {
    int8_t size = r1.getSize();
    int8_t size2 = size + size;
    assert(size == r2.getSize());

    bool negative = r1.isNegative() != r2.isNegative();

    Register r1ex(size2);
    Register r2ex(size2);
    r1ex.setChangedCallback(r1.getChangedCallback());
    r2ex.setChangedCallback(r2.getChangedCallback());
    r1.setChangedCallback(nullptr);
    r2.setChangedCallback(nullptr);
    r1ex.set(r1);
    r2ex.set(r2);

    // r1ex / 100:
    r1ex.setPointPos(r1ex.getPointPos() + S2);

    mul(r1ex, r2ex);

    r1ex.setNegative(negative);

    r1.setChangedCallback(r1ex.getChangedCallback());
    r2.setChangedCallback(r2ex.getChangedCallback());

    doubleSizedRegisterToSingle(r1ex, r1);
    truncRightZeros(r1);
}

void Math::divPercent(Register &r1, Register &r2) {
    int8_t size = r1.getSize();
    int8_t size2 = size + size;
    assert(size == r2.getSize());

    bool negative = r1.isNegative() != r2.isNegative();

    Register r1ex(size2);
    Register r2ex(size2);
    r1ex.setChangedCallback(r1.getChangedCallback());
    r2ex.setChangedCallback(r2.getChangedCallback());
    r1.setChangedCallback(nullptr);
    r2.setChangedCallback(nullptr);
    r1ex.set(r1);
    r2ex.set(r2);

    // r1ex * 100:
    safeShiftLeft(r1ex, false);
    safeShiftLeft(r1ex, false);

    div(r1ex, r2ex);

    r1ex.setNegative(negative);

    r1.setChangedCallback(r1ex.getChangedCallback());
    r2.setChangedCallback(r2ex.getChangedCallback());

    doubleSizedRegisterToSingle(r1ex, r1);
    truncRightZeros(r1);
}

void Math::sqrt(Register &r) {
    //TODO DZZ sqrt(99999998) = 9999.9998 (should be)
    r.clear();
    r.setDigit(0, 3);
}

void Math::changeSign(Register &r) {
    r.switchNegative();
}
