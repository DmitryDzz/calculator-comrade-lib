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

#define HRES_OK ((HRES)0)
#define HRES_ERR_NO_INSTANCE ((HRES)-1)
#define HRES_ERR_TOO_MANY_INSTANCES ((HRES)-2)

extern "C" HRES CreateCalculator(int8_t digits, uint8_t options, HCALC *hcalc);

extern "C" HRES DisposeCalculator(HCALC hCalc);

extern "C" void DisposeAll();

extern "C" HRES SetDisplayEventCallback(HCALC hCalc, DisplayEventCallback callback);

extern "C" HRES CalculatorInput(HCALC hCalc, Button button);

extern "C" HRES GetSize(HCALC hCalc, int8_t *size);

extern "C" HRES GetNegative(HCALC hCalc, bool *negative);

extern "C" HRES GetError(HCALC hCalc, bool *hasError);

extern "C" HRES GetPointPos(HCALC hCalc, int8_t *pointPos);

extern "C" HRES GetDigit(HCALC hCalc, int8_t index, int8_t *digit);

extern "C" HRES GetDisplayDigit(HCALC hCalc, int8_t index, int8_t *digit);

/// Exports current state to dump.
/// \param hCalc [input param] instance identifier.
/// \param dump [input/output param] dump pointer, nullable.
/// \param dumpSize [output param] dump size.
/// \return HRES.
extern "C" HRES ExportDump(HCALC hCalc, int8_t *dump, int8_t *dumpSize);

/// Sets calculator's state to recently saved by exportDump method.
/// \param hCalc [input param] instance identifier.
/// \param dump [input param] dump pointer, nullable.
/// \param dumpSize [input param] dump size.
/// \param importedSize [output param] the value should be equal to dumpSize. Otherwise it is an error code: 1 - wrong dump version, 0 or 2 - wrong dump size.
/// \return HRES.
extern "C" HRES ImportDump(HCALC hCalc, int8_t *dump, int8_t dumpSize, int8_t *importedSize);

#endif //CALCULATORCOMRADE_MAIN_H

#pragma clang diagnostic pop