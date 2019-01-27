//
// Created by dmitrydzz on 27.01.2019.
//

#include <memory.h>
#include "calculator/calculator.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

using namespace calculatorcomrade;

#define CALCULATOR(pCalculator) (*((Calculator *)pCalculator))
#define DISPLAY_REGISTER(pCalculator) (CALCULATOR(pCalculator).getState().x)

extern "C" void *CreateCalculator(const int8_t digits) {
    return new Calculator(digits);
}

extern "C" void DisposeCalculator(const void *pCalculator) {
    delete ((Calculator *)pCalculator);
}

extern "C" void SetDisplayEventCallback(const void *pCalculator, const DisplayEventCallback callback) {
    CALCULATOR(pCalculator).setDisplayEventCallback(callback);
}

extern "C" void CalculatorInput(const void *pCalculator, const Button button) {
    CALCULATOR(pCalculator).input(button);
}

extern "C" int8_t GetSize(const void *pCalculator) {
    return CALCULATOR(pCalculator).getSize();
}

extern "C" bool IsNegative(const void *pCalculator) {
    return DISPLAY_REGISTER(pCalculator).getNegative();
}

extern "C" bool IsOverflow(const void *pCalculator) {
    return DISPLAY_REGISTER(pCalculator).getOverflow();
}

extern "C" int8_t PointPos(const void *pCalculator) {
    return DISPLAY_REGISTER(pCalculator).getPointPos();
}

extern "C" int8_t GetDigit(const void *pCalculator, const int8_t index) {
    return DISPLAY_REGISTER(pCalculator).getDigit(index);
}

#pragma clang diagnostic pop
