/**
 * Calculator Comrade Library
 * License: https://github.com/DmitryDzz/calculator-comrade-lib/blob/master/LICENSE
 * Author: Dmitry Dzakhov
 * Email: info@robot-mitya.ru
 */
#ifndef CALCULATORCOMRADE_MATH_H
#define CALCULATORCOMRADE_MATH_H

#include "calculator/register.h"
#include "calculator/operation.h"

namespace calculatorcomrade {

    class Math {
    public:
        static void calculate(Register &r1, Register &r2, const Operation &operation, uint8_t options);
        static void calculatePercent(Register &r1, Register &r2, const Operation &operation, uint8_t options);

        static int8_t compare(const Register &r1, const Register &r2);
        static int8_t compare(const Register &r1, const Register &r2, bool ignoreSign);

        static void add(Register &r1, Register &r2);
        static void sub(Register &r1, Register &r2);
        static void mul(Register &r1, Register &r2);
        static void mul(Register &r1, Register &r2, Register &acc);
        static void div(Register &r1, Register &r2);
        static void div(Register &r1, Register &r2, Register &acc);

        static void addPercent(Register &r1, Register &r2);
        static void subPercent(Register &r1, Register &r2);
        static void mulPercent(Register &r1, Register &r2);
        static void divPercent(Register &r1, Register &r2);
        static void muPercent(Register &r1, Register &r2);

        static void sqrt(Register &r);
        static void sqrt(Register &r, Register &h2, Register &g2);
        static void changeSign(Register &r);
    private:
        static void unsafeShiftRight(Register &r, bool updatePointPos);
        static bool safeShiftLeft(Register &r, bool updatePointPos);
        static int8_t compareDigitsIgnoreSign(const Register &r1, const Register &r2);
        static void normalizePointPositions(Register &r1, Register &r2);
        static void truncRightZeros(Register &r);
        static void doubleSizedRegisterToSingle(Register &r2, Register &r);
        static void appendZerosOnOverflow(Register &r, uint8_t options);

        static void addInternal(Register &r1, Register &r2);
        static void addPercent(Register &r1ex, Register &r2ex, Register &accEx);
    };
}

#endif //CALCULATORCOMRADE_MATH_H
