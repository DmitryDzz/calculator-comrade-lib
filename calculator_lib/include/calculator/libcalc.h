/**
 * Calculator Comrade Library
 * License: https://github.com/DmitryDzz/calculator-comrade-lib/blob/master/LICENSE
 * Author: Dmitry Dzakhov
 * Email: info@robot-mitya.ru
 */
#ifndef CALCULATORCOMRADE_MAIN_H
#define CALCULATORCOMRADE_MAIN_H

#include "calculator/calculator.h"
#include "calculator/button.h"

using calculatorcomrade::Calculator;
using calculatorcomrade::DisplayEventCallback;
using calculatorcomrade::Button;

using HCALC = uint8_t;
using HRES = int8_t;

using InstancesMap = std::map<HCALC, Calculator*>;

#define HRES_OK ((HRES)0)
#define HRES_ERR_NO_INSTANCE ((HRES)-1)
#define HRES_ERR_TOO_MANY_INSTANCES ((HRES)-2)
#define HRES_ERR_WRONG_DUMP_VERSION ((HRES)-3)
#define HRES_ERR_WRONG_DUMP_SIZE ((HRES)-4)

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
extern "C" HRES ExportDump(HCALC hCalc, uint8_t *dump, uint8_t *dumpSize);

/// Sets calculator's state to recently saved by exportDump method.
/// \param hCalc [input param] instance identifier.
/// \param dump [input param] dump pointer, nullable.
/// \param dumpSize [input param] dump size.
/// \return HRES.
extern "C" HRES ImportDump(HCALC hCalc, const uint8_t *dump, uint8_t dumpSize);

#endif //CALCULATORCOMRADE_MAIN_H
