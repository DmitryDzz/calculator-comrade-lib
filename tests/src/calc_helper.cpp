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
    r.setNegative(value < 0);
    std::string text = std::to_string(r.isNegative() ? -value : value);
    auto totalDigits = (int8_t) text.size();

    if (digitsAfterPoint < totalDigits) {
        int8_t intDigits = totalDigits - digitsAfterPoint;
        r.setError(intDigits > digits);
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
        r.setError(false);
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

Button calculatorcomrade::stringToButton(const std::string& button) {
    if (button == "CA")
        return Button::ca;
    else if (button == "CE")
        return Button::ce;
    else if (button == "0")
        return Button::d0;
    else if (button == "1")
        return Button::d1;
    else if (button == "2")
        return Button::d2;
    else if (button == "3")
        return Button::d3;
    else if (button == "4")
        return Button::d4;
    else if (button == "5")
        return Button::d5;
    else if (button == "6")
        return Button::d6;
    else if (button == "7")
        return Button::d7;
    else if (button == "8")
        return Button::d8;
    else if (button == "9")
        return Button::d9;
    else if (button == ".")
        return Button::point;
    else if (button == "+")
        return Button::plus;
    else if (button == "-")
        return Button::minus;
    else if (button == "*")
        return Button::mul;
    else if (button == "/")
        return Button::div;
    else if (button == "SQRT")
        return Button::sqrt;
    else if (button == "%")
        return Button::percent;
    else if (button == "=")
        return Button::equals;
    else if (button == "M+")
        return Button::memPlus;
    else if (button == "M-")
        return Button::memMinus;
    else if (button == "MR")
        return Button::memR;
    else if (button == "MC")
        return Button::memC;
    return Button::none;
}
