//
// Created by dmitrydzz on 27.01.2019.
//

#include <memory.h>
#include <map>
#include <utility>
#include "calculator/calculator.h"

#include "calculator/main.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

using namespace calculatorcomrade;

typedef uint8_t HCALC;
typedef int8_t HRES;

typedef std::map<HCALC, Calculator*> InstancesMap;
InstancesMap g_instances;
HCALC g_calc_hnd = 0;

#define HRES_OK ((HCALC)0)
#define HRES_ERR_NO_INSTANCE ((HCALC)-1)
#define HRES_ERR_TOO_MANY_CALCULATORS ((HCALC)-2)

#define CALCULATOR(pCalculator) (*((Calculator *)pCalculator))
#define DISPLAY_REGISTER(pCalculator) (CALCULATOR(pCalculator).getState().x)

//TODO DZZ Make tests
HCALC addInstance(Calculator *calculator) {
    if (g_calc_hnd == 255)
        return HRES_ERR_TOO_MANY_CALCULATORS;
    HCALC result = ++g_calc_hnd;
    g_instances[g_calc_hnd] = calculator;
    return result;
}

Calculator* findInstance(HCALC hCalc) {
    auto it = g_instances.find(hCalc);
    if (it == g_instances.end())
        return nullptr;
    return it->second;
}

extern "C" HCALC CreateCalculator(const int8_t digits) {
    return addInstance(new Calculator(digits));
}

extern "C" HRES DisposeCalculator(const HCALC hCalc) {
    Calculator* calculator = findInstance(hCalc);
    if (calculator == nullptr)
        return HRES_ERR_NO_INSTANCE;
    delete calculator;
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

extern "C" HRES IsNegative(const HCALC hCalc, bool *negative) {
    Calculator* calculator = findInstance(hCalc);
    if (calculator == nullptr)
        return HRES_ERR_NO_INSTANCE;
    *negative = DISPLAY_REGISTER(calculator).getNegative();
    return HRES_OK;
}

extern "C" HRES IsOverflow(const HCALC hCalc, bool *overflow) {
    Calculator* calculator = findInstance(hCalc);
    if (calculator == nullptr)
        return HRES_ERR_NO_INSTANCE;
    *overflow = DISPLAY_REGISTER(calculator).getOverflow();
    return HRES_OK;
}

extern "C" HRES PointPos(const HCALC hCalc, int8_t *pointPos) {
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

#pragma clang diagnostic pop
