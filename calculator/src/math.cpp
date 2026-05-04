/**
 * Calculator Comrade Library
 * License: https://github.com/DmitryDzz/calculator-comrade-lib/blob/master/LICENSE
 * Author: Dmitry Dzakhov
 * Email: info@robot-mitya.ru
 */
#include "calculator/math.h"

using calculatorcomrade::Math;
using calculatorcomrade::CalcInt;

void Math::calculate(Register &r1, Register &r2, const Operation &operation, const CalcOptions options) {
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
        case Operation::mu:
            // I'm not sure about this code...
            // Check EqualsAfterMuPercent test in mu_input_tests.cpp.
//            if (!r2.isZero()) {
//                mul(r1, r2);
//                r2.clear();
//            }
            return;
    }

    appendZerosOnOverflow(r1, options);
}

// "unsafe" means that right shift will be performed
// even if the lowest digit is lost.
void Math::unsafeShiftRight(Register &r, const bool updatePointPos) {
    const CalcInt size = r.getSize();
    for (CalcInt i = 1; i < size; i++) {
        r.setDigit(i - S1, r.getDigit(i));
    }
    r.setDigit(size - S1, 0);
    if (updatePointPos && r.getPointPos() > 0)
        r.incPointPos(-1);
}

// "safe" means that left shift will be performed until there is a
// non-zero value in the highest digit or a decimal point after it.
bool Math::safeShiftLeft(Register &r, const bool updatePointPos) {
    const CalcInt size = r.getSize();
    const CalcInt lastIndex = size - S1;
    if (r.getDigit(size - S1) != 0 || r.getPointPos() == lastIndex) return false;
    for (CalcInt i = lastIndex; i >= 1; i--) {
        r.setDigit(i, r.getDigit(i - S1));
    }
    r.setDigit(0, 0);
    if (updatePointPos)
        r.incPointPos(+1);
    return true;
}

CalcInt Math::compare(const Register &r1, const Register &r2) {
    return compare(r1, r2, false);
}

CalcInt Math::compare(const Register &r1, const Register &r2, const bool ignoreSign) {
    const CalcInt size = r1.getSize();
    assert(size == r2.getSize());

    if (!ignoreSign && r1.isNegative() != r2.isNegative())
        return r1.isNegative() ? -S1 : S1;

    CalcInt result = 0;

    const CalcInt r1p = r1.getPointPos();
    const CalcInt r2p = r2.getPointPos();

    // Integer part:
    const CalcInt intSize1 = size - r1p;
    const CalcInt intSize2 = size - r2p;
    const CalcInt intSize = intSize1 > intSize2 ? intSize1 : intSize2;
    for (CalcInt i1 = r1p + intSize - S1, i2 = r2p + intSize - S1; i1 >= r1p; i1--, i2--) {
        const CalcDigit d1 = i1 < size ? r1.getDigit(i1) : S0;
        const CalcDigit d2 = i2 < size ? r2.getDigit(i2) : S0;
        if (d1 == d2) continue;
        result = d1 > d2 ? S1 : -S1;
        break;
    }

    // Fraction part:
    const CalcInt fracSize1 = size - intSize1;
    const CalcInt fracSize2 = size - intSize2;
    const CalcInt fracSize = fracSize1 > fracSize2 ? fracSize1 : fracSize2;
    for (CalcInt f1 = r1p - S1, f2 = r2p - S1, i = 0; i < fracSize; f1--, f2--, i++) {
        const CalcDigit d1 = f1 < S0 ? S0 : r1.getDigit(f1);
        const CalcDigit d2 = f2 < S0 ? S0 : r2.getDigit(f2);
        if (d1 == d2) continue;
        result = d1 > d2 ? S1 : -S1;
        break;
    }

    if (!ignoreSign && r1.isNegative())
        result = -result;
    return result;
}


