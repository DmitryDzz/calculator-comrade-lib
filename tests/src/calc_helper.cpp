//
// Created by dmitrydzz on 11.01.19.
//

#include "calc_helper.h"

#define S1 ((int8_t)1)

using calculatorcomrade::Register;
using calculatorcomrade::Button;

int64_t calculatorcomrade::getAbsIntValue(Register &r) {
    int64_t result = 0;
    int64_t factor = 1;
    int8_t digits = r.getSize();
    for (int i = 0; i < digits; i++, factor *= 10)
        result += factor * r.getDigit((int8_t)i);
    return result;
}

int64_t calculatorcomrade::getIntValue(Register &r) {
    return r.isNegative() ? -getAbsIntValue(r) : getAbsIntValue(r);
}

void calculatorcomrade::setValue(Register &r, int64_t value) {
    setValue(r, value, 0);
}

void calculatorcomrade::setValue(Register &r, int64_t value, int8_t digitsAfterPoint) {
    int8_t digits = r.getSize();
    bool isNegative = value < 0;
    std::string text = std::to_string(isNegative ? -value : value);
    auto totalDigits = (int8_t) text.size();

    if (digitsAfterPoint < totalDigits) {
        int8_t intDigits = totalDigits - digitsAfterPoint;
        r.setError(intDigits > digits, intDigits > digits);
        if (r.hasError()) {
            r.setPointPos(digits - (intDigits - digits));
            for (int16_t i = 0; i < digits; i++) {
                char digitChar = text[digits - i - 1];
                std::string digitText(1, digitChar);
                r.setDigit((int8_t)i, (int8_t)std::stoi(digitText));
            }
        } else {
            if (totalDigits > digits) {
                r.setPointPos(digits - intDigits);
                for (int16_t i = 0; i < digits; i++) {
                    char digitChar = text[digits - i - 1];
                    std::string digitText(1, digitChar);
                    r.setDigit((int8_t)i, (int8_t)std::stoi(digitText));
                }
            } else {
                r.setPointPos(digitsAfterPoint);
                for (int16_t i = 0; i < digits; i++) {
                    char digitChar = i < totalDigits ? text[totalDigits - i - 1] : '0';
                    std::string digitText(1, digitChar);
                    r.setDigit((int8_t)i, (int8_t)std::stoi(digitText));
                }
            }
        }
    } else { // means: (digitsAfterPoint >= totalDigits)
        r.setError(false, false);
        int8_t newTotalDigits = digitsAfterPoint + S1;
        int16_t delta = newTotalDigits > digits ? newTotalDigits - digits : (int16_t) 0;
        if (newTotalDigits - totalDigits >= digits) {
            r.setPointPos(0);
        } else {
            r.setPointPos(delta > (int8_t) 0 ? (int8_t) (digitsAfterPoint - delta) : digitsAfterPoint);
        }
        for (int16_t i = 0; i < digits; i++) {
            int16_t charIndex = totalDigits - delta - S1 - i;
            char digitChar = charIndex >= 0 ? text[charIndex] : '0';
            std::string digitText(1, digitChar);
            r.setDigit((int8_t)i, (int8_t)std::stoi(digitText));
        }
    }
    r.setNegative(isNegative);
}

void calculatorcomrade::evaluateText(Register &r, std::string *output) {
    int8_t size = r.getSize();

    if (size == 0) {
        *output = "Empty";
        return;
    }

    auto digitsInGroup = static_cast<int8_t>(size == 6 ? 3 : 4);

    *output = "";
    if (r.hasError())
        *output += "[Err]";
    if (r.isNegative())
        *output += "–";
    for (int8_t i = 0; i < size; i++) {
        if (i % digitsInGroup == 0 && i != 0)
            *output += " ";
        *output += std::to_string(r.getDigit(size - i - S1));
        if (i == size - r.getPointPos() - S1)
            *output += ".";
    }
}

