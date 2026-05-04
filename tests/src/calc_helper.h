/**
 * Calculator Comrade Library
 * License: https://github.com/DmitryDzz/calculator-comrade-lib/blob/master/LICENSE
 * Author: Dmitry Dzakhov
 * Email: info@robot-mitya.ru
 */
#ifndef CALCULATORCOMRADE_CALC_HELPER_HPP
#define CALCULATORCOMRADE_CALC_HELPER_HPP

#include <string>
#include "calculator/register.h"

namespace calculatorcomrade {

    CalcInt getAbsIntValue(Register &r);

    CalcInt getIntValue(Register &r);

    void setValue(Register &r, CalcInt value);

    void setValue(Register &r, CalcInt value, CalcInt digitsAfterPoint);

    void evaluateText(Register &r, std::string *output);
}

#endif //CALCULATORCOMRADE_CALC_HELPER_HPP