CalcInt Math::compareDigitsIgnoreSign(const Register &r1, const Register &r2) {
    const CalcInt size = r1.getSize();
    if (size != r2.getSize()) return 0;
    for (CalcInt i = 0; i < size; i++) {
        const CalcInt index = size - i - S1;
        if (r1.getDigit(index) > r2.getDigit(index))
            return 1;
        if (r1.getDigit(index) < r2.getDigit(index))
            return -1;
    }
    return 0;
}

void Math::normalizePointPositions(Register &r1, Register &r2) {
    const CalcInt size = r1.getSize();
    if (size != r2.getSize() || r1.getPointPos() == r2.getPointPos()) return;

    Register &rL = r1.getPointPos() < r2.getPointPos() ? r1 : r2;
    Register &rR = r1.getPointPos() > r2.getPointPos() ? r1 : r2;

    // First shift left the register where pointPos is smaller.
    for (CalcInt i = 0; i < size; i++) {
        if (rL.getDigit(size - S1) != 0) break;
        safeShiftLeft(rL, true);
        if (r1.getPointPos() == r2.getPointPos()) return;
    }

    // Than shift right the other register until pointPos's are equal.
    for (CalcInt i = 0; i < size; i++) {
        unsafeShiftRight(rR, true);
        if (r1.getPointPos() == r2.getPointPos()) return;
    }
}

void Math::truncRightZeros(Register &r) {
    const CalcInt size = r.getSize();
    for (CalcInt i = 0; i < size; i++) {
        if (r.getDigit(0) != 0 || r.getPointPos() == 0) break;
        unsafeShiftRight(r, true);
    }
}

void Math::doubleSizedRegisterToSingle(Register &r2, Register &r) {
    const CalcInt size = r.getSize();
    const CalcInt size2 = r2.getSize();

    CalcInt pointPos = r2.getPointPos();

    CalcInt firstDigitIndex = 0;
    for (CalcInt i = size2 - S1; i >= 0; i--) {
        if (r2.getDigit(i) > 0) {
            firstDigitIndex = i;
            break;
        }
    }
    if (firstDigitIndex < pointPos)
        firstDigitIndex = pointPos;

    CalcInt overflowPos = 0;
    while (firstDigitIndex >= size) {
        unsafeShiftRight(r2, false);
        if (pointPos == 0) overflowPos++;
        else pointPos--;
        firstDigitIndex--;
    }
    const bool hasOverflow = overflowPos > 0;
    r2.setError(hasOverflow, hasOverflow);
    r2.setPointPos(overflowPos > 0 ? size - overflowPos : pointPos);
    if (r2.isZero(true))
        r2.setNegative(false);

    r.set(r2);
}

void Math::appendZerosOnOverflow(Register &r, const CalcOptions options) {
    if (!r.hasOverflow()) return;
    if ((options & Config::OPTION_TRUNC_ZEROS_ON_OVERFLOW) != 0) return;
    while (safeShiftLeft(r, true)) {}
}

void Math::add(Register &r1, Register &r2) {
    const CalcInt size = r1.getSize();
    assert(size == r2.getSize());
    const CalcInt size2 = size + size;

    // This could be done (and it is) in addInternal() method.
    // See TestSpecial.RegisterYChanged test for details.
    normalizePointPositions(r1, r2);

    Register r1ex(size2);
    Register r2ex(size2);
    r1ex.setChangedCallback(r1.getChangedCallback());
    r2ex.setChangedCallback(r2.getChangedCallback());
    r1ex.set(r1);
    r2ex.set(r2);

    addInternal(r1ex, r2ex);

    r1.setChangedCallback(r1ex.getChangedCallback());
    r2.setChangedCallback(r2ex.getChangedCallback());
    doubleSizedRegisterToSingle(r1ex, r1);
    doubleSizedRegisterToSingle(r2ex, r2);
    truncRightZeros(r1);
    truncRightZeros(r2);
}

