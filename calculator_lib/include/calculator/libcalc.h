/**
 * Calculator Comrade Library
 *
 * Calculator Comrade C API.
 * WARNING: The C API is not thread-safe!
 *
 * Copyright (c) 2019-2026 Dmitry Dzakhov (dmitrydzz)
 * SPDX-License-Identifier: MIT
 */
#ifndef CALCULATORCOMRADE_LIBCALC_H
#define CALCULATORCOMRADE_LIBCALC_H

// NOLINTBEGIN(modernize-deprecated-headers, modernize-use-using, performance-enum-size, modernize-redundant-void-arg)

#include <stdint.h>
// ReSharper disable once CppUnusedIncludeDirective
#include <stdbool.h>

#include "calculator/button_codes.h"
#include "calculator/option_codes.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "calculator/libcalc_version.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Calculator instance handle.
 *
 * A handle is returned by CreateCalculator and must be passed to all functions
 * that operate on a specific calculator instance.
 */
typedef uint8_t HCALC;

/**
 * Display update callback.
 *
 * The calculator calls this callback when the display should be redrawn.
 * Inside the callback, use GetSize, GetNegative, GetError, GetMemory,
 * GetPointPos, GetDigit, and GetDisplayDigit to read the current display state
 * and redraw the display in the host application.
 */
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

/**
 * Result code returned by C API functions.
 *
 * CALC_OK indicates success. Negative values indicate specific errors.
 */
typedef int8_t CalculatorResult;

/**
 * Calculator C API result codes.
 */
enum {
    /** Operation completed successfully. */
    CALC_OK = 0,
    /** The specified calculator handle does not refer to an existing instance. */
    CALC_ERR_NO_INSTANCE = -1,
    /** No more calculator instances can be created. */
    CALC_ERR_TOO_MANY_INSTANCES = -2,
    /** The supplied dump has an unsupported or invalid dump format version. */
    CALC_ERR_WRONG_DUMP_VERSION = -3,
    /** The supplied dump size is invalid. */
    CALC_ERR_WRONG_DUMP_SIZE = -4,
    /** An output pointer argument is null or otherwise invalid. */
    CALC_ERR_INVALID_OUT_ARGUMENT = -5,
    /** An index argument is outside the valid display digit range. */
    CALC_ERR_INVALID_INDEX_ARGUMENT = -6,
    /** The requested calculator display size is not supported. */
    CALC_ERR_UNSUPPORTED_SIZE = -7,
    /** An internal error occurred. */
    CALC_ERR_INTERNAL = -8
};

/**
 * Gets the Calculator Comrade library version string.
 *
 * The returned string is a static null-terminated string and must not be freed
 * or modified by the caller.
 *
 * \return Library version string in MAJOR.MINOR.PATCH format.
 */
CALCULATOR_API const char *GetCalculatorVersion(void);

/**
 * Creates a calculator instance.
 *
 * The created calculator has the specified number of display digits and uses
 * the specified option flags.
 *
 * The returned handle must be released with DisposeCalculator() when it is no longer needed.
 *
 * \param digits Number of display digits. Valid values are from 3 to 16.
 * \param options Calculator option flags. Use CALC_OPTIONS_DEFAULT for the
 *        default behavior, or combine CALC_OPTION_* values with bitwise OR.
 * \param hcalc Output pointer that receives the created calculator handle.
 * \return CALC_OK on success, or an error code on failure.
 */
CALCULATOR_API CalculatorResult CreateCalculator(uint8_t digits, CalculatorOptions options, HCALC *hcalc);

/**
 * Disposes a calculator instance.
 *
 * After this call succeeds, the handle must not be used again.
 *
 * \param hCalc Calculator instance handle.
 * \return CALC_OK on success, or an error code on failure.
 */
CALCULATOR_API CalculatorResult DisposeCalculator(HCALC hCalc);

/**
 * Disposes all calculator instances created through this C API.
 */
CALCULATOR_API void DisposeAll(void);

/**
 * Sets the display update callback for a calculator instance.
 *
 * The callback is called when the calculator display should be redrawn.
 * Pass null to clear the current callback.
 *
 * \param hCalc Calculator instance handle.
 * \param callback Display update callback, or null.
 * \return CALC_OK on success, or an error code on failure.
 */
CALCULATOR_API CalculatorResult SetDisplayEventCallback(HCALC hCalc, DisplayEventCallback callback);

/**
 * Sends a button press to the calculator.
 *
 * Use one of the CalculatorButtonCode values declared in button_codes.h.
 *
 * \param hCalc Calculator instance handle.
 * \param button Pressed calculator button code.
 * \return CALC_OK on success, or an error code on failure.
 */
