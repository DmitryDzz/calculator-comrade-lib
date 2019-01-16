//
// Created by dmitrydzz on 11.01.19.
//

#include "calc_helper.h"

#define U1 ((uint8_t)1)

using calculatorcomrade::Register;

uint64_t calculatorcomrade::getAbsIntValue(Register &r) {
    uint64_t result = 0;
    uint64_t factor = 1;
    uint8_t digits = r.getDigits();
    for (int i = 0; i < digits; i++, factor *= 10)
        result += factor * r.getDigit((uint8_t)i);
    return result;
}

void calculatorcomrade::setValue(Register &r, int64_t value) {
    setValue(r, value, 0);
}

void calculatorcomrade::setValue(Register &r, int64_t value, uint8_t digitsAfterPoint) {
    uint8_t digits = r.getDigits();
    r.setNegative(value < 0);
    std::string text = std::to_string(r.getNegative() ? -value : value);
    auto totalDigits = (uint8_t) text.size();

    if (digitsAfterPoint < totalDigits) {
        uint8_t intDigits = totalDigits - digitsAfterPoint;
        r.setOverflow(intDigits > digits);
        if (r.getOverflow()) {
            r.setPointPos(digits - (intDigits - digits));
            for (int16_t i = 0; i < digits; i++) {
                char digitChar = text[digits - i - 1];
                std::string digitText(1, digitChar);
                r.setDigit((uint8_t )i, (uint8_t )std::stoi(digitText));
            }
        } else {
            if (totalDigits > digits) {
                r.setPointPos(digits - intDigits);
                for (int16_t i = 0; i < digits; i++) {
                    char digitChar = text[digits - i - 1];
                    std::string digitText(1, digitChar);
                    r.setDigit((uint8_t )i, (uint8_t )std::stoi(digitText));
                }
            } else {
                r.setPointPos(digitsAfterPoint);
                for (int16_t i = 0; i < digits; i++) {
                    char digitChar = i < totalDigits ? text[totalDigits - i - 1] : '0';
                    std::string digitText(1, digitChar);
                    r.setDigit((uint8_t )i, (uint8_t )std::stoi(digitText));
                }
            }
        }
    } else { // means: (digitsAfterPoint >= totalDigits)
        r.setOverflow(false);
        uint8_t newTotalDigits = digitsAfterPoint + (uint8_t) 1;
        int16_t delta = newTotalDigits > digits ? newTotalDigits - digits : (int16_t) 0;
        if (newTotalDigits - totalDigits >= digits) {
            r.setPointPos(0);
        } else {
            r.setPointPos(delta > (uint8_t) 0 ? (uint8_t) (digitsAfterPoint - delta) : digitsAfterPoint);
        }
        for (int16_t i = 0; i < digits; i++) {
            int16_t charIndex = totalDigits - delta - ((uint8_t) 1) - i;
            char digitChar = charIndex >= 0 ? text[charIndex] : '0';
            std::string digitText(1, digitChar);
            r.setDigit((uint8_t )i, (uint8_t )std::stoi(digitText));
        }
    }
}

void calculatorcomrade::evaluateText(Register &r, std::string *output) {
    uint8_t digits = r.getDigits();

    if (digits == 0) {
        *output = "Empty";
        return;
    }

    *output = "";
    if (r.getOverflow())
        *output += "[Err]";
    if (r.getNegative())
        *output += "–";
    for (uint8_t i = 0; i < digits; i++) {
        if (i % 4 == 0 && i != 0)
            *output += " ";
        *output += std::to_string(r.getDigit(digits - i - U1));
    }
}
