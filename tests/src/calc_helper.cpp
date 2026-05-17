/**
 * Calculator Comrade Library
 * Copyright (c) 2019-2026 Dmitry Dzakhov (dmitrydzz)
 * SPDX-License-Identifier: MIT
 */
#include "calc_helper.h"

#include "calculator/button.h"

using calculatorcomrade::Register;
using calculatorcomrade::Button;
using calculatorcomrade::CalcInt;

CalcInt calculatorcomrade::getAbsIntValue(Register &r) {
    CalcInt result = 0;
    CalcInt factor = 1;
    const CalcInt digits = r.getSize();
    for (CalcInt i = 0; i < digits; i++, factor *= 10)
        result += factor * r.getDigit(i);
    return result;
}

CalcInt calculatorcomrade::getIntValue(Register &r) {
    return r.isNegative() ? -getAbsIntValue(r) : getAbsIntValue(r);
}

void calculatorcomrade::setValue(Register &r, const CalcInt value) {
    setValue(r, value, 0);
}

void calculatorcomrade::setValue(Register &r, const CalcInt value, const CalcInt digitsAfterPoint) {
    const CalcInt digits = r.getSize();
    const bool isNegative = value < 0;
    const std::string text = std::to_string(isNegative ? -value : value);

    // ReSharper disable once CppTooWideScopeInitStatement
    const auto totalDigits = static_cast<CalcInt>(text.size());
    if (digitsAfterPoint < totalDigits) {
        const CalcInt intDigits = totalDigits - digitsAfterPoint;
        r.setError(intDigits > digits, intDigits > digits);
        if (r.hasError()) {
            r.setPointPos(digits - (intDigits - digits));
            for (CalcInt i = 0; i < digits; i++) {
                const char digitChar = text[digits - i - 1];
                std::string digitText(1, digitChar);
                r.setDigit(i, static_cast<CalcDigit>(std::stoi(digitText)));
            }
        } else {
            if (totalDigits > digits) {
                r.setPointPos(digits - intDigits);
                for (CalcInt i = 0; i < digits; i++) {
                    const char digitChar = text[digits - i - 1];
                    std::string digitText(1, digitChar);
                    r.setDigit(i, static_cast<CalcDigit>(std::stoi(digitText)));
                }
            } else {
                r.setPointPos(digitsAfterPoint);
                for (CalcInt i = 0; i < digits; i++) {
                    const char digitChar = i < totalDigits ? text[totalDigits - i - 1] : '0';
                    std::string digitText(1, digitChar);
                    r.setDigit(i, static_cast<CalcDigit>(std::stoi(digitText)));
                }
            }
        }
    } else { // means: (digitsAfterPoint >= totalDigits)
        r.setError(false, false);
        const CalcInt newTotalDigits = digitsAfterPoint + S1;
        const CalcInt delta = newTotalDigits > digits ? newTotalDigits - digits : S0;
        if (newTotalDigits - totalDigits >= digits) {
            r.setPointPos(0);
        } else {
            r.setPointPos(delta > S0 ? digitsAfterPoint - delta : digitsAfterPoint);
        }
        for (CalcInt i = 0; i < digits; i++) {
            const CalcInt charIndex = totalDigits - delta - S1 - i;
            const char digitChar = charIndex >= 0 ? text[charIndex] : '0';
            std::string digitText(1, digitChar);
            r.setDigit(i, static_cast<CalcDigit>(std::stoi(digitText)));
        }
    }
    r.setNegative(isNegative);
}

void calculatorcomrade::evaluateText(Register &r, std::string *output) {
    const CalcInt size = r.getSize();

    if (size == 0) {
        *output = "Empty";
        return;
    }

    const auto digitsInGroup = size == 6 ? 3 : 4;

    *output = "";
    if (r.hasError())
        *output += "[Err]";
    if (r.isNegative())
        *output += "–";
    for (CalcInt i = 0; i < size; i++) {
        if (i % digitsInGroup == 0 && i != 0)
            *output += " ";
        *output += std::to_string(r.getDigit(size - i - S1));
        if (i == size - r.getPointPos() - S1)
            *output += ".";
    }
}

