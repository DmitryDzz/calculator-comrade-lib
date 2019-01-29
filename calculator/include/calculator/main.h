//
// Created by dmitrydzz on 29.01.2019.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

#ifndef CALCULATORCOMRADE_MAIN_H
#define CALCULATORCOMRADE_MAIN_H

#include "calculator/calculator.h"
#include "calculator/button.h"

using calculatorcomrade::Calculator;
using calculatorcomrade::DisplayEventCallback;
using calculatorcomrade::Button;

typedef uint8_t HCALC;
typedef int8_t HRES;

typedef std::map<HCALC, Calculator*> InstancesMap;

#define HRES_OK ((HCALC)0)
#define HRES_ERR_NO_INSTANCE ((HCALC)-1)
#define HRES_ERR_TOO_MANY_CALCULATORS ((HCALC)-2)

extern "C" HCALC CreateCalculator(int8_t digits);

extern "C" HRES DisposeCalculator(HCALC hCalc);

extern "C" void DisposeAll();

extern "C" HRES SetDisplayEventCallback(HCALC hCalc, DisplayEventCallback callback);

extern "C" HRES CalculatorInput(HCALC hCalc, Button button);

extern "C" HRES GetSize(HCALC hCalc, int8_t *size);

extern "C" HRES IsNegative(HCALC hCalc, bool *negative);

extern "C" HRES IsOverflow(HCALC hCalc, bool *overflow);

extern "C" HRES PointPos(HCALC hCalc, int8_t *pointPos);

extern "C" HRES GetDigit(HCALC hCalc, int8_t index, int8_t *digit);

#endif //CALCULATORCOMRADE_MAIN_H

#pragma clang diagnostic pop