CALCULATOR_API CalculatorResult CalculatorInput(HCALC hCalc, CalculatorButtonCode button);

/**
 * Gets the number of digits on the calculator display.
 *
 * The size is selected when the calculator instance is created with
 * CreateCalculator.
 *
 * \param hCalc Calculator instance handle.
 * \param size Output pointer that receives the display digit count.
 * \return CALC_OK on success, or an error code on failure.
 */
CALCULATOR_API CalculatorResult GetSize(HCALC hCalc, uint8_t *size);

/**
 * Gets the current negative-sign display flag.
 *
 * This flag indicates whether the minus sign should be shown on the calculator
 * display.
 *
 * \param hCalc Calculator instance handle.
 * \param negative Output pointer that receives the negative-sign flag.
 * \return CALC_OK on success, or an error code on failure.
 */
CALCULATOR_API CalculatorResult GetNegative(HCALC hCalc, bool *negative);

/**
 * Gets the current error display flag.
 *
 * This flag indicates whether the error sign, usually shown as E, should be
 * shown on the calculator display.
 *
 * \param hCalc Calculator instance handle.
 * \param hasError Output pointer that receives the error flag.
 * \return CALC_OK on success, or an error code on failure.
 */
CALCULATOR_API CalculatorResult GetError(HCALC hCalc, bool *hasError);

/**
 * Gets the current memory display flag.
 *
 * This flag indicates whether the calculator memory register currently contains
 * a value and the memory indicator should be shown on the display.
 *
 * \param hCalc Calculator instance handle.
 * \param memoryHasValue Output pointer that receives the memory flag.
 * \return CALC_OK on success, or an error code on failure.
 */
CALCULATOR_API CalculatorResult GetMemory(HCALC hCalc, bool *memoryHasValue);

/**
 * Gets the current decimal point position.
 *
 * The returned value is the index of the decimal point used for display
 * rendering. The index is counted from right to left, from the least
 * significant decimal digit to the most significant decimal digit.
 *
 * \param hCalc Calculator instance handle.
 * \param pointPos Output pointer that receives the decimal point position.
 * \return CALC_OK on success, or an error code on failure.
 */
CALCULATOR_API CalculatorResult GetPointPos(HCALC hCalc, int8_t *pointPos);

/**
 * Gets the value of a decimal digit by index.
 *
 * Index 0 corresponds to the least significant display digit. This function
 * returns 0 for empty leading display positions.
 *
 * \param hCalc Calculator instance handle.
 * \param index Display digit index. Index 0 is the least significant digit.
 * \param digit Output pointer that receives the decimal digit value.
 * \return CALC_OK on success, or an error code on failure.
 */
CALCULATOR_API CalculatorResult GetDigit(HCALC hCalc, int8_t index, int8_t *digit);

/**
 * Gets the display digit value by index.
 *
 * Index 0 corresponds to the least significant display digit. This function is
 * intended for display rendering: it returns -1 for empty leading display
 * positions and a decimal digit value for visible positions.
 *
 * \param hCalc Calculator instance handle.
 * \param index Display digit index. Index 0 is the least significant digit.
 * \param digit Output pointer that receives the display digit value, or -1 for an empty position.
 * \return CALC_OK on success, or an error code on failure.
 */
CALCULATOR_API CalculatorResult GetDisplayDigit(HCALC hCalc, int8_t index, int8_t *digit);

/**
 * Exports the current calculator state to a dump.
 *
 * This can be used to save the calculator state when an application is unloaded
 * from memory or needs to persist the current calculator state for another
 * reason.
 *
 * The dump pointer may be null when only the required dump size is needed.
 *
 * \param hCalc Calculator instance handle.
 * \param dump Output buffer that receives the dump data, or null.
 * \param dumpSize Output pointer that receives the dump size.
 * \return CALC_OK on success, or an error code on failure.
 */
CALCULATOR_API CalculatorResult ExportDump(HCALC hCalc, uint8_t *dump, uint8_t *dumpSize);

/**
 * Imports a previously exported calculator state dump.
 *
 * This can be used to restore the calculator state after it was saved with
 * ExportDump.
 *
 * \param hCalc Calculator instance handle.
 * \param dump Input buffer containing the dump data.
 * \param dumpSize Dump data size.
 * \return CALC_OK on success, or an error code on failure.
 */
CALCULATOR_API CalculatorResult ImportDump(HCALC hCalc, const uint8_t *dump, uint8_t dumpSize);

#ifdef __cplusplus
}
#endif

// NOLINTEND(modernize-deprecated-headers, modernize-use-using, performance-enum-size, modernize-redundant-void-arg)

#endif //CALCULATORCOMRADE_LIBCALC_H
