/**
 * Calculator Comrade Library
 * License: https://github.com/DmitryDzz/calculator-comrade-lib/blob/master/LICENSE
 * Author: Dmitry Dzakhov
 * Email: info@robot-mitya.ru
 */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

#include <limits>
#include <map>

#include "calculator/libcalc.h"

using namespace calculatorcomrade;

InstancesMap g_instances;
HCALC g_calc_hnd = 0;

#define CALCULATOR(pCalculator) (*((Calculator *)pCalculator))
#define DISPLAY_REGISTER(pCalculator) (CALCULATOR(pCalculator).getX())

Calculator* findInstance(HCALC hCalc) {
    auto it = g_instances.find(hCalc);
    if (it == g_instances.end())
        return nullptr;
    return it->second;
}

extern "C" HRES CreateCalculator(const int8_t digits, const uint8_t options, HCALC *hcalc) {
    if (g_calc_hnd == std::numeric_limits<HCALC>::max())
        return HRES_ERR_TOO_MANY_INSTANCES;
    *hcalc = ++g_calc_hnd;
    g_instances[g_calc_hnd] = new Calculator(digits, options);
    return HRES_OK;
}

extern "C" HRES DisposeCalculator(const HCALC hCalc) {
    auto it = g_instances.find(hCalc);
    if (it == g_instances.end())
        return HRES_ERR_NO_INSTANCE;
    delete it->second;
    it->second = nullptr;
    return HRES_OK;
}

extern "C" void DisposeAll() {
    for (auto &g_instance : g_instances)
        delete g_instance.second;

    g_instances.clear();
    g_calc_hnd = 0;
}

extern "C" HRES SetDisplayEventCallback(const HCALC hCalc, const DisplayEventCallback callback) {
    Calculator* calculator = findInstance(hCalc);
    if (calculator == nullptr)
        return HRES_ERR_NO_INSTANCE;
    CALCULATOR(calculator).setDisplayEventCallback(callback);
    return HRES_OK;
}

extern "C" HRES CalculatorInput(const HCALC hCalc, const Button button) {
    Calculator* calculator = findInstance(hCalc);
    if (calculator == nullptr)
        return HRES_ERR_NO_INSTANCE;
    CALCULATOR(calculator).input(button);
    return HRES_OK;
}

extern "C" HRES GetSize(const HCALC hCalc, int8_t *size) {
    Calculator* calculator = findInstance(hCalc);
    if (calculator == nullptr)
        return HRES_ERR_NO_INSTANCE;
    *size = CALCULATOR(calculator).getSize();
    return HRES_OK;
}

extern "C" HRES GetNegative(const HCALC hCalc, bool *negative) {
    Calculator* calculator = findInstance(hCalc);
    if (calculator == nullptr)
        return HRES_ERR_NO_INSTANCE;
    *negative = DISPLAY_REGISTER(calculator).isNegative();
    return HRES_OK;
}

extern "C" HRES GetError(const HCALC hCalc, bool *hasError) {
    Calculator* calculator = findInstance(hCalc);
    if (calculator == nullptr)
        return HRES_ERR_NO_INSTANCE;
    *hasError = DISPLAY_REGISTER(calculator).hasError();
    return HRES_OK;
}

extern "C" HRES GetMemory(const HCALC hCalc, bool *memoryHasValue) {
    Calculator* calculator = findInstance(hCalc);
    if (calculator == nullptr)
        return HRES_ERR_NO_INSTANCE;
    *memoryHasValue = calculator->memHasValue();
    return HRES_OK;
}

extern "C" HRES GetPointPos(const HCALC hCalc, int8_t *pointPos) {
    Calculator* calculator = findInstance(hCalc);
    if (calculator == nullptr)
        return HRES_ERR_NO_INSTANCE;
    *pointPos = DISPLAY_REGISTER(calculator).getPointPos();
    return HRES_OK;
}

extern "C" HRES GetDigit(const HCALC hCalc, const int8_t index, int8_t *digit) {
    Calculator* calculator = findInstance(hCalc);
    if (calculator == nullptr)
        return HRES_ERR_NO_INSTANCE;
    *digit = DISPLAY_REGISTER(calculator).getDigit(index);
    return HRES_OK;
}

extern "C" HRES GetDisplayDigit(const HCALC hCalc, const int8_t index, int8_t *digit) {
    Calculator* calculator = findInstance(hCalc);
    if (calculator == nullptr)
        return HRES_ERR_NO_INSTANCE;
    *digit = DISPLAY_REGISTER(calculator).getDisplayDigit(index);
    return HRES_OK;
}

extern "C" HRES ExportDump(const HCALC hCalc, int8_t *dump, int8_t *dumpSize) {
    Calculator* calculator = findInstance(hCalc);
    if (calculator == nullptr)
        return HRES_ERR_NO_INSTANCE;
    *dumpSize = calculator->exportDump(dump);
    return HRES_OK;
}

extern "C" HRES ImportDump(const HCALC hCalc, int8_t *dump, const int8_t dumpSize) {
    Calculator* calculator = findInstance(hCalc);
    if (calculator == nullptr)
        return HRES_ERR_NO_INSTANCE;
    int8_t importedSize = calculator->importDump(dump, dumpSize);
    if (importedSize == dumpSize)
        return HRES_OK;
    if (importedSize == 1)
        return HRES_ERR_WRONG_DUMP_VERSION;
    return HRES_ERR_WRONG_DUMP_SIZE;
}

#pragma clang diagnostic pop
