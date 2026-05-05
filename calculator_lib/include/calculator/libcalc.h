/**
 * Calculator Comrade Library
 *
 * Calculator Comrade C API.
 * WARNING: The C API is not thread-safe!
 *
 * License: https://github.com/DmitryDzz/calculator-comrade-lib/blob/master/LICENSE
 * Author: Dmitry Dzakhov
 * Email: info@robot-mitya.ru
 */
#ifndef CALCULATORCOMRADE_LIBCALC_H
#define CALCULATORCOMRADE_LIBCALC_H

// NOLINTBEGIN(modernize-deprecated-headers, modernize-use-using, performance-enum-size, modernize-redundant-void-arg)

#include <stdint.h>
// ReSharper disable once CppUnusedIncludeDirective
#include <stdbool.h>

#include "calculator/button_codes.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t HCALC;

typedef void (*DisplayEventCallback)(void);

#if defined(_WIN32) && !defined(CALCULATOR_LIB_STATIC)
    #if defined(CALCULATOR_LIB_BUILD)
        #define CALCULATOR_API __declspec(dllexport)
    #else
        #define CALCULATOR_API __declspec(dllimport)
    #endif
#else
    #define CALCULATOR_API
#endif

typedef int8_t CalculatorResult;
enum {
    CALC_OK = 0,
    CALC_ERR_NO_INSTANCE = -1,
    CALC_ERR_TOO_MANY_INSTANCES = -2,
    CALC_ERR_WRONG_DUMP_VERSION = -3,
    CALC_ERR_WRONG_DUMP_SIZE = -4,
    CALC_ERR_INVALID_ARGUMENT = -5,
    CALC_ERR_UNSUPPORTED_SIZE = -6,
    CALC_ERR_INTERNAL = -7
};

CALCULATOR_API CalculatorResult CreateCalculator(uint8_t digits, uint8_t options, HCALC *hcalc);

CALCULATOR_API CalculatorResult DisposeCalculator(HCALC hCalc);

CALCULATOR_API void DisposeAll(void);

CALCULATOR_API CalculatorResult SetDisplayEventCallback(HCALC hCalc, DisplayEventCallback callback);

CALCULATOR_API CalculatorResult CalculatorInput(HCALC hCalc, CalculatorButtonCode button);

CALCULATOR_API CalculatorResult GetSize(HCALC hCalc, uint8_t *size);

CALCULATOR_API CalculatorResult GetNegative(HCALC hCalc, bool *negative);

CALCULATOR_API CalculatorResult GetError(HCALC hCalc, bool *hasError);

CALCULATOR_API CalculatorResult GetMemory(HCALC hCalc, bool *memoryHasValue);

CALCULATOR_API CalculatorResult GetPointPos(HCALC hCalc, int8_t *pointPos);

CALCULATOR_API CalculatorResult GetDigit(HCALC hCalc, int8_t index, int8_t *digit);

CALCULATOR_API CalculatorResult GetDisplayDigit(HCALC hCalc, int8_t index, int8_t *digit);

/// Exports current state to dump.
/// \param hCalc [input param] instance identifier.
/// \param dump [input/output param] dump pointer, nullable.
/// \param dumpSize [output param] dump size.
/// \return CalculatorResult.
CALCULATOR_API CalculatorResult ExportDump(HCALC hCalc, uint8_t *dump, uint8_t *dumpSize);

/// Sets calculator's state to recently saved by exportDump method.
/// \param hCalc [input param] instance identifier.
/// \param dump [input param] dump pointer.
/// \param dumpSize [input param] dump size.
/// \return CalculatorResult.
CALCULATOR_API CalculatorResult ImportDump(HCALC hCalc, const uint8_t *dump, uint8_t dumpSize);

#ifdef __cplusplus
}
#endif

// NOLINTEND(modernize-deprecated-headers, modernize-use-using, performance-enum-size, modernize-redundant-void-arg)

#endif //CALCULATORCOMRADE_LIBCALC_H
