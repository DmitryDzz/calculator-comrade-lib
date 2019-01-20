//
// Created by dmitrydzz on 10.01.19.
//

#ifndef CALCULATORCOMRADE_MATH_H
#define CALCULATORCOMRADE_MATH_H

#include "calculator/register.h"
#include "calculator/operation.h"

namespace calculatorcomrade {

    class Math {
    public:
        static void calculate(Register &r1, Register &r2, const Operation &operation);

        static void sum(Register &r1, Register &r2);
        static void mul(Register &r1, Register &r2);
        static void mul(Register &r1, Register &r2, Register &r3);
    private:
        static void unsafeShiftRight(Register &r, const bool updatePointPos);
        static void safeShiftLeft(Register &r, const bool updatePointPos);
        static int8_t compareIgnoreSign(const Register &r1, const Register &r2);
        static void normalizePointPositions(Register &r1, Register &r2);
        static void truncRightZeros(Register &r);

        static void sum(Register &r1, Register &r2, bool truncRightZeros);
    };
};

#endif //CALCULATORCOMRADE_MATH_H