void Math::addInternal(Register &r1, Register &r2) {
    const CalcInt size = r1.getSize();
    assert(size == r2.getSize());

    normalizePointPositions(r1, r2);

    if (r1.isNegative() == r2.isNegative()) { // (same sign)
        bool extraDigit = false;
        for (CalcInt i = 0; i < size; i++) {
            r1.setDigit(i, static_cast<CalcDigit>(r1.getDigit(i) + r2.getDigit(i)));
            if (extraDigit)
                r1.incDigit(i, 1);

            extraDigit = r1.getDigit(i) > S9;
            if (extraDigit)
                r1.incDigit(i, -S10);
        }

        if (extraDigit) {
            r1.setError(true, true);
            unsafeShiftRight(r1, false);
            r1.setDigit(size - S1, 1);
            r1.setPointPos(size - S1);
        }
    } else { // (different signs)
        const CalcInt comparision = compareDigitsIgnoreSign(r1, r2);
        CalcDigit borrowedDigit = 0;
        CalcDigit srcDigit;
        if (comparision == 1) { // |r1| > |r2|
            for (CalcInt i = 0; i < size; i++) {
                srcDigit = static_cast<CalcDigit>(r1.getDigit(i) - borrowedDigit);
                if (srcDigit < r2.getDigit(i)) {
                    r1.setDigit(i, static_cast<CalcDigit>(srcDigit + S10 - r2.getDigit(i)));
                    borrowedDigit = 1;
                } else {
                    r1.setDigit(i, static_cast<CalcDigit>(srcDigit - r2.getDigit(i)));
                    borrowedDigit = 0;
                }
            }
        } else if (comparision == -1) { // |r1| < |r2|
            for (CalcInt i = 0; i < size; i++) {
                srcDigit = static_cast<CalcDigit>(r2.getDigit(i) - borrowedDigit);
                if (srcDigit < r1.getDigit(i)) {
                    r1.setDigit(i, static_cast<CalcDigit>(srcDigit + S10 - r1.getDigit(i)));
                    borrowedDigit = 1;
                } else {
                    r1.setDigit(i, static_cast<CalcDigit>(srcDigit - r1.getDigit(i)));
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

void Math::mul(Register &r1, const Register &r2) {
    const CalcInt size = r1.getSize();
    assert(size == r2.getSize());

    Register acc(size + size);
    mul(r1, r2, acc);
}

void Math::mul(Register &r1, const Register &r2, Register &acc) {
    const CalcInt size = r1.getSize();
    assert(size == r2.getSize());
    assert(size * 2 == acc.getSize());

    Register r2ex(acc.getSize());
    r2ex.set(r2);
    r2ex.setPointPos(0);
    r2ex.setNegative(false);

    acc.clear();
    const CalcInt lastRegIndex = size - S1;
    for (CalcInt i = lastRegIndex; i >= 0; i--) {
        const CalcDigit digit = r1.getDigit(i);
        for (CalcInt j = 0; j < digit; j++) {
            addInternal(acc, r2ex);
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
    const CalcInt size = r1.getSize();
    assert(size == r2.getSize());

    Register acc(size + size);
    div(r1, r2, acc);
}

void Math::div(Register &r1, Register &r2, Register &acc) {
    const CalcInt size = r1.getSize();
    const CalcInt size2 = size + size;
    assert(size == r2.getSize());
    assert(size2 == acc.getSize());

    if (r2.isZero(true)) {
        r1.clear();
        r1.setError(true, false);
        return;
    }

    const bool negative = r1.isNegative() != r2.isNegative();

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

    if (compareDigitsIgnoreSign(acc, r2ex) >= 0) {
        // Shift r2ex to the very right:
        const CalcInt lastIndex2 = size2 - S1;
        CalcInt shifts = 0;
        while (r2ex.getDigit(lastIndex2) == 0)
            if (safeShiftLeft(r2ex, false)) shifts++;
            else break;
        acc.setPointPos(0);
        r2ex.setPointPos(0);

        for (CalcInt i = 0; i <= shifts; i++) {
            CalcDigit digit = 0;
            if (compareDigitsIgnoreSign(acc, r2ex) >= 0) {
                while (compareDigitsIgnoreSign(acc, r2ex) >= 0) {
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
        for (CalcInt j = 0; j < size2; j++) {
            safeShiftLeft(acc, false);

            CalcDigit digit = 0;
            if (compareDigitsIgnoreSign(acc, r2ex) >= 0) {
                while (compareDigitsIgnoreSign(acc, r2ex) >= 0) {
                    addInternal(acc, r2ex);
                    digit++;
                }
            }

            if (safeShiftLeft(r1ex, true)) // if (canShift)
                r1ex.setDigit(0, digit);
        }
    }

    r1ex.setNegative(negative);

    r1.setChangedCallback(r1ex.getChangedCallback());
    r2.setChangedCallback(r2ex.getChangedCallback());

    doubleSizedRegisterToSingle(r1ex, r1);
    truncRightZeros(r1);
}

void Math::calculatePercent(Register &r1, Register &r2, const Operation &operation, const CalcOptions options) {
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
        case Operation::mu:
            muPercent(r1, r2);
            break;
    }

    appendZerosOnOverflow(r1, options);
}

void Math::addPercent(Register &r1ex, Register &r2ex, Register &accEx) {
    const bool negative = r1ex.isNegative() != r2ex.isNegative();

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
    const CalcInt size = r1.getSize();
    const CalcInt size2 = size + size;
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
    const CalcInt size = r1.getSize();
    const CalcInt size2 = size + size;
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
    const CalcInt size = r1.getSize();
    const CalcInt size2 = size + size;
    assert(size == r2.getSize());

    const bool negative = r1.isNegative() != r2.isNegative();

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
    const CalcInt size = r1.getSize();
    const CalcInt size2 = size + size;
    assert(size == r2.getSize());

    const bool negative = r1.isNegative() != r2.isNegative();

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

// "value mu percent %" => value / (1 - percent/100)
// Example: 200 mu 60 % => 500
// Input: r1: value, r2: percent
// Output: r1: result, r2: percent/100
void Math::muPercent(Register &r1, Register &r2) {
    const CalcInt size = r1.getSize();
    assert(size == r2.getSize());

    Register acc(size);
    acc.setDigit(2, 1); // acc = 100

    div(r2, acc); // r2 = r2 / 100

    acc.clear();
    acc.setDigit(0, 1); // acc = 1
    sub(acc, r2);

    div(r1, acc);
    truncRightZeros(r1);
    truncRightZeros(r2);
}

void Math::changeSign(Register &r) {
    r.switchNegative();
}

void Math::sqrt(Register &r) {
    const CalcInt size = r.getSize();
    const CalcInt size2 = size + size;
    Register h2(size2);
    Register g2(size2);
    sqrt(r, h2, g2);
}

void Math::sqrt(Register &r, Register &h2, Register &g2) {
    const CalcInt size = r.getSize();
    const CalcInt size2 = size + size;
    assert(size2 == h2.getSize());
    assert(size2 == g2.getSize());

    const bool isNegative = r.isNegative();
    if (isNegative)
        r.setNegative(false);

    Register two(size2);
    two.setDigit(0, 2);

    Register h(size);
    Register g(size);

    // h2 = 0
    h2.clear();

    // g2 = 10
    g2.clear();
    g2.setDigit(0, 1);
    safeShiftLeft(g2, false);

    CalcInt counter = 0;
    constexpr CalcInt maxCount = 100;
    while (counter++ < maxCount) {
        // h2 = r / g2
        h2.set(r);
        div(h2, g2);

        // g2 = (g2 + h2) / 2
        add(g2, h2);
        div(g2, two);

        h.setSafe(h2);
        g.setSafe(g2);
        if (compare(h, g, true) == 0) break;
    }

    r.set(g);
    truncRightZeros(r);
    r.setError(isNegative, false);
}
