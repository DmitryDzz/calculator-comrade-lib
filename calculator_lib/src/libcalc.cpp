/**
 * Calculator Comrade Library
 * License: https://github.com/DmitryDzz/calculator-comrade-lib/blob/master/LICENSE
 * Author: Dmitry Dzakhov
 * Email: info@robot-mitya.ru
 */
#include <limits>
#include <map>

#include "calculator/calculator.h"
#include "calculator/libcalc.h"

using namespace calculatorcomrade;

using InstancesMap = std::map<HCALC, Calculator*>;
InstancesMap g_instances;

HCALC g_calc_hnd = 0;

// #define CALCULATOR(pCalculator) (*((Calculator *)pCalculator))
// #define DISPLAY_REGISTER(pCalculator) (CALCULATOR(pCalculator).getX())

Calculator* findInstance(const HCALC hCalc) {
    const auto it = g_instances.find(hCalc);
    if (it == g_instances.end())
        return nullptr;
    return it->second;
}

CALCULATOR_API CalculatorResult CreateCalculator(const uint8_t digits, const uint8_t options, HCALC *hcalc) {
    if (hcalc == nullptr) {
        return CALC_ERR_INVALID_ARGUMENT;
    }
    if (digits < Config::MIN_SIZE || digits > Config::MAX_SIZE) {
        return CALC_ERR_UNSUPPORTED_SIZE;
    }
    if (g_calc_hnd == std::numeric_limits<HCALC>::max())
        return CALC_ERR_TOO_MANY_INSTANCES;
    const HCALC newCalcHnd = g_calc_hnd + 1;
    *hcalc = newCalcHnd;
    try {
        g_instances[newCalcHnd] = new Calculator(digits, options);
        g_calc_hnd = newCalcHnd;
    } catch (...) {
        if (hcalc != nullptr) *hcalc = 0;
        return CALC_ERR_INTERNAL;
    }
    return CALC_OK;
}

CALCULATOR_API CalculatorResult DisposeCalculator(const HCALC hCalc) {
    const auto it = g_instances.find(hCalc);
    if (it == g_instances.end())
        return CALC_ERR_NO_INSTANCE;
    delete it->second;
    g_instances.erase(it);
    return CALC_OK;
}

CALCULATOR_API void DisposeAll() {
    // ReSharper disable once CppUseStructuredBinding
    for (const auto &g_instance : g_instances)
        delete g_instance.second;

    g_instances.clear();
    g_calc_hnd = 0;
}

CALCULATOR_API CalculatorResult SetDisplayEventCallback(const HCALC hCalc, const DisplayEventCallback callback) {
    Calculator* calculator = findInstance(hCalc);
    if (calculator == nullptr)
        return CALC_ERR_NO_INSTANCE;
    calculator->setDisplayEventCallback(callback);
    return CALC_OK;
}

CALCULATOR_API CalculatorResult CalculatorInput(const HCALC hCalc, const CalculatorButtonCode button) {
    Calculator* calculator = findInstance(hCalc);
    if (calculator == nullptr)
        return CALC_ERR_NO_INSTANCE;
    calculator->input(static_cast<Button>(button));
    return CALC_OK;
}

CALCULATOR_API CalculatorResult GetSize(const HCALC hCalc, uint8_t *size) {
    if (size == nullptr)
        return CALC_ERR_INVALID_ARGUMENT;
    const Calculator* calculator = findInstance(hCalc);
    if (calculator == nullptr)
        return CALC_ERR_NO_INSTANCE;
    *size = calculator->getSize();
    return CALC_OK;
}

CALCULATOR_API CalculatorResult GetNegative(const HCALC hCalc, bool *negative) {
    if (negative == nullptr)
        return CALC_ERR_INVALID_ARGUMENT;
    Calculator* calculator = findInstance(hCalc);
    if (calculator == nullptr)
        return CALC_ERR_NO_INSTANCE;
    *negative = calculator->getX().isNegative();
    return CALC_OK;
}

CALCULATOR_API CalculatorResult GetError(const HCALC hCalc, bool *hasError) {
    if (hasError == nullptr)
        return CALC_ERR_INVALID_ARGUMENT;
    Calculator* calculator = findInstance(hCalc);
    if (calculator == nullptr)
        return CALC_ERR_NO_INSTANCE;
    *hasError = calculator->getX().hasError();
    return CALC_OK;
}

CALCULATOR_API CalculatorResult GetMemory(const HCALC hCalc, bool *memoryHasValue) {
    if (memoryHasValue == nullptr)
        return CALC_ERR_INVALID_ARGUMENT;
    const Calculator* calculator = findInstance(hCalc);
    if (calculator == nullptr)
        return CALC_ERR_NO_INSTANCE;
    *memoryHasValue = calculator->memHasValue();
    return CALC_OK;
}

CALCULATOR_API CalculatorResult GetPointPos(const HCALC hCalc, int8_t *pointPos) {
    if (pointPos == nullptr)
        return CALC_ERR_INVALID_ARGUMENT;
    Calculator* calculator = findInstance(hCalc);
    if (calculator == nullptr)
        return CALC_ERR_NO_INSTANCE;
    *pointPos = static_cast<int8_t>(calculator->getX().getPointPos());
    return CALC_OK;
}

CALCULATOR_API CalculatorResult GetDigit(const HCALC hCalc, const int8_t index, int8_t *digit) {
    if (digit == nullptr)
        return CALC_ERR_INVALID_ARGUMENT;
    Calculator* calculator = findInstance(hCalc);
    if (calculator == nullptr)
        return CALC_ERR_NO_INSTANCE;
    *digit = calculator->getX().getDigit(index);
    return CALC_OK;
}

CALCULATOR_API CalculatorResult GetDisplayDigit(const HCALC hCalc, const int8_t index, int8_t *digit) {
    if (digit == nullptr)
        return CALC_ERR_INVALID_ARGUMENT;
    Calculator* calculator = findInstance(hCalc);
    if (calculator == nullptr)
        return CALC_ERR_NO_INSTANCE;
    *digit = calculator->getX().getDisplayDigit(index);
    return CALC_OK;
}

CALCULATOR_API CalculatorResult ExportDump(const HCALC hCalc, uint8_t *dump, uint8_t *dumpSize) {
    if (dumpSize == nullptr)
        return CALC_ERR_INVALID_ARGUMENT;
    Calculator* calculator = findInstance(hCalc);
    if (calculator == nullptr)
        return CALC_ERR_NO_INSTANCE;
    *dumpSize = calculator->exportDump(dump);
    return CALC_OK;
}

CALCULATOR_API CalculatorResult ImportDump(const HCALC hCalc, const uint8_t *dump, const uint8_t dumpSize) {
    if (dump == nullptr)
        return CALC_ERR_INVALID_ARGUMENT;
    Calculator* calculator = findInstance(hCalc);
    if (calculator == nullptr)
        return CALC_ERR_NO_INSTANCE;
    const uint8_t importedSize = calculator->importDump(dump, dumpSize);
    if (importedSize == dumpSize)
        return CALC_OK;
    if (importedSize == 1)
        return CALC_ERR_WRONG_DUMP_VERSION;
    return CALC_ERR_WRONG_DUMP_SIZE;
}
